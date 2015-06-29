#include <windows.h>
#include <tchar.h>
#include "include/CkFtp2.h"
#include <iostream>
#include "RemotoFileParser.h"

int _tmain(int argc, _TCHAR* argv[])
{
	RemotoFileParser* parser = new RemotoFileParser();
	cout << "START Parse" << endl;
	parser->parse();
	delete parser;
	cout << "END" << endl;
	system("pause");
	return 0;	
}

