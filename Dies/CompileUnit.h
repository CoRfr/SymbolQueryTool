/*
 * CompileUnit.h
 *
 *  Created on: 8 mars 2012
 *      Author: cor
 */

#ifndef COMPILEUNIT_H_
#define COMPILEUNIT_H_

namespace Dies
{

using namespace std;

class CompileUnit : public DwarfDie
{
public:
	CompileUnit(Dwarf * dbg, const Dwarf_Die & die)
	: DwarfDie(dbg, die, "CompileUnit"), m_files(NULL), m_filesCnt(0) {}

	virtual void Explore(DieVisitor * visitor)
	{
		visitor->BeginVisit(*this);
		DwarfDie::Explore(visitor);
		visitor->EndVisit(*this);
	}

	DwarfFile * GetFile(int idx)
	{
		if(m_files == NULL)
		{
			if(dwarf_getsrcfiles(&m_die, &m_files, &m_filesCnt) != 0)
			{
				cerr << "Unable to get files from CU" << endl;
			}

#if 0
			cout << "Got " << m_filesCnt << " files" << endl;
			for(int i = 0; i < m_filesCnt; i++)
			{
				Dwarf_Word mtime, length;
				const char * str = dwarf_filesrc (m_files, i, &mtime, &length);

				cout << i << str << " | " << mtime << " | " << length << endl;
			}
#endif
		}

		if(m_files != NULL)
		{
			if(idx >= m_filesCnt)
			{
				cerr << "Files idx is out of files in CU" << endl;
				return NULL;
			}

			return new DwarfFile(m_dbg, m_files);
		}

		return NULL;
	}

protected:
	Dwarf_Files * m_files;
	size_t m_filesCnt;
};

} /* namespace Dies */
#endif /* COMPILEUNIT_H_ */
