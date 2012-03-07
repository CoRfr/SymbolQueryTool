/*
 * main.c
 *
 *  Created on: 15 févr. 2012
 *      Author: cor
 */

#include "Common.h"

using namespace std;

void printUsage() {

}

ostream & operator<<(ostream & os, DwarfCu * cu)
{
	return *cu << os;
}

ostream & operator<<(ostream & os, DwarfDie * die)
{
	os << "Die " << die->GetTag().ToString();
	const char * name = die->GetName();
	if(name != NULL)
		os << " [" << name << "]";

	return os;
}

void handle(DwarfDie * die, int level)
{
	if(die == NULL)
		return;

	/* Self */
	//cout << string(4*level, ' ') << "Hu:" << die << endl;

	/* List Die attributes */
	/*{
		list<DwarfAttrib> attrs = die->GetAttributes();
		list<DwarfAttrib>::iterator it;

		for(it = attrs.begin(); it != attrs.end(); it++)
		{
			cout << string(4*level + 2, ' ') << it->ToString() << endl;
		}
	}*/

	/* Handle special tags */
	switch(die->GetTag().GetTag())
	{
	case DW_TAG_member:
	case DW_TAG_volatile_type:
	case DW_TAG_structure_type:
	case DW_TAG_typedef:
	case DW_TAG_union_type:
	case DW_TAG_enumeration_type:
	case DW_TAG_array_type:
		/* Self */
		cout << string(4*level, ' ') << die << endl;

		if(die->HasAttribute(DW_AT_type))
		{
			DwarfAttrib * attr = die->GetAttribute(DW_AT_type);
			//cout << string(4*level + 2, ' ') << attr->ToString() << endl;

			DwarfDie * childType;
			if(attr->AsDie(&childType))
			{
				handle(childType, level+1);
			}
		}

		break;
	}

	/* Child */
	DwarfDie * child = die->FirstChildren();
	while(child != NULL)
	{
		handle(child, level+1);

		/* Next */
		child = child->Next();
	}
}

int main(int argc, char * argv[]) {
	/* Usage */
	if (argc != 3) {
		printUsage();
		return -1;
	}

	DwarfFile file(argv[1]);
	DwarfDie * root = file.FindDie(argv[2]);
	handle(root, 0);

	return 0;
}
