/*
 * main.c
 *
 *  Created on: 15 févr. 2012
 *      Author: cor
 */

#include "Common.h"

#include "XmlVisitor/XmlExporter.h"
#include "XmlVisitor/XmlVisitor.h"
#include "XmlVisitor/XmlDieVisitor.h"

#define VERSION_MAJOR	0
#define VERSION_MINOR	1

using namespace std;

void printUsage(const char * name)
{
	cout << name << " v" << VERSION_MAJOR << "." << VERSION_MINOR << endl;
	cout << "---" << endl;
	cout << "Query stuff from files with Dwarf debugging infos (.elf, .o, .exe, .dll, ...)" << endl;
	cout << "Syntax: <source file> <options>" << endl;
	cout << "Options:" << endl;
	cout << " -o <output.xml> : File output as XML, to stdout if option is not specified" << endl;
	cout << " -q <query + query options> : Add queries results to output" << endl;
	cout << "Queries:" << endl;
	cout << " 'cus' : List all files used in compilation" << endl;
	cout << " 'sym' : Find symbols (types, members) in input file and dump the type as a tree" << endl;
	cout << "         down to base types" << endl;
	cout << "         => Format: sym <symbol> <verbose:0|1,optional>" << endl;
	cout << "Example: " << endl;
	cout << " " << name << " /path/to/my/file.elf -o dump.xml -q cus -q sym myBigVar" << endl;
}

namespace Queries
{

class Query
{
public:
	virtual int ParseOptions(int argc, char * argv[]) = 0;
	virtual void DoWork(DwarfObj & obj, Exporters::XmlExporter & exporter) = 0;

	string Name;
protected:
	Query(string name) :
			Name(name)
	{
	}
};

class Cu: public Query
{
public:
	static const char * Option;

	Cu() :
			Query("Cu")
	{
	}

	int ParseOptions(int argc, char * argv[])
	{
		return 0;
	}

	void DoWork(DwarfObj & obj, Exporters::XmlExporter & exporter)
	{
		exporter.ExportCus(&obj);
	}
};

const char * Cu::Option = "cus";

class Enum: public Query
{
public:
	static const char * Option;

	Enum() :
			Query("Enum")
	{
	}

	int ParseOptions(int argc, char * argv[])
	{
		return 0;
	}

	void DoWork(DwarfObj & obj, Exporters::XmlExporter & exporter)
	{
		exporter.ExportEnums(&obj);
	}
};

const char * Enum::Option = "enums";

class Symbol: public Query
{
public:
	static const char * Option;

	Symbol() :
			Query("Symbol"), Verbose(false)
	{
	}

	string ExportedSymbol;
	bool Verbose;

	int ParseOptions(int argc, char * argv[])
	{
		if ((argc == 0) || (argv[0][0] == '-'))
		{
			cerr << "Query Symbol takes at least one argument" << endl;
			throw exception();
		}

		ExportedSymbol = argv[0];
		cout << "Symbol: Export Symbol is " << ExportedSymbol << endl;

		if (argc <= 1)
			return 1;

		string verb(argv[1]);
		cout << "Symbol: Verbose is " << verb << endl;
		if (verb == "0")
			Verbose = false;
		else if (verb == "1")
			Verbose = true;
		else
			return 1;

		return 2;
	}

	void DoWork(DwarfObj & obj, Exporters::XmlExporter & exporter)
	{
		DwarfDie * root = obj.FindDie(ExportedSymbol.c_str());
		exporter.ExportDie(root, Verbose);
		if (root != NULL)
		{
			delete root;
		}
	}
};

const char * Symbol::Option = "sym";

}

class Options
{
public:
	Options() :
			HasOutput(false)
	{
	}

	void Parse(int argc, char * argv[]);

	string SourceFile;

	/* Output */
	bool HasOutput;
	string Output;

	/* Queries */
	list<Queries::Query *> Queries;
};

void Options::Parse(int argc, char * argv[])
{
	int lastArgc = 0;
	int currentArgc = 1;
	bool error = true;

	/* Source file */
	if (argc < 2)
		return;
	SourceFile = argv[currentArgc];
	currentArgc++;

	cout << "Found Source " << SourceFile << endl;

	while (lastArgc != currentArgc)
	{
		lastArgc = currentArgc;

		if (argc <= currentArgc)
			break;

		if (string(argv[currentArgc]) == "-o")
		{
			currentArgc++;

			if (argc <= currentArgc)
				break;

			HasOutput = true;
			Output = argv[currentArgc];
			currentArgc++;

			/* All required options have been found */
			error = false;

			cout << "Found Output " << Output << endl;
		}
		else if (string(argv[currentArgc]) == "-q")
		{
			currentArgc++;
			if (argc <= currentArgc)
			{
				error = true;
				break;
			}

			string queryStr(argv[currentArgc]);

			Queries::Query * query = NULL;
			if (queryStr == Queries::Cu::Option)
			{
				query = new Queries::Cu();
				cout << "Found Query CU" << endl;

			}
			else if (queryStr == Queries::Symbol::Option)
			{
				query = new Queries::Symbol();
				cout << "Found Query Symbol" << endl;
			}
			else if (queryStr == Queries::Enum::Option)
			{
				query = new Queries::Enum();
				cout << "Found Query Enum" << endl;
			}
			else
			{
				cout << "Unable to find query for " << queryStr << endl;
			}

			currentArgc++;
			if (query != NULL)
			{
				currentArgc += query->ParseOptions(argc - currentArgc, &argv[currentArgc]);
				Queries.push_back(query);
			}
		}

	}

	if (error)
	{
		cerr << "Unable to parse options" << endl;
		throw exception();
	}
}

ostream & operator<<(ostream & os, DwarfCu * cu)
{
	return *cu << os;
}

ostream & operator<<(ostream & os, DwarfDie * die)
{
	os << "Die " << die->GetTag().ToString();
	const char * name = die->GetAttrName();
	if (name != NULL)
		os << " [" << name << "]";

	return os;
}

int main(int argc, char * argv[])
{

	/* Usage */
	if (argc <= 1)
	{
		printUsage(argv[0]);
		return -1;
	}

	try
	{
		/* Handle options */
		Options opts;
		opts.Parse(argc, argv);

		/* Process */
		DwarfObj file(opts.SourceFile);
        file.PrintFiles();

		Exporters::XmlExporter exporter;

		list<Queries::Query *>::iterator it;
		for (it = opts.Queries.begin(); it != opts.Queries.end(); it++)
		{
			(*it)->DoWork(file, exporter);
		}

		/* Export */
		if (opts.HasOutput)
		{
			exporter.Save(opts.Output);
		}
		else
		{
			exporter.Print();
		}

	} catch (exception & ex)
	{
		cerr << "Exception" << endl;
	}

	return 0;
}

