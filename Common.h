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

	#define __STDC_FORMAT_MACROS
	#include <inttypes.h>

	/* Dwarf */
	#include <dwarf.h>
	#include <elfutils/libdw.h>

	#include "DwarfHelper.h"
}

/* Internal */

class DieVisitor;

class DwarfObj;
class DwarfDie;
class DwarfCu;
class DwarfFile;
class DwarfTag;
class DwarfAttrib;

#include "DieVisitor.h"

#include "DwarfTag.h"
#include "DwarfAttrib.h"
#include "DwarfFile.h"
#include "DwarfObj.h"
#include "DwarfDie.h"
#include "DwarfCu.h"

#include "Dies/Dies.h"

std::ostream & operator<<(std::ostream & os, DwarfCu * cu);
std::ostream & operator<<(std::ostream & os, DwarfDie * die);

#endif /* COMMON_H_ */
