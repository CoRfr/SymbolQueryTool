/*
 * DwarfDie.cpp
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#include "Common.h"

using namespace std;

DwarfDie::DwarfDie(Dwarf * dbg, const Dwarf_Die & die) :
		m_dbg(dbg),
		m_die(die),
		m_tag( dwarf_tag(&m_die) )
{
}

const DwarfTag & DwarfDie::GetTag() const
{
	return m_tag;
}

const char * DwarfDie::GetName()
{
	return dwarf_diename(&m_die);
}

bool DwarfDie::HasAttribute(Dwarf_Half attrib)
{
	return (dwarf_hasattr(&m_die, attrib) == 1);
}

DwarfAttrib * DwarfDie::GetAttribute(Dwarf_Half attrib)
{
	if(HasAttribute(attrib))
	{
		Dwarf_Attribute attr;
		if(dwarf_attr(&m_die, attrib, &attr) == NULL)
		{
			cerr << "Failed to retrieve " << attrib << endl;
			return NULL;
		}

		return new DwarfAttrib(m_dbg, attr);
	}

	return NULL;
}

typedef struct DieAttrsCbAdsTag {
	list<DwarfAttrib> * attribs;
	Dwarf * dbg;
} DieAttrsCbAds;

static int DieAttrsCb(Dwarf_Attribute * attr, void * arg)
{
	DieAttrsCbAds * ads = (DieAttrsCbAds *)arg;
	DwarfAttrib newAttrib(ads->dbg, *attr);
	ads->attribs->push_back(newAttrib);
	return 0;
}

list<DwarfAttrib> DwarfDie::GetAttributes()
{
	list<DwarfAttrib> attribs;
	DieAttrsCbAds ads;

	ads.attribs = &attribs;
	ads.dbg = m_dbg;

	dwarf_getattrs(&m_die, &DieAttrsCb, &ads, 0);

	return attribs;
}

DwarfDie * DwarfDie::Next()
{
	Dwarf_Die die;
	if(dwarf_siblingof(&m_die, &die) == 0)
		return new DwarfDie(m_dbg, die);

	return NULL;
}

bool DwarfDie::HasChildren()
{
	return (dwarf_haschildren(&m_die) != 0);
}

DwarfDie * DwarfDie::FirstChildren()
{
	Dwarf_Die child;
	if(dwarf_child(&m_die, &child) == 0)
		return new DwarfDie(m_dbg, child);

	return NULL;
}

DwarfDie * DwarfDie::FindChildren(const char * name)
{
	DwarfDie * die = FirstChildren();
	while(die != NULL)
	{
		const char * childName = die->GetName();
		if( (childName != NULL) && (strcmp(name, childName) == 0) )
			return die;

		DwarfDie * child = die->FindChildren(name);
		if(child != NULL)
			return child;

		die = die->Next();
	}
}
