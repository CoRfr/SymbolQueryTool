/*
 * XmlExporter.cpp
 *
 *  Created on: 10 mars 2012
 *      Author: cor
 */

#include "../Common.h"

#include "XmlVisitor.h"
#include "XmlDieVisitor.h"
#include "XmlExporter.h"

namespace Exporters
{

using namespace std;
using namespace tinyxml2;

XmlExporter::XmlExporter() :
		m_doc()
{
	m_root = m_doc.NewElement("Root");
	m_doc.InsertEndChild(m_root);
}

void XmlExporter::Save(string & filename)
{
	m_doc.SaveFile(filename.c_str());
}

void XmlExporter::Print()
{
	XMLPrinter printer(stdout);
	m_doc.Print(&printer);
}

void XmlExporter::ExportDie(DwarfDie * die, bool verbose)
{
	XMLElement * elmt = m_doc.NewElement("Query");
	m_root->InsertEndChild(elmt);

	if(die == NULL)
	{
		elmt->SetAttribute("Error", "SymbolNotFound");
		cerr << "WARN: Symbol not found" << endl;
		return;
	}

	if (die->HasAttribute(DW_AT_name))
		elmt->SetAttribute("Die", die->GetAttrName());

	if (verbose)
	{
		XmlDieVisitor visitor(elmt);
		die->Explore(&visitor);
	}
	else
	{
		XmlVisitor visitor(elmt);
		die->Explore(&visitor);

		/* Export enums */
		XMLElement * xmlEnums = m_doc.NewElement("Enums");
		elmt->InsertEndChild(xmlEnums);

		XmlVisitor enumVisitor(xmlEnums);
		enumVisitor.SetOption(XmlVisitor::OPTION_EXPLORE_ENUMS, true);

		map<unsigned int, Dies::EnumerationType *> enums = visitor.GetEnums();
		map<unsigned int, Dies::EnumerationType *>::iterator it;
		for(it = enums.begin(); it != enums.end(); it++ )
		{
			it->second->Explore(&enumVisitor);
		}
	}
}

void XmlExporter::ExportCus(DwarfObj * obj)
{
	XMLElement * queryElmt = m_doc.NewElement("Query");
	m_root->InsertEndChild(queryElmt);

	DwarfCu * cu = obj->FirstCu(), * tmpCu;
	while (cu != NULL)
	{
		Dies::CompileUnit * die = dynamic_cast<Dies::CompileUnit*>(cu->GetDie());

		if (die != NULL)
		{
			XMLElement * elmt = m_doc.NewElement("CompileUnit");
			queryElmt->InsertEndChild(elmt);

			/* Print every attributes */
			list<DwarfAttrib> attribs = die->GetAttributes();
			list<DwarfAttrib>::iterator it;

			if (!attribs.empty())
			{
				XMLElement * xmlAttribs = m_doc.NewElement("Attribs");
				elmt->InsertEndChild(xmlAttribs);

				for (it = attribs.begin(); it != attribs.end(); it++)
				{
					XMLElement * attrib = m_doc.NewElement("Attrib");
					xmlAttribs->InsertEndChild(attrib);

					attrib->SetAttribute("Name", it->GetName());

					{
						/* Buf */
						char buf[20];

						/* Vars */
						const char * tmpStr;
						DwarfDie * tmpDie;
						unsigned long tmpUdata;
						signed long tmpSdata;

						/* String */
						if (it->AsString(&tmpStr))
						{
							attrib->SetAttribute("Type", "String");
							attrib->SetAttribute("Value", tmpStr);
						}

						/* Die */
						else if (it->AsDie(&tmpDie))
						{
							attrib->SetAttribute("Type", "Die");
							delete tmpDie;
						}

						/* Udata */
						else if (it->AsUdata(&tmpUdata))
						{
							attrib->SetAttribute("Type", "Udata");
							sprintf(buf, "%lu", tmpUdata);
							attrib->SetAttribute("Value", buf);
						}

						/* Sdata */
						else if (it->AsSdata(&tmpSdata))
						{
							attrib->SetAttribute("Type", "Sdata");
							sprintf(buf, "%ls", tmpUdata);
							attrib->SetAttribute("Value", buf);
						}

						/* Addr */
						else if(it->AsAddr(&tmpUdata))
						{
							attrib->SetAttribute("Type", "Addr");
							sprintf(buf, "0x%x", tmpUdata);
							attrib->SetAttribute("Value", buf);
						}
					}
				}
			}
		}

		/* Next */
		tmpCu = cu;
		cu = cu->Next();
		delete tmpCu;
	}
}

} /* namespace Exporters */
