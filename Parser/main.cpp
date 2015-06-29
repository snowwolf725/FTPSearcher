
#include <iostream>
#include "RemotoFileParser.h"

using namespace std;

int main() {
	RemotoFileParser* parser = new RemotoFileParser();
	parser->parse();
	delete parser;
	cout << "END" << endl;
	return 0;
}

