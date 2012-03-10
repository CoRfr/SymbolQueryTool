/*
 * DwarfObj.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef DWARFOBJ_H_
#define DWARFOBJ_H_

class DwarfObj
{
public:
	DwarfObj(const std::string & file);
	virtual ~DwarfObj();

	bool IsValid() const { return (m_dbg != NULL); }
	Dwarf * GetDbg() const { return m_dbg; }

	DwarfCu * FirstCu();
	DwarfCu * NextCu(const DwarfCu * cu);

	DwarfDie * FindDie(const char * name);

	void PrintFiles();

private:
	Dwarf * m_dbg;
	int m_fd;
};

#endif /* DWARFOBJ_H_ */
