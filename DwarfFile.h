/*
 * DwarfFile.h
 *
 *  Created on: 10 mars 2012
 *      Author: cor
 */

#ifndef DWARFFILE_H_
#define DWARFFILE_H_

class DwarfFile
{
public:
	DwarfFile(Dwarf * dbg, Dwarf_Files * file);

protected:
	Dwarf * m_dbg;
	Dwarf_Files * m_file;
};

#endif /* DWARFFILE_H_ */
