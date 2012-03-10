/*
 * ArrayType.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef ARRAYTYPE_H_
#define ARRAYTYPE_H_

namespace Dies
{

using namespace std;

class ArrayType : public DwarfDie
{
public:
	ArrayType(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "Array") {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}

	size_t GetCount()
	{
		/* For arrays, there is one child, which is a subrange,
		 * which countains an attribute, DW_AT_upper_bound, that is the [count] of the array.
		 */
		DwarfDie * child = this->FirstChildren();
		if( (child == NULL) || !child->HasAttribute(DW_AT_upper_bound) )
		{
			cerr << "WARN: Unable to get array upper bound" << endl;
			return 0;
		}

		unsigned long udata;
		child->GetAttribute(DW_AT_upper_bound)->AsUdata(&udata);

		return (size_t)udata;
	}
};

} /* namespace Dies */
#endif /* ARRAYTYPE_H_ */
