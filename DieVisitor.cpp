/*
 * DieVisitor.cpp
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#include "Common.h"

DieVisitor::DieVisitor()
{
}

void DieVisitor::DieVisitor::BeginVisit(Dies::Member & member)
{
	BeginVisit((DwarfDie &) member);
}
void DieVisitor::EndVisit(Dies::Member & member)
{
	EndVisit((DwarfDie &) member);
}

void DieVisitor::BeginVisit(Dies::ArrayType & array)
{
	BeginVisit((DwarfDie &) array);
}
void DieVisitor::EndVisit(Dies::ArrayType & array)
{
	EndVisit((DwarfDie &) array);
}

void DieVisitor::BeginVisit(Dies::Typedef & tdef)
{
	BeginVisit((DwarfDie &) tdef);
}
void DieVisitor::EndVisit(Dies::Typedef & tdef)
{
	EndVisit((DwarfDie &) tdef);
}

void DieVisitor::BeginVisit(Dies::CompileUnit & cu)
{
	BeginVisit((DwarfDie &) cu);
}
void DieVisitor::EndVisit(Dies::CompileUnit & cu)
{
	EndVisit((DwarfDie &) cu);
}

void DieVisitor::BeginVisit(Dies::StructureType & str)
{
	BeginVisit((DwarfDie &) str);
}
void DieVisitor::EndVisit(Dies::StructureType & str)
{
	EndVisit((DwarfDie &) str);
}

void DieVisitor::BeginVisit(Dies::BaseType & base)
{
	BeginVisit((DwarfDie &) base);
}
void DieVisitor::EndVisit(Dies::BaseType & base)
{
	EndVisit((DwarfDie &) base);
}

void DieVisitor::BeginVisit(Dies::PointerType & ptr)
{
	BeginVisit((DwarfDie &) ptr);
}
void DieVisitor::EndVisit(Dies::PointerType & ptr)
{
	EndVisit((DwarfDie &) ptr);
}

void DieVisitor::BeginVisit(Dies::UnionType & uni)
{
	BeginVisit((DwarfDie &) uni);
}
void DieVisitor::EndVisit(Dies::UnionType & uni)
{
	EndVisit((DwarfDie &) uni);
}

void DieVisitor::BeginVisit(Dies::Variable & var)
{
	BeginVisit((DwarfDie &) var);
}
void DieVisitor::EndVisit(Dies::Variable & var)
{
	EndVisit((DwarfDie &) var);
}

void DieVisitor::BeginVisit(Dies::VolatileType & vol)
{
	BeginVisit((DwarfDie &) vol);
}
void DieVisitor::EndVisit(Dies::VolatileType & vol)
{
	EndVisit((DwarfDie &) vol);
}

void DieVisitor::BeginVisit(Dies::EnumerationType & enu)
{
	BeginVisit((DwarfDie &) enu);
}
void DieVisitor::EndVisit(Dies::EnumerationType & enu)
{
	EndVisit((DwarfDie &) enu);
}

void DieVisitor::BeginVisit(Dies::Enumerator & enu)
{
	BeginVisit((DwarfDie &) enu);
}
void DieVisitor::EndVisit(Dies::Enumerator & enu)
{
	EndVisit((DwarfDie &) enu);
}

void DieVisitor::BeginVisit(Dies::SubrangeType & sub)
{
	BeginVisit((DwarfDie &) sub);
}
void DieVisitor::EndVisit(Dies::SubrangeType & sub)
{
	EndVisit((DwarfDie &) sub);
}

void DieVisitor::BeginVisit(Dies::UnknownTag & uni)
{
	BeginVisit((DwarfDie &) uni);
}
void DieVisitor::EndVisit(Dies::UnknownTag & uni)
{
	EndVisit((DwarfDie &) uni);
}
