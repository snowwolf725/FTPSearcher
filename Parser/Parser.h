/*
 * Parser.h
 *
 *  Created on: 2009/3/19
 *      Author: Administrator
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>

using namespace std;
typedef basic_string<char>::size_type S_T;
static const S_T npos = -1;

class Parser {
public:
	Parser();
	~Parser();
	vector<string> tokenize(const string& src, string tok, bool trim = false, string null_subst = "");
	bool parse(string fileName, int docid);
	void output(string str, int pos);
	bool isNumeric(const string &test);
	bool checkToken(const string &token);
	string toLowerString(const string &token);
private:
	void initialStopWord();
	int _docid;
	map<string, int> _stopWord;
	ofstream outfile;
};

#endif /* PARSER_H_ */
