#ifndef __DATABASE_H_
#define __DATABASE_H_

#pragma warning (disable:4786)	//Disable warning about name truncated to 255 chars in debug info

#include <string>

#include "datafile.h"
#include "..\Params.h"
#include "RecordStruct.h"
#include "SearchObject.h"
#include "SearchStruct.h"
#include <map>
#include "AVLtree.h"

typedef std::map<std::string,int> Map;

class SearchObject;
class tree;
class datafile;
class TermRecords;

class FieldInfo
{
public:
	FieldInfo() : _SearchObjectPtr(0) {}
	SearchObject *	_SearchObjectPtr;
	tree *			_treePtr;
};

class database
{
public:
	database() : _datafile(0), _searchObject(0) {};
	~database();
	database(const database &rhs);
	database& operator=(const database &rhs);
	datafile * GetDataFile () const { return _datafile; }
	bool GetInitStatus () const { return _initialised; }
	void NewDataFile(std::vector<TREETYPE> &fieldtypes,
					 std::vector<std::string> &fieldnames);
	bool IsDataFileOpen() const;
	void CloseDataFile();
	TREETYPE GetTypeArray(int index);
	TREETYPE * GetTypeArray();
	std::string GetTheTypeArray(int index);
	int GetNumberofFields() const;
	void AddRecord(std::vector<std::string> stringvector);
	int GetNumberofRecords() const;
	void ShowRecord(RecordStruct::recordstruct & testrec);
	std::string GetFieldName(int fieldnum) const;
	void MakeSearchObject(std::string msg);
	void DestroySearchObject();
	std::map<std::string, int> database::GetFieldNameMap() const
	{
		return _fieldNameMap;
	}
	void Search(TermRecords &searchRecords);
	void RemoveRecord(int toremove);
	
	static DWORD WINAPI SearchThreadProc(LPVOID data);
	template <typename T>
	void RecordTally(SearchStruct<T> &tempstruct);
	void ProcessOperators(TermRecords &searchRecords);
	void RemoveDuplicatesAndSort(TermRecords &searchRecords);	
private:


	bool			_initialised;
	datafile		*_datafile;
	SearchObject	*_searchObject;
	Map				_fieldNameMap;
	HANDLE			*_threadHandle;
	DWORD			*_threadId;
	int				_numOfSearchFields;
};

#endif