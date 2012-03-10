/*
 * DwarfAttrib.cpp
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#include "Common.h"

using namespace std;

const char * DwarfAttrib::GetAttrName(Dwarf_Word attr)
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
	case DW_AT_external: return "External";
	case DW_AT_declaration: return "Declaration";
	case DW_AT_encoding: return "Encoding";
	case DW_AT_upper_bound: return "UpperBound";
	case DW_AT_const_value: return "ConstValue";
	case DW_AT_producer: return "Producer";
	case DW_AT_location: return "Location";
	case DW_AT_language: return "Language";
	case DW_AT_low_pc: return "LowPC";
	case DW_AT_high_pc: return "HighPC";
	case DW_AT_entry_pc: return "EntryPC";
	case DW_AT_ranges: return "Ranges";
	case DW_AT_stmt_list: return "Statements";
	case DW_AT_comp_dir: return "CompDir";
	case DW_AT_macro_info: return "MacroInfo";

	default:
		cout << "Unknown attr: " << hex << attr << endl;
		return "UNKNOWN";
	}
}

DwarfAttrib::DwarfAttrib(Dwarf * dbg, const Dwarf_Attribute & attr)
	: m_dbg(dbg), m_attr(attr)
{
}

const char * DwarfAttrib::GetName()
{
	return GetAttrName( this->GetAttr() );
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
	switch(GetForm())
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
	switch(GetForm())
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
		*die = DwarfDie::Build(m_dbg, tmp);
		return true;
	}
	}

	return false;
}

bool DwarfAttrib::AsUdata(unsigned long * var)
{
	switch(GetForm())
	{
	case DW_FORM_data1:
	case DW_FORM_data2:
	case DW_FORM_data4:
	case DW_FORM_data8:
	case DW_FORM_udata:
	{
		Dwarf_Word uword;
		if(dwarf_formudata(&m_attr, &uword) != 0)
		{
			return false;
		}
		*var = (unsigned long)uword;
		return true;
	}
	}

	return false;
}

bool DwarfAttrib::AsSdata(signed long * var)
{
	switch(GetForm())
	{
	case DW_FORM_sdata:
	{
		Dwarf_Sword sword;
		if(dwarf_formsdata(&m_attr, &sword) != 0)
		{
			return false;
		}
		*var = (unsigned long)sword;
		return true;
	}
	}

	return false;
}

bool DwarfAttrib::AsAddr(unsigned long * var)
{
	switch(GetForm())
	{
	case DW_FORM_addr:
	case DW_FORM_block:
	case DW_FORM_block1:
	case DW_FORM_block2:
	case DW_FORM_block4:
	{
		Dwarf_Addr addr;
		if(dwarf_formaddr(&m_attr, &addr) != 0)
			return false;
		*var = (unsigned long)addr;
		return true;
	}
	}

	return false;
}
std::string DwarfAttrib::ToString()
{
	ostringstream stream;

	/* Name */
	const char * name = GetName();
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
		DwarfDie * dwarfDie = DwarfDie::Build(m_dbg, die);
		const char * str = dwarfDie->GetAttrName();
		if(str != NULL)
			stream << ": " << str;
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
	case DW_FORM_flag:
	{
		bool flag;
		dwarf_formflag(&m_attr, &flag);
		if(flag)
			stream << ": " << "YES";
		else
			stream << ": " << "NO";
		break;
	}
	default:
		cout << "Unknown form: " << hex << form << endl;
		stream << "UNKNOWN";
	}

	return stream.str();
}
