/*
 * Typedef.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef TYPEDEF_H_
#define TYPEDEF_H_

namespace Dies
{

class Typedef : public DwarfDie
{
public:
	Typedef(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Typedef") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}
};

} /* namespace Dies */
#endif /* TYPEDEF_H_ */
