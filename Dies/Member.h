/*
 * Member.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef MEMBER_H_
#define MEMBER_H_

namespace Dies
{

class Member : public DwarfDie
{
public:
	Member(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Member") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}
};

} /* namespace Dies */
#endif /* MEMBER_H_ */
