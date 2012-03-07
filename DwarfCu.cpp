/*
 * DwarfCu.cpp
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#include "Common.h"

using namespace std;

DwarfCu * DwarfCu::GetCu(Dwarf * dbg, Dwarf_Off offset)
{
	Dwarf_Off nextOffset = 0;
	size_t hsize;
	Dwarf_Off abbrev;
	uint8_t addresssize;
	uint8_t offsetsize;
	if(dwarf_nextcu(dbg, offset, &nextOffset, &hsize, &abbrev, &addresssize, &offsetsize) == 0)
	{
		return new DwarfCu(dbg, offset, nextOffset, hsize, abbrev, addresssize, offsetsize);
	}

	return NULL;
}

DwarfCu::DwarfCu(Dwarf * dbg, Dwarf_Off offset, Dwarf_Off nextOffset, size_t hSize,
		Dwarf_Off abbrev, uint8_t addressSize, uint8_t offsetSize) :
		m_dbg(dbg), m_offset(offset), m_nextOffset(nextOffset), m_hSize(hSize), m_abbrev(abbrev),
		m_addressSize(addressSize), m_offsetSize(offsetSize)
{
}

DwarfCu * DwarfCu::Next() const
{
	return GetCu(m_dbg, m_nextOffset);
}

DwarfDie * DwarfCu::GetDie()
{
	Dwarf_Die die;
	if(dwarf_offdie(m_dbg, m_offset + m_hSize, &die) != NULL)
	{
		return new DwarfDie(m_dbg, die);
	}

	return NULL;
}

ostream & DwarfCu::operator<<(ostream & os)
{
	os << "DwarfCu: " << m_offset << " " <<
			"[" << m_hSize <<
			"," << m_abbrev <<
			"," << m_addressSize <<
			"," << m_offsetSize << "]";
	return os;
}

