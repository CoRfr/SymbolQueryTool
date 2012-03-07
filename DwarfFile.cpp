/*
 * DwarfFile.cpp
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#include "Common.h"

using namespace std;

DwarfFile::DwarfFile(const char * file) : m_dbg(NULL)
{
	/* Open file */
	m_fd = open(file, O_RDONLY);
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

DwarfFile::~DwarfFile()
{
	if(m_dbg != NULL) {
		dwarf_end(m_dbg);
		close(m_fd);
	}
}

DwarfCu * DwarfFile::FirstCu()
{
	return DwarfCu::GetCu(m_dbg);
}

DwarfCu * DwarfFile::NextCu(const DwarfCu * cu)
{
	return cu->Next();
}

DwarfDie * DwarfFile::FindDie(const char * name)
{
	DwarfCu * cu = FirstCu();
	while(cu != NULL)
	{
		//cout << cu << endl;

		DwarfDie * die = cu->GetDie();
		while(die != NULL)
		{
			//cout << die << endl;

			{
				DwarfDie * child = die->FindChildren(name);
				if(child != NULL)
				{
					return child;
				}
			}

			die = die->Next();
		}

		cu = cu->Next();
	}

	return NULL;
}
