/*
 * DwarfFile.cpp
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#include "Common.h"

using namespace std;

DwarfObj::DwarfObj(const std::string & file) : m_dbg(NULL)
{
	/* Open file */
	m_fd = open(file.c_str(), O_RDONLY);
	if (m_fd == -1) {
		cerr << "Cannot open '" << file << "'";
		return;
	}

	/* Start dwarf */
	m_dbg = dwarf_begin(m_fd, DWARF_C_READ);
	if (m_dbg == NULL) {
		cerr << "Not usable '" << file << "': " << dwarf_errmsg(-1);
		close(m_fd);
		return;
	}
}

DwarfObj::~DwarfObj()
{
	if(m_dbg != NULL) {
		dwarf_end(m_dbg);
		close(m_fd);
	}
}

DwarfCu * DwarfObj::FirstCu()
{
	return DwarfCu::GetCu(m_dbg);
}

DwarfCu * DwarfObj::NextCu(const DwarfCu * cu)
{
	return cu->Next();
}

DwarfDie * DwarfObj::FindDie(const char * name)
{
	DwarfCu * cu = FirstCu();
	DwarfCu * tmpCu;

	while(cu != NULL)
	{

		DwarfDie * die = cu->GetDie();
		if(die != NULL)
		{
			cout << die << endl;

			/* Is this the die we're looking for ? */
			const char * childName = die->GetAttrName();
			if( (childName != NULL) && (strcmp(name, childName) == 0) )
				return die;

			/* Is one child the die we're looking for ? */
			{
				DwarfDie * child = die->FindChildren(name);
				if(child != NULL)
				{
					delete die;
					return child;
				}
			}
		}

		/* Next Cu */
		tmpCu = cu;
		cu = cu->Next();
		delete tmpCu;
	}

	return NULL;
}

void DwarfObj::PrintFiles()
{
	DwarfCu * cu = FirstCu();
	DwarfCu * tmpCu;

	int idx = 0;
	while(cu != NULL)
	{
		DwarfDie * die = cu->GetDie();
		cout << idx++ << ": " << die->GetAttrName() << endl;

		/* Next Cu */
		tmpCu = cu;
		cu = cu->Next();
		delete tmpCu;
	}
}
