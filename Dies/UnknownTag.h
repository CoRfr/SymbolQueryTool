/*
 * UnknownTag.h
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#ifndef UNKNOWNTAG_H_
#define UNKNOWNTAG_H_

namespace Dies
{

class UnknownTag : public DwarfDie
{
public:
	UnknownTag(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "UNKNOWN") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}
};

} /* namespace Dies */
#endif /* UNKNOWNTAG_H_ */
