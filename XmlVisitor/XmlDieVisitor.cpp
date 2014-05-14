/*
 * XmlDieVisitor.cpp
 *
 *  Created on: 10 mars 2012
 *      Author: cor
 */

#include "../Common.h"

#include "XmlDieVisitor.h"

using namespace std;
using namespace tinyxml2;

XmlDieVisitor::XmlDieVisitor(XMLElement * elmt) :
		m_indentLevel(0), m_indentLevelMax(13)
{
	m_doc = elmt->GetDocument();
	m_currentElmt = elmt;
}

void XmlDieVisitor::BeginVisit(DwarfDie & die)
{
	const char * name = die.GetName();

	//cout << string(2*m_indentLevel, ' ') << "<" << name << ">" << endl;
	m_indentLevel++;

	if(m_indentLevel > m_indentLevelMax)
	{
		m_indentLevelMax = m_indentLevel;
		cout << name << "[" << die.GetAttrName() << endl;
	}

	/* Element with Die name (Structure, Union ...) */
	XMLElement * elmt = m_doc->NewElement(name);
	m_currentElmt->InsertEndChild(elmt);

	/* Print every attributes */
	list<DwarfAttrib> attribs = die.GetAttributes();
	list<DwarfAttrib>::iterator it;

	if(!attribs.empty())
	{
		XMLElement * xmlAttribs = m_doc->NewElement("Attribs");
		elmt->InsertEndChild(xmlAttribs);

		for(it = attribs.begin(); it != attribs.end(); it++)
		{
			XMLElement * attrib = m_doc->NewElement("Attrib");
			xmlAttribs->InsertEndChild(attrib);

			attrib->SetAttribute("Name", it->GetName());

			{
				/* Buf */
				const int bufSize = 40;
				char buf[bufSize+1] = {0};

				/* Vars */
				const char * tmpStr;
				DwarfDie * tmpDie;
				uint64_t tmpUdata;
				int64_t tmpSdata;

				/* String */
				if(it->AsString(&tmpStr))
				{
					attrib->SetAttribute("Type", "String");
					attrib->SetAttribute("Value", tmpStr);
				}

				/* Die */
				else if(it->AsDie(&tmpDie) && (strcmp(it->GetName(), "Sibling") != 0))
				{
					XMLElement * saveCurrent = m_currentElmt;
					attrib->SetAttribute("Type", "Die");

					if( (strcmp(name, "Pointer") != 0) )// && (m_indentLevel < 30) )
					{
						m_currentElmt = attrib;
						tmpDie->Explore(this);
						m_currentElmt = saveCurrent;
					}

					delete tmpDie;
				}

				/* Udata */
				else if(it->AsUdata(&tmpUdata))
				{
					attrib->SetAttribute("Type", "Udata");
					snprintf(buf, bufSize, "%" PRIu64, tmpUdata);
					attrib->SetAttribute("Value", buf);
				}

				/* Sdata */
				else if(it->AsSdata(&tmpSdata))
				{
					attrib->SetAttribute("Type", "Sdata");
					snprintf(buf, bufSize, "%" PRIi64, tmpSdata);
					attrib->SetAttribute("Value", buf);
				}

				/* Addr */
				else if(it->AsAddr(&tmpUdata))
				{
					attrib->SetAttribute("Type", "Addr");
					snprintf(buf, bufSize, "0x%" PRIX64, tmpUdata);
					attrib->SetAttribute("Value", buf);
				}
			}
		}
	}

	XMLElement * childs = m_doc->NewElement("Childs");
	elmt->InsertEndChild(childs);
	m_currentElmt = childs;
}

void XmlDieVisitor::EndVisit(DwarfDie & die)
{
	m_currentElmt = m_currentElmt->Parent()->ToElement();
	m_currentElmt = m_currentElmt->Parent()->ToElement();
	m_indentLevel--;
	//cout << string(2*m_indentLevel, ' ') << "</" << die.GetName() << ">" << endl;
}

