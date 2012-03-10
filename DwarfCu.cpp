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
		m_addressSize(addressSize), m_offsetSize(offsetSize), m_die(NULL)
{
}

DwarfCu::~DwarfCu()
{
	if(m_die != NULL)
	{
		delete m_die;
		m_die = NULL;
	}
}

DwarfCu * DwarfCu::Next() const
{
	return GetCu(m_dbg, m_nextOffset);
}

DwarfDie * DwarfCu::GetDie()
{
	if(m_die == NULL)
	{
		Dwarf_Die die;
		if(dwarf_offdie(m_dbg, m_offset + m_hSize, &die) != NULL)
		{
			m_die = DwarfDie::Build(m_dbg, die);
		}
	}

	return m_die;
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

DwarfFile * DwarfCu::GetFile(int idx)
{
	return dynamic_cast<Dies::CompileUnit *>(GetDie())->GetFile(idx);
}

