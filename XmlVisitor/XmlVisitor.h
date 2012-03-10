/*
 * XmlVisitor.h
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#ifndef XMLVISITOR_H_
#define XMLVISITOR_H_

#include "../TinyXml/tinyxml2.h"

#include <stack>
#include <exception>
#include <map>

class XmlVisitor : public DieVisitor
{
public:
	XmlVisitor(tinyxml2::XMLElement * elmt);

	typedef enum OptionsTag {
		OPTION_EXPLORE_ENUMS
	} Options;

	void SetOption(Options opt, bool value);

	virtual void BeginVisit(Dies::Typedef & tdef);
	virtual void EndVisit(Dies::Typedef & tdef);

	virtual void BeginVisit(Dies::StructureType & str)
	{ BeginVisitChildType(str); }
	virtual void EndVisit(Dies::StructureType & str)
	{ EndVisitChildType(str); }

	virtual void BeginVisit(Dies::UnionType & uni)
	{ BeginVisitChildType(uni); }
	virtual void EndVisit(Dies::UnionType & uni)
	{ EndVisitChildType(uni); }

	virtual void BeginVisit(Dies::ArrayType & arr)
	{ BeginVisitChildType(arr); }
	virtual void EndVisit(Dies::ArrayType & arr)
	{ EndVisitChildType(arr); }

	virtual void BeginVisit(Dies::BaseType & base)
	{ BeginVisitChildType(base); }
	virtual void EndVisit(Dies::BaseType & base)
	{ EndVisitChildType(base); }

	virtual void BeginVisit(Dies::SubrangeType & sub) {}
	virtual void EndVisit(Dies::SubrangeType & sub) {}

	virtual void BeginVisit(Dies::EnumerationType & enu)
	{
		enu.ExploreEnums = m_exploreEnums;

		if(!m_exploreEnums)
		{
			unsigned int id = enu.GetUniqueId();
			if(m_enums.count(id) == 0)
				m_enums[id] = dynamic_cast<Dies::EnumerationType*>(enu.Clone());
		}
		BeginVisitChildType(enu);
	}
	virtual void EndVisit(Dies::EnumerationType & enu)
	{ EndVisitChildType(enu); }

	virtual void BeginVisit(Dies::Enumerator & enu);

	virtual void BeginVisit(Dies::Member & member);
	virtual void EndVisit(Dies::Member & member);

	virtual void BeginVisit(Dies::Variable & var);
	virtual void EndVisit(Dies::Variable & var);

	virtual void BeginVisit(Dies::VolatileType & var);
	virtual void EndVisit(Dies::VolatileType & var);

	std::map<unsigned int, Dies::EnumerationType *> GetEnums() { return m_enums; }

private:
	tinyxml2::XMLDocument * m_doc;

	tinyxml2::XMLElement * m_currentElmt;
	const char * m_currentVarName;

	/* Options */
	bool m_exploreEnums;

	std::stack<Dies::Typedef> m_typedefs;
	std::map<unsigned int, Dies::EnumerationType *> m_enums;

	const char * GetTypeName(DwarfDie & die);

	void BeginVisitChildType(DwarfDie & die);
	void EndVisitChildType(DwarfDie & die);
};

#endif /* XMLVISITOR_H_ */
