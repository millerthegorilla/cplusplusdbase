#if !defined (RECORDSTRUCT_H)
#define RECORDSTRUCT_H


#pragma warning (disable:4786) 

#include <strstream>
#include <iostream>
#include <string>

template <class T>
std::string ToString(const T &val)
{
	std::strstream out;
	out << val;
	return out.str();
}


class record
{
public:
	std::vector<std::string> fieldvector;
};

class recordstruct
{
public:
	recordstruct(int begin, int end);
	~recordstruct();
	void AddField(int recordnum, std::string val);
	int GetNumofRecords() const { return _numOfRecords; }
	std::string GetField(int recordnum, int fieldnum);
private:
	int		_recordBegin;
	int		_recordEnd;
	int		_numOfRecords;
	record * _therecords;

};

recordstruct::recordstruct(int begin, int end) : _recordBegin(begin),
												 _recordEnd(end)
{
	_numOfRecords = end - begin;
	if(_numOfRecords)
	{
		_therecords = new record [end - begin];
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


void recordstruct::AddField(int recordnum, std::string val)
{
	if(_numOfRecords)
	{
		_therecords[recordnum].fieldvector.push_back(val);
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
		return _therecords[recordnum].fieldvector[fieldnum];
	}
	else
	{
		return _therecords->fieldvector[fieldnum];
	}
}

#endif