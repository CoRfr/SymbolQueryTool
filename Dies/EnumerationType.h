/*
 * EnumerationType.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef ENUMERATIONTYPE_H_
#define ENUMERATIONTYPE_H_

namespace Dies
{

class EnumerationType : public DwarfDie
{
public:
	EnumerationType(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Enum"), ExploreEnums(false) {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		if(ExploreEnums)
			DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}

	bool ExploreEnums;
};

} /* namespace Dies */
#endif /* ENUMERATIONTYPE_H_ */
