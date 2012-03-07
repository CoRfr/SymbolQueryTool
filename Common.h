/*
 * DwarfDie.h
 *
 *  Created on: 7 mars 2012
 *      Author: cor
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <string>
#include <sstream>
#include <list>

extern "C" {
	#include <fcntl.h>
	#include <unistd.h>
	#include <string.h>

	/* Dwarf */
	#include <dwarf.h>
	#include <elfutils/libdw.h>

	/* XML */
	#include <libxml/encoding.h>
	#include <libxml/xmlwriter.h>

	#include "DwarfHelper.h"
}

/* Internal */

class DwarfFile;
class DwarfDie;
class DwarfCu;
class DwarfTag;
class DwarfAttrib;

#include "DwarfTag.h"
#include "DwarfAttrib.h"
#include "DwarfFile.h"
#include "DwarfDie.h"
#include "DwarfCu.h"

std::ostream & operator<<(std::ostream & os, DwarfCu * cu);
std::ostream & operator<<(std::ostream & os, DwarfDie * die);

#endif /* COMMON_H_ */
