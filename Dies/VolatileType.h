/*
 * VolatileType.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef VOLATILETYPE_H_
#define VOLATILETYPE_H_

namespace Dies
{

class VolatileType : public DwarfDie
{
public:
	VolatileType(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Volatile") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}
};

} /* namespace Dies */
#endif /* VOLATILETYPE_H_ */
