/*
 * XmlVisitor.cpp
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#include "../Common.h"

#include "XmlVisitor.h"

using namespace std;
using namespace tinyxml2;

XmlVisitor::XmlVisitor(tinyxml2::XMLElement * elmt) :
		m_currentVarName(NULL), m_exploreEnums(false)
{
	m_doc = elmt->GetDocument();
	m_currentElmt = elmt;
}

void XmlVisitor::SetOption(Options opt, bool value)
{
	switch(opt)
	{
	case OPTION_EXPLORE_ENUMS:
		m_exploreEnums = value;
		break;
	}
}

void XmlVisitor::BeginVisit(Dies::Typedef & tdef)
{
	m_typedefs.push(tdef);

	DwarfDie * type = tdef.GetAttrType();
	type->Explore(this);
}

void XmlVisitor::EndVisit(Dies::Typedef & tdef)
{
	m_typedefs.pop();
}

const char * XmlVisitor::GetTypeName(DwarfDie & die)
{
	const char * name = NULL;

	if(m_typedefs.size() != 0)
		name = m_typedefs.top().GetAttrName();

	if(name == NULL)
		name = die.GetAttrName();

	if(name == NULL) {
		cerr << "Unable to find structure name" << endl;
		throw exception();
	}

	return name;
}

void XmlVisitor::BeginVisitChildType(DwarfDie & die)
{
	XMLElement * elmt = m_doc->NewElement(die.GetName());
	m_currentElmt->InsertEndChild(elmt);
	m_currentElmt = elmt;

	if(m_currentVarName != NULL)
	{
		elmt->SetAttribute("Name", m_currentVarName);
		m_currentVarName = NULL;
	}

	if(die.GetTag().GetTag() != DW_TAG_array_type)
	{
		const char * name = NULL;
		if(die.GetTag().GetTag() != DW_TAG_base_type)
		{
			name = GetTypeName(die);
			elmt->SetAttribute("Type", name);
		}
		else
		{
			name = die.GetAttrName();
			elmt->SetAttribute("Type", name);
		}

		DwarfAttrib * sz = die.GetAttribute(DW_AT_byte_size);
		if(sz != NULL)
		{
			unsigned long data;
			sz->AsUdata(&data);
			elmt->SetAttribute("Size", (int)data);
			delete sz;
		}
		else
		{
			cerr << "WARN: " << name << " has no size" << endl;
		}
	}
	else
	{
		/* For arrays */

		/* Get the count ... */
		elmt->SetAttribute("Count", (unsigned int)dynamic_cast<Dies::ArrayType*>(&die)->GetCount() + 1 );

		/* Continue digging */
		DwarfDie * type = die.GetAttrType();
		type->Explore(this);
	}
}

void XmlVisitor::EndVisitChildType(DwarfDie & die)
{
	m_currentElmt = m_currentElmt->Parent()->ToElement();
}

void XmlVisitor::BeginVisit(Dies::Member & member)
{
	m_currentVarName = member.GetAttrName();

	DwarfDie * type = member.GetAttrType();
	type->Explore(this);
}

void XmlVisitor::EndVisit(Dies::Member & str)
{
	m_currentVarName = NULL;
}

void XmlVisitor::BeginVisit(Dies::Variable & var)
{
	m_currentVarName = var.GetAttrName();

	DwarfDie * type = var.GetAttrType();
	type->Explore(this);
}

void XmlVisitor::EndVisit(Dies::Variable & var)
{
	m_currentVarName = NULL;
}

void XmlVisitor::BeginVisit(Dies::VolatileType & var)
{
	DwarfDie * type = var.GetAttrType();
	type->Explore(this);
}

void XmlVisitor::EndVisit(Dies::VolatileType & var)
{
	m_currentVarName = NULL;
}

void XmlVisitor::BeginVisit(Dies::Enumerator & enu)
{
	XMLElement * elmt = m_doc->NewElement(enu.GetName());
	m_currentElmt->InsertEndChild(elmt);

	elmt->SetAttribute("Name", enu.GetAttrName());
	elmt->SetAttribute("Value", enu.GetAttrConstValue());
}
