#if !defined(SEARCHOBJECT_H)
#define SEARCHOBJECT_H

#pragma warning (disable:4786)

#include "database.h"
#include "SearchStruct.h"
#include <string>
#include <vector>
#include <windows.h>
#include <map>

typedef std::map<int,DWORD> termMap;

class TermRecords
{
public:
	std::vector<int> _recordNumbers;
};

class database;

class SearchObject
{
public:
	SearchObject(std::string msg, database &dbase);
	~SearchObject();
	
	std::string StripQuotes(std::string &term);
	int GetFieldNum(std::string fieldname);
	SStruct * GetSearchStruct(int fieldnum);
	SStruct * GetSStructByIndex(int index) const {return _searchStructs[index];}
	int GetSearchStructsSize() const {return _searchStructs.size();}
	int GetFieldNum(int index) {return _searchStructs[index]->_fieldNumber;}
	HANDLE GetMutex () const { return _myMutex;}
	TermRecords * GetTermRecords() const { return _termRecords; }
	void And(TermRecords & resultRecords, TermRecords termone, TermRecords termtwo);
	void Or(TermRecords & resultRecords, TermRecords termone, TermRecords termtwo);
	std::vector<std::string> GetOperatorVector() const { return _operatorVector;}
private:
	database &_database;
	std::vector<std::string> _operatorVector;
	std::vector<SStruct *>  _searchStructs;
	termMap					_searchTermMap;
	TermRecords				*_termRecords;
	HANDLE	_myMutex;
};
#endif