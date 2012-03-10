/*
 * DwarfTag.cpp
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#include "Common.h"

using namespace std;

const char * DwarfTag::GetName(unsigned int tag)
{
	switch(tag)
	{
	case DW_TAG_array_type: return "Array";
	case DW_TAG_class_type: return "Class";
	case DW_TAG_enumeration_type: return "Enum";
	case DW_TAG_pointer_type: return "Pointer";
	case DW_TAG_compile_unit: return "CompileUnit";
	case DW_TAG_typedef: return "Typedef";
	case DW_TAG_union_type: return "Union";
	case DW_TAG_variable: return "Variable";
	case DW_TAG_member: return "Member";
	case DW_TAG_structure_type: return "Structure";
	case DW_TAG_volatile_type: return "VolatileType";
	default:
		cout << "DwarfTag: Unknown tag " << hex << tag << endl;
		return NULL;
	}
}

DwarfTag::DwarfTag(unsigned int tag) : m_tag(tag)
{
}

