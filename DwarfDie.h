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
	static DwarfDie * Build(Dwarf * dbg, Dwarf_Die & die);

	DwarfDie * Clone();

	const DwarfTag & GetTag() const;
	const char * GetName() const { return m_name; }
	unsigned int GetUniqueId();

	DwarfDie * Next();

	bool HasChildren();
	DwarfDie * FirstChildren();

	DwarfDie * FindChildren(const char * name);

	/* Visitor */
	virtual void Explore(DieVisitor * visitor);

	/* Attributes */
	bool HasAttribute(Dwarf_Half attrib);
	DwarfAttrib * GetAttribute(Dwarf_Half attrib);
	std::list<DwarfAttrib> GetAttributes();

	/* Attributes Helpers */
	const char * GetAttrName();
	DwarfDie * GetAttrType();

protected:
	DwarfDie(Dwarf * dbg, const Dwarf_Die & die, const char * name);

	const char * m_name;
	Dwarf * m_dbg;
	Dwarf_Die m_die;
	DwarfTag m_tag;
};

#endif /* DWARFDIE_H_ */
