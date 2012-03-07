/*
 * DwarfCu.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef DWARFCU_H_
#define DWARFCU_H_

class DwarfCu
{
public:
	static DwarfCu * GetCu(Dwarf * dbg, Dwarf_Off offset = 0);

	std::ostream & operator<<(std::ostream & os);

	DwarfCu(Dwarf * dbg,
			Dwarf_Off offset,
			Dwarf_Off nextOffset,
			size_t hSize,
			Dwarf_Off abbrev,
			uint8_t addressSize,
			uint8_t offsetSize);

	DwarfCu * Next() const;

	DwarfDie * GetDie();

private:
	Dwarf * m_dbg;
	Dwarf_Off m_offset;
	Dwarf_Off m_nextOffset;
	size_t m_hSize;
	Dwarf_Off m_abbrev;
	uint8_t m_addressSize;
	uint8_t m_offsetSize;
};

#endif /* DWARFCU_H_ */
