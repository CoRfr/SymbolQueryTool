/*
 * DwarfFile.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef DWARFFILE_H_
#define DWARFFILE_H_

class DwarfFile
{
public:
	DwarfFile(const char * file);
	virtual ~DwarfFile();

	bool IsValid() const { return (m_dbg != NULL); }
	Dwarf * GetDbg() const { return m_dbg; }

	DwarfCu * FirstCu();
	DwarfCu * NextCu(const DwarfCu * cu);

	DwarfDie * FindDie(const char * name);

private:
	Dwarf * m_dbg;
	int m_fd;
};

#endif /* DWARFFILE_H_ */
