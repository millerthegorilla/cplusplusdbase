#if !defined (RECORDSTRUCT_H)
#define RECORDSTRUCT_H


#pragma warning (disable:4786) 

#include <strstream>
#include <iostream>
#include <string>
#include <vector>

namespace RecordStruct
{
	class record
	{
	public:
		std::vector<std::string> fieldvector;
	};

	class recordstruct
	{
	public:
		recordstruct(){};
		recordstruct(int begin, int end);
		~recordstruct();
		void SetRecordNum(int recordnum);
		void AddField(int recordnum, std::string val);
		int GetNumofRecords() const { return _numOfRecords; }
		int GetFirst() const { return _recordBegin; }
		int GetLast() const { return _recordEnd; }
		std::string GetField(int recordnum, int fieldnum);
	private:
		int		_recordBegin;
		int		_recordEnd;
		int		_numOfRecords;
		record * _therecords;

	};

}

#endif