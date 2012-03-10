/*
 * BaseType.h
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#ifndef BASETYPE_H_
#define BASETYPE_H_

namespace Dies
{

class BaseType : public DwarfDie
{
public:
	BaseType(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Base") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}
};

} /* namespace Dies */
#endif /* BASETYPE_H_ */
