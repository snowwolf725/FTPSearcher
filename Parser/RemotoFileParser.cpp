#include "RemotoFileParser.h"
const string FILE_PATH = "ftp://ir:ir@140.124.181.200";
const string SQL_INSERT = "INSERT INTO index_table(id, parentid, name, extName, path, size, date, is_folder) VALUES ";

RemotoFileParser::RemotoFileParser() {
	_ftp = new CkFtp2();
	_docid = 1;
	_parentid = 0;
	//DB	
	//_driver = get_driver_instance();
	//cout << "START CONNECTED" << endl;
	//_con = _driver->connect("tcp://127.0.0.1:3306", "soriel", "dianna");
	//cout << "CONNECTED OVER" << endl;
	//_stmt = _con->prepareStatement("INSERT INTO index_table(name, sub, path, size, date, is_folder) VALUES (?, ?, ?, ?, ?, ?)");
}

RemotoFileParser::~RemotoFileParser() {
	delete _ftp;
	//delete _stmt;
	//delete _con;	
}

void RemotoFileParser::parse() {
	bool success;

	success = _ftp->UnlockComponent("anything works for 30-day trial");
	if(!success) {
		cout << _ftp->lastErrorText() << endl;
		return;
	}

	_ftp->put_Hostname("140.124.181.200");
	_ftp->put_Username("ir");
	_ftp->put_Password("ir");

	success = _ftp->Connect();
	if(!success) {
		cout << _ftp->lastErrorText() << endl;
		return;
	}	
	ofstream outfile;
	outfile.open("Listing.txt");
	if(!outfile){
		outfile.close();
		return;
	}

	//cout << _ftp->listPattern() << endl;
	_ftp->put_ListPattern("*");

	int number = _ftp->get_NumFilesAndDirs();

	if(number < 0) {
		cout << _ftp->lastErrorText() << endl;
		return;
	}
	//string stopWord = "CPAN";
	//string stopWord2 = "linux";

	FILETIME fTime;
    SYSTEMTIME sysTime;
    CkString str;
	CkString dir;

	if(number > 0) {
		for(int index = 0; index < number; index++, _docid++) {
			stringstream pathTemp;
			string path;
			_ftp->GetCurrentRemoteDir(dir);	
			_ftp->GetFilename(index, str);

			if(str.equals(".") || str.equals(".."))
				continue;

			_ftp->GetLastModifiedTime(index,fTime);
			FileTimeToSystemTime(&fTime,&sysTime);	
			//outfile << sysTime.wHour << ":" << sysTime.wMinute << " " << sysTime.wMonth << "/" << sysTime.wDay << "/" << sysTime.wYear << " "; 
			stringstream modTimeTemp;
			modTimeTemp << sysTime.wYear << "-" << sysTime.wMonth << "-" << sysTime.wDay; 
			string modTime = modTimeTemp.str();
			
			bool isDirectory;
			stringstream sqlStmt;
			string stmt;
			if(_ftp->GetIsDirectory(index)) {
				_parentid = _docid;
				isDirectory = true;
				pathTemp << FILE_PATH << dir.getUtf8() << str.getUtf8();
				path = pathTemp.str();
				sqlStmt << "(" << _docid << "," << _parentid << ", \"" << str.getUtf8() << 	"\", \"\", \"" << path << "\", " << _ftp->GetSize(index) << ", \"" << 	modTime << "\", " << isDirectory << ")";	
				stmt = sqlStmt.str();
				//outfile << path << "," << str.getUtf8() << "," << "" << "," << modTime << "," << isDirectory << endl << flush;
				//outfile << "[directory]" << endl << flush;
				//if(str.getUtf8() != stopWord && str.getUtf8() != stopWord2) {
					insertToDatabase(stmt, outfile, _docid);
					_ftp->ChangeRemoteDir(str.getAnsi());
					parseDirectory(outfile);
					_ftp->ChangeRemoteDir("/");
					reconnectFTP();
					cout << "ONE DIRECTORY [" << str.getUtf8() << "] COMPLETE." << endl;
				//}								
				//directory.push_back(str.getString());
			}
			else {
				isDirectory = false;
				pathTemp << FILE_PATH << dir.getUtf8() << str.getUtf8();
				path = pathTemp.str();
				CkStringArray* array;
				array = str.split('.', false, true, false);	
				string temp;
				if(array->get_Count() > 1) {
					temp = array->lastStr();
					sqlStmt << "(" << _docid << "," << _parentid << ", \"" << str.getUtf8() << 	"\", \"" << temp << "\", \"" << path << "\", " << _ftp->GetSize(index) << ", \"" << 	modTime << "\", " << isDirectory << ")";
				}
				else {
					//temp = "";
					sqlStmt << "(" << _docid << "," << _parentid << ", \"" << str.getUtf8() << 	"\", \"\" , \"" << path << "\", " << _ftp->GetSize(index) << ", \"" << 	modTime << "\", " << isDirectory << ")";
				}
				array->Clear();
				//cout << temp << endl;
				//outfile << endl << flush;
				stmt = sqlStmt.str();
				insertToDatabase(stmt, outfile, _docid);
				//outfile << path << "," << str.getUtf8() << "," << temp << "," << modTime << "," << isDirectory << endl << flush;

				// download .txt file and parser it
				if(str.endsWith("txt"))
				{
					CkString fullpath, localpath;
					fullpath.append(dir);
					fullpath.append("/");
					fullpath.append(str);
					localpath.append("dl/");
					localpath.append(str);
					cout << fullpath << endl;
					_ftp->GetFile(fullpath ,localpath);

					// parser text file
					Parser parser;
					parser.parse(localpath.getString(), _docid);
				}
			}
			//cout << "---" << endl;
		}
	}

	_ftp->Disconnect();	
}

void RemotoFileParser::parseDirectory(ofstream& outfile) {
	int number;
	number = _ftp->get_NumFilesAndDirs();
	if(number < 0) {
		cout << _ftp->lastErrorText() << endl;
		return;
	}	

	//cout << number << endl;

	FILETIME fTime;
    SYSTEMTIME sysTime;
    CkString str;
	CkString dir;

	if(number > 0) {
		for(int index = 0; index < number; index++, _docid++) {
			stringstream pathTemp;
			string path;
			_ftp->GetCurrentRemoteDir(dir);	
			_ftp->GetFilename(index, str);			

			// skip . or ..
			if(str.equals(".") || str.equals(".."))
				continue;

			_ftp->GetLastModifiedTime(index,fTime);
			FileTimeToSystemTime(&fTime,&sysTime);	
			//outfile << sysTime.wHour << ":" << sysTime.wMinute << " " << sysTime.wMonth << "/" << sysTime.wDay << "/" << sysTime.wYear << " "; 
			stringstream modTimeTemp;
			modTimeTemp << sysTime.wYear << "-" << sysTime.wMonth << "-" << sysTime.wDay; 
			string modTime = modTimeTemp.str();
			
			bool isDirectory;
			stringstream sqlStmt;
			string stmt;
			if(_ftp->GetIsDirectory(index)) {				
				CkString newdir;
				cout << dir << endl;
				_parentid = _docid;
				isDirectory = true;
				pathTemp << FILE_PATH << dir.getUtf8() << "/" << str.getUtf8();
				path = pathTemp.str();
				sqlStmt << "(" << _docid << "," << _parentid << ", \"" << str.getUtf8() << 	"\", \"\" , \"" << path << "\", " << _ftp->GetSize(index) << ", \"" << 	modTime << "\", " << isDirectory << ")";	
				stmt = sqlStmt.str();
				insertToDatabase(stmt, outfile, _docid);
				//outfile << path << "," << str.getUtf8() << "," << "" << "," << modTime << "," << isDirectory << endl << flush;
				//outfile << "[directory]" << endl << flush;				
				_ftp->ChangeRemoteDir(str.getAnsi());
				
				_ftp->GetCurrentRemoteDir(newdir);
				if(newdir.equals(dir))
					continue;
				cout << str <<endl;
				parseDirectory(outfile);
				_ftp->ChangeRemoteDir("..");
				
			}
			else {
				isDirectory = false;
				pathTemp << FILE_PATH << dir.getUtf8() << "/" << str.getUtf8();
				path = pathTemp.str();
				CkStringArray* array;
				array = str.split('.', false, true, false);	
				string temp;
				if(array->get_Count() > 1) {
					temp = array->lastStr();
					sqlStmt << "(" << _docid << "," << _parentid << ", \"" << str.getUtf8() << 	"\", \"" << temp << "\", \"" << path << "\", " << _ftp->GetSize(index) << ", \"" << 	modTime << "\", " << isDirectory << ")";
				}
				else {
					//temp = "";
					sqlStmt << "(" << _docid << "," << _parentid << ", \"" << str.getUtf8() << 	"\", \"\" , \"" << path << "\", " << _ftp->GetSize(index) << ", \"" << 	modTime << "\", " << isDirectory << ")";
				}
				array->Clear();				
				//outfile << endl << flush;
				stmt = sqlStmt.str();
				insertToDatabase(stmt, outfile, _docid);
				//outfile << path << "," << str.getUtf8() << "," << temp << "," << modTime << "," << isDirectory << endl << flush;
				
				// download .txt file and parser it
				if(str.endsWith("txt"))
				{
					CkString fullpath, localpath;
					fullpath.append(dir);
					fullpath.append("/");
					fullpath.append(str);
					localpath.append("dl/");
					localpath.append(str);
					cout << fullpath << endl;
					_ftp->GetFile(fullpath ,localpath);

					// parser text file
					Parser parser;
					parser.parse(localpath.getString(), _docid);
				}
			}			
			//cout << "---" << endl;
		}
	}

}

void RemotoFileParser::reconnectFTP() {
	_ftp->Disconnect();
	bool success;
	success = _ftp->Connect();
	if(!success) {
		cout << _ftp->lastErrorText() << endl;
		return;
	}
}

void RemotoFileParser::insertToDatabase(string stmtAttribute, ofstream& outfile, int docid) {
	stringstream temp;
	temp << SQL_INSERT << stmtAttribute << ";";
	string insert = temp.str();

	outfile << insert << endl;

	//sql::Statement*	stmt;
	//stmt = _con->createStatement();
	//stmt->execute("USE ir");
	//stmt->execute(insert);
	
	//delete stmt;
}
