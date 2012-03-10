/*
 * Variable.h
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

namespace Dies
{

class Variable : public DwarfDie
{
public:
	Variable(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Variable") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}
};

} /* namespace Dies */
#endif /* VARIABLE_H_ */
