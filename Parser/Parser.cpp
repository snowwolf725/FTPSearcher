/*
 * Parser.cpp
 *
 *  Created on: 2009/3/19
 *      Author: Administrator
 */

#include "Parser.h"

Parser::Parser() {
	initialStopWord();
	outfile.open("docindex.txt", ios::app);
	if(!outfile){
		outfile.close();
		return;
	}
}

Parser::~Parser() {
	outfile.close();
}

vector<string> Parser::tokenize(const string& src, string tok, bool trim, string null_subst) {
	vector<string> v;
	if (src.empty() || tok.empty())
		return v;

	S_T pre_index = 0, index = 0, len = 0;
	while ((index = src.find_first_of(tok, pre_index)) != npos) {
		if ((len = index - pre_index) != 0)
			v.push_back(src.substr(pre_index, len));
		else if (trim == false)
			v.push_back(null_subst);
		pre_index = index + 1;
	}
	string endstr = src.substr(pre_index);

	if (trim == false)
		v.push_back(endstr.empty() ? null_subst : endstr);
	else if (!endstr.empty())
		v.push_back(endstr);
	return v;
}

bool Parser::parse(string fileName, int docid) {
	ifstream inputFile;
	string line, lower, delimit = " :,./+\"-()[]\\';&#@$*^?!%=~";
	vector<string> tokens;
	_docid = docid;

	inputFile.open(fileName.c_str());
	if(!inputFile) {
		inputFile.close();
		return false;
	}
	while(!inputFile.eof()) {
		getline(inputFile, line);
		//Call Split
		tokens = tokenize(line, delimit, true);
		for(int index2 = 0;index2 < (int)tokens.size(); index2++) {
			lower = toLowerString(tokens[index2]);
			if(checkToken(lower))
				output(lower, index2 + 1);
		}
		tokens.clear();
	}
	inputFile.close();
	return true;
}

void Parser::output(string str, int pos) {
	string sql = "INSERT INTO doc_index(docid, token, pos) VALUES ";
	outfile << sql << "(" << _docid << ",\"" << str << "\", " << pos << ");\n";
}

bool Parser::isNumeric(const string &test) {
	char *testEnd;
	double d;

	d = strtod(test.c_str(), &testEnd);
	return test.c_str() != testEnd;
}

bool Parser::checkToken(const string &token) {
	if(isNumeric(token) || (int)token.size() == 1)
		return false;
	map<string, int>::iterator itr = _stopWord.find(token);
	if(itr != _stopWord.end()) {
		return false;
	}
	return true;
}

string Parser::toLowerString(const string &token) {
	locale loc;
	string temp = "";
	for(int index = 0; index < (int)token.size(); index++) {
		temp += tolower(token[index], loc);
	}
	return temp;
}

void Parser::initialStopWord() {
	ifstream inputFile;
	string fileName = "stopword.txt";
	string line;
	int count = 1;

	inputFile.open(fileName.c_str());
	if(!inputFile) {
		inputFile.close();
		return;
	}
	while(!inputFile.eof()) {
		getline(inputFile, line);
		_stopWord[line] = count;
		count++;
	}
	inputFile.close();
}
