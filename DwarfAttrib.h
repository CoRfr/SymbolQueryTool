/*
 * DwarfAttrib.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef DWARFATTRIB_H_
#define DWARFATTRIB_H_

class DwarfAttrib
{
public:
	static const char * GetName(Dwarf_Word attr);

	DwarfAttrib(Dwarf * dbg, const Dwarf_Attribute & attr);

	unsigned int GetAttr();
	unsigned int GetForm();

	std::string ToString();

	bool AsString(const char ** str);
	bool AsDie(DwarfDie ** die);

protected:
	Dwarf * m_dbg;
	Dwarf_Attribute m_attr;
};

#endif /* DWARFATTRIB_H_ */
