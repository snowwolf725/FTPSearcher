#ifndef REMOTOFILEPARSER_H_
#define REMOTOFILEPARSER_H_

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "include/CkFtp2.h"
#include "include/CkString.h"
#include "include/CkStringArray.h"
#include "include/mysql_connection.h"
#include "include/mysql_driver.h"
//#include "cppconn/statement.h"
//#include <driver/mysql_public_iface.h>
#include "Parser.h"

using namespace std;

class RemotoFileParser {
public:
	RemotoFileParser();
	~RemotoFileParser();
	void parse();
	void parseDirectory(ofstream& outfile);
	void reconnectFTP();
	void insertToDatabase(string stmtAttribute, ofstream& outfile, int docid);
private:
	CkFtp2* _ftp;
	int _docid;
	int _parentid;
	//sql::Connection* _con;
	//sql::Driver* _driver;
	//sql::PreparedStatement*	_stmt;
};


#endif /* REMOTOFILEPARSER_H_ */
