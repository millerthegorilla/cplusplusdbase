#include "RecordStruct.h"

using namespace RecordStruct;

recordstruct::recordstruct(int begin, int end) : _recordBegin(begin),
												 _recordEnd(end)
{
	_numOfRecords = end - begin;
	if(_numOfRecords)
	{
		_therecords = new record [end - begin + 1];
	}
	else
	{
		_therecords = new record;
	}
}

recordstruct::~recordstruct ()
{
	if(_numOfRecords)
	{
		delete [] _therecords;
	}
	else
	{
		delete _therecords;
	}
}

void recordstruct::SetRecordNum(int recordnum)
{
	_numOfRecords = 0;
	_recordBegin = recordnum;
	_recordEnd = recordnum;
	_therecords = new record;
}
void recordstruct::AddField(int recordnum, std::string val)
{
	if(_numOfRecords)
	{
		_therecords[recordnum - _recordBegin].fieldvector.push_back(val);
	}
	else
	{
		_therecords->fieldvector.push_back(val);
	}
}

std::string recordstruct::GetField (int recordnum, int fieldnum)
{
	if(_numOfRecords)
	{
		return _therecords[recordnum - _recordBegin].fieldvector[fieldnum];
	}
	else
	{
		return _therecords->fieldvector[fieldnum];
	}
}