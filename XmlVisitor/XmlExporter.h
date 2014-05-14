/*
 * XmlExporter.h
 *
 *  Created on: 10 mars 2012
 *      Author: cor
 */

#ifndef XMLEXPORTER_H_
#define XMLEXPORTER_H_

#include "../TinyXml/tinyxml2.h"

namespace Exporters
{

class XmlExporter
{
public:
	XmlExporter();

	void Save(std::string & filename);
	void Print();

	void ExportDie(DwarfDie * die, bool verbose = false);
	void ExportCus(DwarfObj * obj);
	void ExportEnums(DwarfObj * obj);

private:
	tinyxml2::XMLDocument m_doc;

	tinyxml2::XMLElement * m_root;

	tinyxml2::XMLElement * ExportCu(Dies::CompileUnit * die);
};

} /* namespace Exporters */
#endif /* XMLEXPORTER_H_ */
