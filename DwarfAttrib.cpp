/*
 * DwarfAttrib.cpp
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#include "Common.h"

using namespace std;

const char * DwarfAttrib::GetName(Dwarf_Word attr)
{
	switch(attr)
	{
	case DW_AT_name: return "Name";
	case DW_AT_type: return "Type";
	case DW_AT_decl_file: return "DeclFile";
	case DW_AT_decl_line: return "DeclLine";
	case DW_AT_data_member_location: return "DataMemberLocation";
	case DW_AT_byte_size: return "ByteSize";
	case DW_AT_sibling: return "Sibling";
	default:
		cout << "Unknown attr: " << hex << attr << endl;
		return NULL;
	}
}

DwarfAttrib::DwarfAttrib(Dwarf * dbg, const Dwarf_Attribute & attr)
	: m_dbg(dbg), m_attr(attr)
{

}

unsigned int DwarfAttrib::GetAttr()
{
	return dwarf_whatattr(&m_attr);
}

unsigned int DwarfAttrib::GetForm()
{
	return dwarf_whatform(&m_attr);
}

bool DwarfAttrib::AsString(const char ** str)
{
	unsigned int form = GetForm();
	switch(form)
	{
	case DW_FORM_string:
	case DW_FORM_strp:
	{
		const char * tmp = dwarf_formstring(&m_attr);
		if(tmp != NULL)
		{
			*str = tmp;
			return true;
		}
		break;
	}
	}

	return false;
}

bool DwarfAttrib::AsDie(DwarfDie ** die)
{
	unsigned int form = GetForm();
	switch(form)
	{
	case DW_FORM_ref1:
	case DW_FORM_ref2:
	case DW_FORM_ref4:
	case DW_FORM_ref8:
	{
		Dwarf_Die tmp;
		if(dwarf_formref_die(&m_attr, &tmp) == NULL)
		{
			cout << "Unable to retrieve ref" << endl;
			*die = NULL;
			return false;
		}
		*die = new DwarfDie(m_dbg, tmp);
		return true;
	}
	}

	return false;
}

std::string DwarfAttrib::ToString()
{
	ostringstream stream;

	/* Name */
	const char * name = GetName( this->GetAttr() );
	if(name != NULL)
		stream << name;

	/* Content */
	unsigned int form = GetForm();
	stream << "[" << hex << form << dec << "] ";

	switch(form)
	{
	case DW_FORM_string:
	case DW_FORM_strp:
	{
		const char * str = dwarf_formstring(&m_attr);
		if(str != NULL)
			stream << ": " << str;
		break;
	}
	case DW_FORM_ref1:
	case DW_FORM_ref2:
	case DW_FORM_ref4:
	case DW_FORM_ref8:
	{
		Dwarf_Die die;
		if(dwarf_formref_die(&m_attr, &die) == NULL)
		{
			cout << "Unable to retrieve ref" << endl;
			break;
		}
		DwarfDie * dwarfDie = new DwarfDie(m_dbg, die);
		stream << ": " << dwarfDie->GetName();
		break;
	}
	case DW_FORM_data1:
	case DW_FORM_data2:
	case DW_FORM_data4:
	case DW_FORM_data8:
	case DW_FORM_sdata:
	case DW_FORM_udata:
	{
		Dwarf_Word u;
		dwarf_formudata(&m_attr, &u);
		stream << ": " << u;
		break;
	}
	case DW_FORM_block:
	case DW_FORM_block1:
	case DW_FORM_block2:
	case DW_FORM_block4:
		break;
	default:
		cout << "Unknown form: " << hex << form << endl;
		break;
	}

	return stream.str();
}
