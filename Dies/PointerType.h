/*
 * PointerType.h
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#ifndef POINTERTYPE_H_
#define POINTERTYPE_H_

namespace Dies
{

class PointerType : public DwarfDie
{
public:
	PointerType(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Pointer") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}
};

} /* namespace Dies */
#endif /* POINTERTYPE_H_ */
