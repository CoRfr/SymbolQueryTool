/*
 * UnionType.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef UNIONTYPE_H_
#define UNIONTYPE_H_

namespace Dies
{

class UnionType : public DwarfDie
{
public:
	UnionType(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Union") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}
};

} /* namespace Dies */
#endif /* UNIONTYPE_H_ */
