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
	static const char * GetAttrName(Dwarf_Word attr);

	DwarfAttrib(Dwarf * dbg, const Dwarf_Attribute & attr);

	const char * GetName();
	unsigned int GetAttr();
	unsigned int GetForm();

	std::string ToString();

	bool AsString(const char ** str);
	bool AsDie(DwarfDie ** die);
	bool AsUdata(unsigned long * var);
	bool AsSdata(signed long * var);
	bool AsAddr(unsigned long * var);

protected:
	Dwarf * m_dbg;
	Dwarf_Attribute m_attr;
};

#endif /* DWARFATTRIB_H_ */
