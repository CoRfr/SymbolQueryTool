/*
 * XmlDieVisitor.h
 *
 *  Created on: 10 mars 2012
 *      Author: cor
 */

#ifndef XMLDIEVISITOR_H_
#define XMLDIEVISITOR_H_

#include "../TinyXml/tinyxml2.h"

#include <stack>
#include <exception>

class XmlDieVisitor : public DieVisitor
{
public:
	XmlDieVisitor(tinyxml2::XMLElement * elmt);

	virtual void BeginVisit(DwarfDie & die);
	virtual void EndVisit(DwarfDie & die);

private:
	tinyxml2::XMLDocument * m_doc;

	tinyxml2::XMLElement * m_currentElmt;

	int m_indentLevel;
	int m_indentLevelMax;
};

#endif /* XMLDIEVISITOR_H_ */
