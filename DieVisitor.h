/*
 * DieVisitor.h
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#ifndef DIEVISITOR_H_
#define DIEVISITOR_H_

namespace Dies {
	class ArrayType;
	class BaseType;
	class CompileUnit;
	class EnumerationType;
	class Enumerator;
	class Member;
	class PointerType;
	class StructureType;
	class SubrangeType;
	class Typedef;
	class UnionType;
	class UnknownTag;
	class Variable;
	class VolatileType;

}

class DieVisitor
{
public:
	DieVisitor();

	/* Default */
	virtual void BeginVisit(DwarfDie & die) {}
	virtual void EndVisit(DwarfDie & die) {}

	/* Dies */
	virtual void BeginVisit(Dies::ArrayType & array);
	virtual void EndVisit(Dies::ArrayType & array);

	virtual void BeginVisit(Dies::BaseType & base);
	virtual void EndVisit(Dies::BaseType & base);

	virtual void BeginVisit(Dies::CompileUnit & cu);
	virtual void EndVisit(Dies::CompileUnit & cu);

	virtual void BeginVisit(Dies::EnumerationType & enu);
	virtual void EndVisit(Dies::EnumerationType & enu);

	virtual void BeginVisit(Dies::Enumerator & enu);
	virtual void EndVisit(Dies::Enumerator & enu);

	virtual void BeginVisit(Dies::Member & member);
	virtual void EndVisit(Dies::Member & member);

	virtual void BeginVisit(Dies::PointerType & ptr);
	virtual void EndVisit(Dies::PointerType & ptr);

	virtual void BeginVisit(Dies::StructureType & str);
	virtual void EndVisit(Dies::StructureType & str);

	virtual void BeginVisit(Dies::SubrangeType & sub);
	virtual void EndVisit(Dies::SubrangeType & sub);

	virtual void BeginVisit(Dies::Typedef & tdef);
	virtual void EndVisit(Dies::Typedef & tdef);

	virtual void BeginVisit(Dies::UnionType & uni);
	virtual void EndVisit(Dies::UnionType & uni);

	virtual void BeginVisit(Dies::UnknownTag & uni);
	virtual void EndVisit(Dies::UnknownTag & uni);

	virtual void BeginVisit(Dies::Variable & var);
	virtual void EndVisit(Dies::Variable & var);

	virtual void BeginVisit(Dies::VolatileType & vol);
	virtual void EndVisit(Dies::VolatileType & vol);




};

#endif /* DIEVISITOR_H_ */
