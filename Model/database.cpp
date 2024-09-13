#include "database.h"
#include <assert.h>
#include <algorithm>

database::~database ()
{
	delete _datafile;
		
	if(_searchObject)
	{
		if(_threadHandle)
		{	
			WaitForMultipleObjects(_numOfSearchFields,     // number of threads to wait for							   _threadHandle,   
									_threadHandle,	// handles to threads
								   TRUE,            // wait for all?
								   INFINITE);

			for (int index=0; index<_numOfSearchFields; index++)
			{
				CloseHandle(_threadHandle[index]);
			}
			
			delete [] _threadHandle;
			_threadHandle = 0;
		}

		delete _searchObject;
		_searchObject = 0;
	}
}

database::database (const database &rhs)
{
	_datafile = rhs.GetDataFile ();
	_initialised = rhs.GetInitStatus ();
}

database& database::operator=(const database &rhs)
{
	if(this == &rhs)
	{
		return *this;
	}

	_datafile = rhs.GetDataFile ();
	_initialised = rhs.GetInitStatus ();

	return *this;
}

void database::NewDataFile (std::vector<TREETYPE> &fieldtypes,
							std::vector<std::string> &fieldnames)
{
	if(!_datafile)
	{
		_datafile = new datafile;
		_datafile->initialise (fieldtypes, fieldnames);
		for(int i =0; i < fieldnames.size(); i++)
		{
			_fieldNameMap.insert (Map::value_type (fieldnames[i], i));
		}
	}

}

bool database::IsDataFileOpen () const
{
	if(_datafile)
	{
		return true;
	}
	return false;
}

void database::CloseDataFile ()
{
	delete _datafile;
	_datafile = 0;
}

TREETYPE database::GetTypeArray (int index)
{
	if(_datafile)
	{
		return _datafile->gettypearray(index);
	}
	else
	{
		return TYPEERROR;
	}
}

TREETYPE * database::GetTypeArray ()
{
	if(_datafile)
	{
		return _datafile->getthetypearray();
	}
	else
	{
		return 0;
	}
}

std::string database::GetTheTypeArray (int index)
{
	switch(GetTypeArray(index))
	{
	case STRINGTYPE:
		return "String";
		break;
	case INTTYPE:
		return "Integer";
		break;
	case CHARTYPE:
		return "Character";
		break;
	case FLOATTYPE:
		return "Float";
		break;
	case TYPEERROR:
		return 0;
		break;
	default:
		return 0;
		break;
	}
}

int database::GetNumberofFields () const
{
	if(_datafile)
	{
		return _datafile->getnumberoffields();
	}
	else
	{
		return 0;
	}
}

void database::AddRecord (std::vector<std::string> stringvector)
{
	if(_datafile)
	{
		_datafile->newrecord(stringvector);
	}
}

int database::GetNumberofRecords () const
{
	if(_datafile)
	{
		return _datafile->getnumberofrecords();
	}
	return 0;
}

void database::ShowRecord (RecordStruct::recordstruct &testrec)
{
	if(_datafile)
	{
		if(testrec.GetNumofRecords ())
		{
			for(int i = testrec.GetFirst (); i <= testrec.GetLast() ; i ++)//cache these
			{
				if(!_datafile->showrecord(testrec, i))
				{
					//throw exception
					;
				}
			}
		}
		else
		{
			if(!_datafile->showrecord(testrec, testrec.GetFirst ()))
			{
				//throw exception
				;
			}
		}
	}
}

void database::MakeSearchObject(std::string msg)
{
	_searchObject = new SearchObject(msg, *this);	
}

void database::DestroySearchObject()
{
	if(_searchObject)
	{
		if(_threadHandle)
		{	
			WaitForMultipleObjects(_numOfSearchFields,     // number of threads to wait for							   _threadHandle,   
									_threadHandle,	// handles to threads
								   TRUE,            // wait for all?
								   INFINITE);

			for (int index=0; index<_numOfSearchFields; index++)
			{
				CloseHandle(_threadHandle[index]);
			}
			
			delete [] _threadHandle;
			_threadHandle = 0;
		}

		delete _searchObject;
		_searchObject = 0;
		
	}
}

void database::Search (TermRecords & searchRecords)
{
	int i;

	_numOfSearchFields = _searchObject->GetSearchStructsSize();	
	
	assert(_searchObject != 0);
	assert(_datafile != 0);
	//this function creates searchthreads.
	//each searchthread proc is passed a reference to
	//searchobject and pointer to appropriate tree.
	//searchthread proc dynamic_casts tree to appropriate
	//type before calling search and passing it 
	//reference to search object
	//search function calls searchobject->getsearchstruct with
	//it's field_num

	_threadHandle = new HANDLE[_numOfSearchFields];
	FieldInfo * fieldInfo = new FieldInfo[_numOfSearchFields];
	_threadId = new DWORD[_numOfSearchFields];
	
	for(i = 0; i< _numOfSearchFields; i++)
	{
		fieldInfo[i]._SearchObjectPtr = _searchObject;
		int fnum = _searchObject->GetFieldNum(i);
		fieldInfo[i]._treePtr = _datafile->getfieldptr(fnum);

		_threadHandle[i] = CreateThread(NULL,
										0,
										database::SearchThreadProc,
										(LPVOID)&fieldInfo[i],
										0,
										&_threadId[i]);

	}

	WaitForMultipleObjects(_numOfSearchFields,     // number of threads to wait for
						   _threadHandle,   // handles to threads
						   TRUE,            // wait for all?
						   INFINITE);

	for(i = 0; i < _searchObject->GetSearchStructsSize(); i++)
	{
		SStruct * temp = _searchObject->GetSStructByIndex(i);

		switch(_datafile->gettypearray(temp->_fieldNumber ))
		{
		case STRINGTYPE:
			{
				SearchStruct<std::string> * tempString = \
					dynamic_cast<SearchStruct<std::string>*>(temp);
				RecordTally(*tempString);
			}
			break;
		case INTTYPE:
			{
				SearchStruct<int> * tempInt = \
					dynamic_cast<SearchStruct<int>*>(temp);
				RecordTally(*tempInt);
			}
			break;
			case CHARTYPE:
			{
				SearchStruct<char> * tempChar = \
					dynamic_cast<SearchStruct<char>*>(temp);
				RecordTally(*tempChar);
			}
			break;
			case FLOATTYPE:
			{
				SearchStruct<float> * tempFloat = \
					dynamic_cast<SearchStruct<float>*>(temp);
				RecordTally(*tempFloat);
			}
			break;
		}// end switch	
	}// end for

	ProcessOperators(searchRecords);
	RemoveDuplicatesAndSort(searchRecords);
	int temprec;
	temprec = searchRecords._recordNumbers.size();
	for(i = 0; i < searchRecords._recordNumbers.size(); i++)
	{
		temprec = searchRecords._recordNumbers[i];
	}
	DestroySearchObject();
}

DWORD WINAPI database::SearchThreadProc (LPVOID data)
{
	FieldInfo *fieldInfo = reinterpret_cast <FieldInfo*>(data);
	switch(fieldInfo->_treePtr->my_type)
	{
	case STRINGTYPE:
		{
			AVLtree<std::string> * tempString = dynamic_cast<AVLtree<std::string>*>(fieldInfo->_treePtr);
			assert(tempString != NULL);
			tempString->search(*fieldInfo->_SearchObjectPtr);
			break;
		}
	case INTTYPE:
		{
			AVLtree<int> * tempInt = dynamic_cast<AVLtree<int>*>(fieldInfo->_treePtr);
			assert(tempInt != NULL);
			tempInt->search (*fieldInfo->_SearchObjectPtr );
			break;
		}
	case CHARTYPE:
		{
			AVLtree<char> * tempChar = dynamic_cast<AVLtree<char>*>(fieldInfo->_treePtr);
			assert(tempChar != NULL);
			tempChar->search (*fieldInfo->_SearchObjectPtr );
			break;
		}
	case FLOATTYPE:
		{
			AVLtree<float> * tempFloat = dynamic_cast<AVLtree<float>*>(fieldInfo->_treePtr);
			assert(tempFloat != NULL);
			tempFloat->search(*fieldInfo->_SearchObjectPtr );
			break;
		}
	}
	return (DWORD)0;
}

std::string database::GetFieldName(int fieldnum) const
{
	return _datafile->getthefieldname (fieldnum);
}

template <typename T>
void database::RecordTally(SearchStruct<T> &tempstruct)
{
	int temprec;

	for(int j = 0; j < tempstruct._searchTermVector.size(); j++)
	{
		if(tempstruct._searchTermVector[j]->_not == true)
		{
			int numofrecs = GetNumberofRecords() + 1;
			bool * tally = new bool[numofrecs];
			memset(tally,false,numofrecs);
			for(int l = 0; l < tempstruct._searchTermVector[j]->_recordNumberVector.size(); l++)
			{
				tally[tempstruct._searchTermVector[j]->_recordNumberVector[l]] = true;
			}
			for(l = 1; l < numofrecs; l++)
			{
				if(tally[l] == 0)
				{
					_searchObject->GetTermRecords()[tempstruct._searchTermNumber[j]]._recordNumbers.push_back(l);
				}
			}
			delete [] tally;
		}
		else
		{
			for(int k = 0; k < tempstruct._searchTermVector[j]->_recordNumberVector.size(); k++)
			{	
				temprec = tempstruct._searchTermVector[j]->_recordNumberVector[k];
				_searchObject->GetTermRecords()[tempstruct._searchTermNumber[j]]._recordNumbers.push_back(temprec);
			}//end of k
		}
	}// end of j
}

void database::ProcessOperators(TermRecords &searchRecords)
{
	std::vector<std::string> & operatorVector = _searchObject->GetOperatorVector();
	TermRecords * termRecords = _searchObject->GetTermRecords();
	
	if(operatorVector.size() == 0)
	{
		for(int i = 0; i < termRecords[0]._recordNumbers.size(); i++)
		{
			searchRecords._recordNumbers.push_back(termRecords[0]._recordNumbers[i]);
		}
	}
	else
	{
		for(int i = 0; i< operatorVector.size(); i ++)
		{
			if(operatorVector[i] == "AND")
			{
				if(i == 0)
				{
					_searchObject->And(searchRecords, termRecords[i], termRecords[i+1]);
				}
				else
				{
					_searchObject->And(searchRecords, searchRecords, termRecords[i+1]);
				}
			}
			else if(operatorVector[i] == "OR")
			{
				if(i == 0)
				{
					_searchObject->Or(searchRecords, termRecords[i], termRecords[i+1]);
				}
				else
				{
					_searchObject->Or(searchRecords, searchRecords, termRecords[i+1]);
				}
			}
		}//end for
	}//end if
}

void database::RemoveDuplicatesAndSort(TermRecords &searchRecords)
{
	std::vector<int>::iterator begin, end;

	begin = searchRecords._recordNumbers.begin();
	end = searchRecords._recordNumbers.end();
	
	std::sort(begin,end);
	end = std::unique(begin,end);
}

void database::RemoveRecord (int toremove)
{
	_datafile->removerecord(toremove);
}
