/*
 * StructureType.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef STRUCTURETYPE_H_
#define STRUCTURETYPE_H_

namespace Dies
{

class StructureType : public DwarfDie
{
public:
	StructureType(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Structure") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}
};

} /* namespace Dies */
#endif /* STRUCTURETYPE_H_ */
