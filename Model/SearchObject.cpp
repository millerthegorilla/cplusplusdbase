#include "SearchObject.h"
#include "Exception.h"

SearchObject::~SearchObject()
{
	delete [] _termRecords;

	//close mutex
	CloseHandle(_myMutex);

	SearchStruct<std::string> * tempstring = 0;
	SearchStruct<int> * tempint = 0;
	SearchStruct<float> * tempfloat = 0;
	SearchStruct<char> * tempchar = 0;

	SStruct *	tempSStruct = 0;
	for(int i = 0; i < _searchStructs.size(); i ++)
	{
		tempSStruct =  _searchStructs[i];
		if((tempstring = dynamic_cast<SearchStruct<std::string>*>(tempSStruct)) == NULL)
		{
			if((tempint = dynamic_cast<SearchStruct<int>*>(tempSStruct)) == NULL)
			{
				if((tempchar = dynamic_cast<SearchStruct<char>*>(tempSStruct)) == NULL)
				{
					if((tempfloat = dynamic_cast<SearchStruct<float>*>(tempSStruct)) == NULL)
					{
						std::cout << "error";
					}
					else
					{
						delete tempfloat;
						tempfloat = 0;
					}
				}
				else
				{
					delete tempchar;
					tempchar = 0;
				}
			}
			else
			{
				delete tempint;
				tempint = 0;
			}
		}
		else
		{
			delete tempstring;
			tempstring = 0;
		}
		tempSStruct = 0;
	}
	_searchStructs.clear();
}

SearchObject::SearchObject(std::string msg, database &dbase) : _database(dbase)
{
	//create Mutex
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = FALSE;

	_myMutex = CreateMutex(&sa,FALSE,"MYMUTEX");
	//extract tokens and put them in tokenVector
	char tokens[] = " ";
	char * token;
	std::vector<std::string> tokenVector;
	
	char * mesg = new char[msg.length() + 1];
	for(int i= 0; i<msg.length(); i++)
	{
		mesg[i] = msg[i];
	}
	mesg[msg.length()] = 0;

	int numoftokens = 0;
	token = strtok(mesg,tokens);
	while(token != NULL)
	{
		tokenVector.push_back(token);
		token = strtok(NULL,tokens);
		
		numoftokens++;
	}
	//done extracting tokens
	delete mesg;
	int inindex = 0;
	int fieldnum = 0;
	int searchTermNumber = 0;
	int searchTermVectorIndex;

	while(1)
	{
		//find IN
		int structindex = -1;
		while(inindex < tokenVector.size() && tokenVector[inindex] != "IN")
		{
			inindex++;
		}
		if(inindex == tokenVector.size())
		{
			break;
		}
		//get field number
		if(tokenVector[inindex + 1] == "FIELDNAME")
		{
			fieldnum = GetFieldNum(StripQuotes(tokenVector[inindex + 2]));
		}
		else
		{
			fieldnum = atoi(tokenVector[inindex + 2].c_str());
			if(fieldnum == 0)
			{
				throw Win::Exception ("Error in SearchString. Check FieldNumber");
			}
		}
		
		fieldnum = fieldnum - 1;

		//search searchstructs for existing field number,
		//if it exists set structindex to that fields index into 
		//searchstructs
		for(int i = 0; i < _searchStructs.size(); i++)
		{
			if(fieldnum == _searchStructs[i]->_fieldNumber)
			{
				structindex = i;
				break;
			}
		}
		if(structindex == -1) //if the field doesn't already exist
		{	

			switch(_database.GetTypeArray(fieldnum))
			{
			case STRINGTYPE:
				{
					SearchStruct<std::string> * temp = new SearchStruct<std::string>;
					_searchStructs.push_back(temp);
				}
				break;
			case INTTYPE:
				{
					SearchStruct<int> *temp = new SearchStruct<int>;
					_searchStructs.push_back(temp);
				}
				break;
			case CHARTYPE:
				{
					SearchStruct<char> *temp = new SearchStruct<char>;
					_searchStructs.push_back(temp);
				}
				break;
			case FLOATTYPE:
				{
					SearchStruct<float> *temp = new SearchStruct<float>;
					_searchStructs.push_back(temp);
				}
				break;
			case TYPEERROR:
				{
					throw Win::Exception ("TypeError 1 in SearchObject Constructor");
				}
			}
		_searchStructs.back()->_fieldNumber = fieldnum;
		structindex = _searchStructs.size() - 1; //structindex is zero based
		}
		else
		{
			_searchStructs[structindex]->_fieldNumber = fieldnum;
		}

        //check for NOT and add term
		switch(_database.GetTypeArray(fieldnum))
		{
		case STRINGTYPE:
			{
				//AVLtree<std::string> * temp = dynamic_cast<AVLtree<std::string>*>(*fptr);
				SearchStruct<std::string> * temp = dynamic_cast<SearchStruct<std::string>*>(_searchStructs[structindex]);
				temp->AddSearchTerm ();
				if(inindex >= 2)
				{
					if(tokenVector[inindex - 2] == "NOT")
					{
					temp->_searchTermVector.back()->_not = true;
					}
				}
				temp->_searchTermVector.back()->_term = StripQuotes(tokenVector[inindex - 1]);
				searchTermVectorIndex = temp->_searchTermVector.size();
			}
			break;
		case INTTYPE:
			{
				SearchStruct<int> * temp = dynamic_cast<SearchStruct<int>*>(_searchStructs[structindex]);
				temp->AddSearchTerm ();
				if(inindex >= 2)
				{
					if(tokenVector[inindex - 2] == "NOT")
					{
						temp->_searchTermVector.back()->_not = true;
					}
				}
				temp->_searchTermVector.back()->_term = atoi(tokenVector[inindex - 1].c_str());
				searchTermVectorIndex = temp->_searchTermVector.size();
			}
			break;
		case CHARTYPE:
			{
				SearchStruct<char> * temp = dynamic_cast<SearchStruct<char>*>(_searchStructs[structindex]);
				temp->AddSearchTerm ();
				if(inindex >= 2)
				{
					if(tokenVector[inindex - 2] == "NOT")
					{
						temp->_searchTermVector.back()->_not = true;
					}
				}
				temp->_searchTermVector.back()->_term = StripQuotes(tokenVector[inindex - 1]).c_str()[0];
				searchTermVectorIndex = temp->_searchTermVector.size();
			}
			break;
		case FLOATTYPE:
			{
				SearchStruct<float> * temp = dynamic_cast<SearchStruct<float>*>(_searchStructs[structindex]);
				temp->AddSearchTerm ();
				if(inindex >= 2)
				{
					if(tokenVector[inindex - 2] == "NOT")
					{
						temp->_searchTermVector.back()->_not = true;
					}
				}
				temp->_searchTermVector.back()->_term = atof(tokenVector[inindex - 1].c_str());
				searchTermVectorIndex = temp->_searchTermVector.size();
			}
			break;
		}

		//push back operator if exists
		if((inindex + 3) < tokenVector.size())
		{
			_operatorVector.push_back(tokenVector[inindex + 3]);
		}
		
		_searchStructs[structindex]->_searchTermNumber.push_back(searchTermNumber);
		
		
		_searchTermMap.insert(termMap::value_type (searchTermNumber,MAKELONG(structindex, searchTermVectorIndex)));

		searchTermNumber ++;
		inindex++;
	}
	_termRecords = new TermRecords[searchTermNumber];
}

std::string SearchObject::StripQuotes(std::string & term)
{	
	std::string temp;
	for(int i = 1; i < term.length() - 1; i++)
	{
		temp = temp + term[i];
	}
	return temp;
}

int SearchObject::GetFieldNum(std::string fieldname)
{
	int cmdIndex = -1;
	Map::const_iterator iter = _database.GetFieldNameMap().find (fieldname);
	if (iter != _database.GetFieldNameMap().end ())
		cmdIndex = iter->second;
	return cmdIndex;
}

SStruct * SearchObject::GetSearchStruct (int fieldnum)
{

	for(int i = 0; i<_searchStructs.size(); i++)
	{ 
		if(fieldnum == _searchStructs[i]->_fieldNumber)
		{
			return _searchStructs[i];
		}
	}

	return NULL;
}
//could have used stl algorithm functions for AND and OR 
//(set_intersection and set_union functions)
void SearchObject::And(TermRecords & resultRecords, TermRecords termone, TermRecords termtwo)
{
	for(int i = 0; i < termone._recordNumbers.size(); i++)
	{
		for(int j = 0; j < termtwo._recordNumbers.size(); j++)
		{
			if(termone._recordNumbers[i] == termtwo._recordNumbers[j])
			{
				resultRecords._recordNumbers.push_back(termone._recordNumbers[i]);
			}
		}
	}
}

void SearchObject::Or(TermRecords & resultRecords, TermRecords termone, TermRecords termtwo)
{
	for(int i = 0; i < termone._recordNumbers.size(); i++)
	{
		resultRecords._recordNumbers.push_back(termone._recordNumbers [i]);
	}
	
	bool found = false;

	for(i = 0; i < termtwo._recordNumbers.size(); i++)
	{
		found = false;

		for(int j = 0; j < termone._recordNumbers.size(); j++)
		{
			if(termtwo._recordNumbers[i] == termone._recordNumbers[j])
			{
				found = true;
			}
		}
		if(!found)
		{
			resultRecords._recordNumbers.push_back(termtwo._recordNumbers[i]);
		}
	}
}