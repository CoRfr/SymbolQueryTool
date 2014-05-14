/*
 * DwarfDie.cpp
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#include "Common.h"

using namespace std;

DwarfDie * DwarfDie::Build(Dwarf * dbg, Dwarf_Die & die)
{
	int tag = dwarf_tag(&die);

	switch(tag)
	{
	case DW_TAG_member: return new Dies::Member(dbg, die);
	case DW_TAG_volatile_type: return new Dies::VolatileType(dbg, die);
	case DW_TAG_structure_type: return new Dies::StructureType(dbg, die);
	case DW_TAG_typedef: return new Dies::Typedef(dbg, die);
	case DW_TAG_union_type: return new Dies::UnionType(dbg, die);
	case DW_TAG_enumeration_type: return new Dies::EnumerationType(dbg, die);
	case DW_TAG_array_type: return new Dies::ArrayType(dbg, die);
	case DW_TAG_compile_unit: return new Dies::CompileUnit(dbg, die);
	case DW_TAG_base_type: return new Dies::BaseType(dbg, die);
	case DW_TAG_pointer_type: return new Dies::PointerType(dbg, die);
	case DW_TAG_subrange_type: return new Dies::SubrangeType(dbg, die);
	case DW_TAG_enumerator: return new Dies::Enumerator(dbg, die);
	case DW_TAG_variable: return new Dies::Variable(dbg, die);
	default: return new Dies::UnknownTag(dbg, die);
	}

#if 0
	const char * name = DwarfTag::GetAttrName(tag);
	if(name != NULL)
		cout << "DwarfDie: Unknown tag `" << name << "`" << endl;
	if(dwarf_hasattr(&die, DW_AT_name))
		cout << "\telement is " << dwarf_diename(&die) << endl;
#endif

	return NULL;
}

DwarfDie::DwarfDie(Dwarf * dbg, const Dwarf_Die & die, const char * name) :
		m_name(name),
		m_dbg(dbg),
		m_die(die),
		m_tag( dwarf_tag(&m_die) )
{
}

DwarfDie * DwarfDie::Clone()
{
	return Build(m_dbg, m_die);
}

const DwarfTag & DwarfDie::GetTag() const
{
	return m_tag;
}

const char * DwarfDie::GetAttrName()
{
	if(!dwarf_hasattr(&m_die, DW_AT_name))
		return NULL;
	return dwarf_diename(&m_die);
}

unsigned int DwarfDie::GetUniqueId()
{
	return (unsigned int)dwarf_dieoffset(&m_die);
}

bool DwarfDie::HasAttribute(Dwarf_Half attrib)
{
	return (dwarf_hasattr(&m_die, attrib) == 1);
}

DwarfAttrib * DwarfDie::GetAttribute(Dwarf_Half attrib)
{
	if(HasAttribute(attrib))
	{
		Dwarf_Attribute attr;
		if(dwarf_attr(&m_die, attrib, &attr) == NULL)
		{
			cerr << "Failed to retrieve " << attrib << endl;
			return NULL;
		}

		return new DwarfAttrib(m_dbg, attr);
	}

	return NULL;
}

typedef struct DieAttrsCbAdsTag {
	list<DwarfAttrib> * attribs;
	Dwarf * dbg;
} DieAttrsCbAds;

static int DieAttrsCb(Dwarf_Attribute * attr, void * arg)
{
	DieAttrsCbAds * ads = (DieAttrsCbAds *)arg;
	DwarfAttrib newAttrib(ads->dbg, *attr);
	ads->attribs->push_back(newAttrib);
	return 0;
}

list<DwarfAttrib> DwarfDie::GetAttributes()
{
	list<DwarfAttrib> attribs;
	DieAttrsCbAds ads;

	ads.attribs = &attribs;
	ads.dbg = m_dbg;

	dwarf_getattrs(&m_die, &DieAttrsCb, &ads, 0);

	return attribs;
}

DwarfDie * DwarfDie::Next()
{
	Dwarf_Die die;
	if(dwarf_siblingof(&m_die, &die) == 0)
		return DwarfDie::Build(m_dbg, die);

	return NULL;
}

bool DwarfDie::HasChildren()
{
	return (dwarf_haschildren(&m_die) != 0);
}

DwarfDie * DwarfDie::FirstChildren()
{
	Dwarf_Die child;
	if(dwarf_child(&m_die, &child) == 0)
		return DwarfDie::Build(m_dbg, child);

	return NULL;
}

DwarfDie * DwarfDie::FindChildren(const char * name)
{
	DwarfDie * die = FirstChildren();
	DwarfDie * tmpDie;

	while(die != NULL)
	{
		/* This die ? */
		const char * childName = die->GetAttrName();
		if( (childName != NULL) && (strcmp(name, childName) == 0) )
			return die;

		/* A child ? */
		DwarfDie * child = die->FindChildren(name);
		if(child != NULL)
		{
			delete die;
			return child;
		}

		/* Next */
		tmpDie = die;
		die = die->Next();
		delete tmpDie;
	}

	return NULL;
}

void DwarfDie::Explore(DieVisitor * visitor)
{
	/* Child */
	DwarfDie * child = this->FirstChildren();

#if 0
	/* No Child ? */
	if(child == NULL)
	{
		list<DwarfAttrib> attrs = this->GetAttributes();
		list<DwarfAttrib>::iterator it;

		cout << "Attribs";
		const char * name = this->GetAttrName();
		if(name != NULL)
			cout << "[" << name << "]";
		cout << ": ";
		for(it = attrs.begin(); it != attrs.end(); it++)
		{
			cout << it->ToString() << " | ";
			//cout << it->GetName() << " | ";
		}
		cout << endl;
	}
#endif

	while(child != NULL)
	{
		child->Explore(visitor);

		/* Next */
		DwarfDie * oldChild = child;
		child = child->Next();
		delete oldChild;
	}
}

DwarfDie * DwarfDie::GetAttrType()
{
	if(!this->HasAttribute(DW_AT_type))
	{
		const char * name = GetAttrName();
		if(!name)
			name = "";

		std::cerr << "Variable '" << name << "' has no type" << std::endl;
		return NULL;
		//throw std::exception();
	}

	DwarfAttrib * attrib = this->GetAttribute(DW_AT_type);
	DwarfDie * type;

	if(!attrib->AsDie(&type))
	{
		std::cerr << "Unable to get variable type" << std::endl;
		throw std::exception();
	}

	return type;
}
