/*
 * DwarfDie.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef DWARFDIE_H_
#define DWARFDIE_H_

class DwarfDie
{
public:
	DwarfDie(Dwarf * dbg, const Dwarf_Die & die);

	const DwarfTag & GetTag() const;
	const char * GetName();

	bool HasAttribute(Dwarf_Half attrib);
	DwarfAttrib * GetAttribute(Dwarf_Half attrib);
	std::list<DwarfAttrib> GetAttributes();

	DwarfDie * Next();

	bool HasChildren();
	DwarfDie * FirstChildren();

	DwarfDie * FindChildren(const char * name);

protected:
	Dwarf * m_dbg;
	Dwarf_Die m_die;
	DwarfTag m_tag;
};

#endif /* DWARFDIE_H_ */
