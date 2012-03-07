/*
 * DwarfTag.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef DWARFTAG_H_
#define DWARFTAG_H_

class DwarfTag
{
public:
	static const char * GetName(unsigned int tag);

	DwarfTag(unsigned int tag);

	unsigned int GetTag() const { return m_tag; }

	const char * ToString() const { return GetName(m_tag); }

private:
	unsigned int m_tag;
};

#endif /* DWARFTAG_H_ */
