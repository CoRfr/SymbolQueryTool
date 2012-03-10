/*
 * SubrangeType.h
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#ifndef SUBRANGETYPE_H_
#define SUBRANGETYPE_H_

namespace Dies
{

class SubrangeType : public DwarfDie
{
public:
	SubrangeType(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Subrange") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}
};

} /* namespace Dies */
#endif /* SUBRANGETYPE_H_ */
