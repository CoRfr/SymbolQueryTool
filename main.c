/*
 * main.c
 *
 *  Created on: 15 févr. 2012
 *      Author: cor
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/* Dwarf */
#include <dwarf.h>
#include <elfutils/libdw.h>

/* XML */
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

Dwarf *dbg_ctx;

void printUsage() {

}

void visitAbbrev(Dwarf_Abbrev * abbrev, int indent) {

}

int printAttribName(Dwarf_Attribute * attrib, void * arg) {
	printf("%p: %x %x\n", attrib, attrib->code, attrib->form);

	const char * name;

	switch (dwarf_whatattr(attrib)) {
	case DW_AT_name:
		name = "Name";
		break;
	case DW_AT_producer:
		name = "Producer";
		break;
	case DW_AT_language:
		name = "Language";
		break;
	case DW_AT_low_pc:
		name = "LowPC";
		break;
	case DW_AT_high_pc:
		name = "HighPC";
		break;
	case DW_AT_entry_pc:
		name = "EntryPC";
		break;
	case DW_AT_ranges:
		name = "Ranges";
		break;
	case DW_AT_stmt_list:
		name = "Stmt List";
		break;
	default:
		name = "Unknown";
		break;
	}

	switch (dwarf_whatform(attrib)) {
	case DW_FORM_string:
		printf("%s: (Str) %s\n", name, dwarf_formstring(attrib));
		break;
	case DW_FORM_addr: {
		Dwarf_Addr return_addr;
		dwarf_formaddr(attrib, &return_addr);
		printf("%s: (Addr) %x\n", name, return_addr);
		break;
	}
	case DW_FORM_strp: {
		printf("%s: (Strp) %s\n", name, dwarf_formstring(attrib));
		break;
	}
	default:
		printf("%s: %x\n", name);
		break;
	}

	return 0;
}

const char str_DW_TAG_compile_unit[] = "DW_TAG_compile_unit";

const char * getTagName(unsigned tag) {
	static char buffer[100];

	switch (tag) {
	case DW_TAG_compile_unit:
		return str_DW_TAG_compile_unit;
	default:
		sprintf(buffer, "%u", tag);
		break;
	}

	return buffer;
}

int loopAllStringsInCu(Dwarf *dbg, Dwarf_Off offset) {
	int count_str = 0;
	size_t len = 0;
	const char * str;

	while ((str = dwarf_getstring(dbg, offset, &len)) != NULL) {
		printf("@%lu: %s\n", offset, str);
		count_str++;
		offset += len + 1;
	}

	printf("Got %u strings\n", count_str);

	return 0;
}

Dwarf_Off findStringInDebugStr(Dwarf *dbg, const char * needle, Dwarf_Off offset) {
	int count_str = 0;
	size_t len = 0;
	const char * str;
	size_t len_needle = strlen(needle);

	while ((str = dwarf_getstring(dbg, offset, &len)) != NULL) {
		if ((len == len_needle) && (strcmp(str, needle) == 0)) {
			printf("%s found @ %x\n", str, offset);
			return offset;
		}
		count_str++;
		offset += len + 1;
	}

	//printf("Got %u strings\n", count_str);

	return -1;
}

int findDieByName(Dwarf *dbg, Dwarf_Off offset_str, Dwarf_Die * die)
{
	/* Loop through all dies to find one that match our string */

}

int printDieInfos(Dwarf * dbg, Dwarf_Die * die, int n) {
	const char *name;
	Dwarf_Off off;
	Dwarf_Off cuoff;

	name = dwarf_diename(die);
	if (name == 0)
		name = "* NO NAME *";

	off = dwarf_dieoffset(die);
	cuoff = dwarf_cuoffset(die);

	printf("%*s Name      : %s\n", n * 5, "", name);
	printf("%*s Offset    : %x\n", n * 5, "", (long long int) off);
	printf("%*s CU offset : %x\n", n * 5, "", (long long int) cuoff);
}

int loopAllAttributes(Dwarf * dbg, Dwarf_Die * die) {
	size_t abbrev_length;
	Dwarf_Off abbrev_offset = 0;
	Dwarf_Abbrev * abbrev;

	do {
		abbrev = dwarf_getabbrev(die, abbrev_offset, &abbrev_length);

		if (abbrev == (NULL - 1)) {
			return 1;
		}

		unsigned tag = dwarf_getabbrevtag(abbrev);
		unsigned code = dwarf_getabbrevcode(abbrev);
		int children = dwarf_abbrevhaschildren(abbrev);

		printf("abbrev[%llu]: code=0x%x tag=0x%x children=%d\n",
				(long long unsigned int) abbrev_offset, tag, code, children);

		switch (tag) {
		case DW_TAG_compile_unit:
		case DW_TAG_partial_unit:
		default:
			dwarf_getattrs(die, &printAttribName, NULL, 0);
			break;
		}
		size_t attr_cnt;
		if (dwarf_getattrcnt(abbrev, &attr_cnt))
			return 1;

		abbrev_offset += abbrev_length;
	} while (1);

	return 0;
}

int loopAllCu(Dwarf *dbg) {
	Dwarf_Off cu_offset = 0;
	Dwarf_Off offset = 0;
	Dwarf_Off offsetNext;
	/* Result */
	size_t header_size;
	Dwarf_Off abbrev_offset;
	uint8_t address_size;
	uint8_t offset_size;
	Dwarf_Die die;

	size_t len;
	const char * str;
	int count = 0;
	int count_str = 0;

	while (!dwarf_nextcu(dbg, cu_offset, &offsetNext, &header_size,
			&abbrev_offset, &address_size, &offset_size)) {
		printf("%4u: [%7lu to %7lu] %lu / %u / %u\n", count, cu_offset,
				offsetNext, header_size, address_size, offset_size);

		//loopAllStringsInCu(dbg, cu_offset);

		/* Get the DIE of the CU */
		if (dwarf_offdie(dbg, offset + header_size, &die) == NULL) {
			printf("Error @ %lu: %s", offset, dwarf_errmsg(-1));
			return 1;
		}

		//while(1)
		{

		}

		cu_offset += offsetNext; // ++
		count++;
	}

	return 0;
}

int printTypesInFile(const char * file, const char * typeDef) {
	/* Open file */
	int fd = open(file, O_RDONLY);
	if (fd == -1) {
		printf("Cannot open '%s': %m\n", file);
		return 1;
	}

	/* Start dwarf */
	Dwarf *dbg = dwarf_begin(fd, DWARF_C_READ);
	if (dbg == NULL) {
		printf("%s not usable: %s\n", file, dwarf_errmsg(-1));
		close(fd);
		return 1;
	}

	dbg_ctx = dbg;

	/* Do work */
	{
		Dwarf_Off offset_str = findStringInDebugStr(dbg, typeDef, 0);
		Dwarf_Die * die = findDieByName(dbg, offset_str);
		Dwarf_Die die_mem;

		if ((die = dwarf_offdie(dbg, offset_str, &die_mem)) == NULL) {
			printf("Die not found\n");
		} else {
			printDieInfos(dbg, die, 0);

			loopAllAttributes(dbg, die);

			Dwarf_Files *files;
			size_t nfiles;
			if (dwarf_getsrcfiles(die, &files, &nfiles) != 0) {
				return 1;
			}

			const char * const *dirs;
			size_t ndirs;
			if (dwarf_getsrcdirs(files, &dirs, &ndirs) != 0) {
				return 1;
			}

			size_t i;
			if (dirs[0] == NULL)
				puts(" dirs[0] = (null)");
			else
				printf(" dirs[0] = \"%s\"\n", dirs[0]);
			for (i = 1; i < ndirs; ++i)
				printf(" dirs[%zu] = \"%s\"\n", i, dirs[i]);

			for (i = 0; i < nfiles; ++i)
				printf(" file[%zu] = \"%s\"\n", i,
						dwarf_filesrc(files, i, NULL, NULL));
		}
	}

	return 0;
}

int main(int argc, char * argv[]) {
	/* Usage */
	if (argc != 2) {
		printUsage();
		return -1;
	}

	return printTypesInFile(argv[1]);
}

