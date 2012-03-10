/*
 * Enumerator.h
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#ifndef ENUMERATOR_H_
#define ENUMERATOR_H_

namespace Dies
{

class Enumerator : public DwarfDie
{
public:
	Enumerator(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Enumerator") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}

	int GetAttrConstValue()
	{
		signed long val;
		this->GetAttribute(DW_AT_const_value)->AsSdata(&val);
		return (int)val;
	}
};

} /* namespace Dies */
#endif /* ENUMERATOR_H_ */
