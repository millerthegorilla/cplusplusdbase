#include "datafile.h"
#include "Util.h"
#include "Exception.h"
// Function name	: datafile constructor
// Description	    : 
// Return type		: none
datafile::datafile()
{
	numberoffields = 0;
	field_ptr = 0;
	type_array = 0;
}

///////////////////////////////////////////////////////////////
//  Destructor: deletes field_ptr (pointers to fields) and type_array
//              (array of integers specifying field type info)
//
///////////////////////////////////////////////////////////////
datafile::~datafile ()
{
	if(field_ptr)
	{
		delete [] field_ptr;
	}
	if(type_array)
	{
		delete [] type_array;
	}

	std::vector<Records::record *>::iterator iter;
	for(iter = therecords.begin(); iter != therecords.end(); ++iter)
	{
		delete *iter;
	}
	therecords.erase(therecords.begin(), therecords.end());
}

datafile::datafile(const datafile &rhs)
{
	type_array = rhs.getthetypearray ();
	numberoffields = rhs.getnumberoffields ();
	therecords = rhs.gettherecords ();
	field_ptr = rhs.getthefieldptr ();

}

datafile & datafile::operator = (const datafile &rhs)
{
	if(this == &rhs)
	{
		return *this;
	}

	type_array = rhs.getthetypearray ();
	numberoffields = rhs.getnumberoffields ();
	therecords = rhs.gettherecords ();
	field_ptr = rhs.getthefieldptr ();

	return *this;
}

TREETYPE datafile::gettypearray(int index)
{
	return type_array[index];
}

////////////////////////////////////////////////////////////////////
//                                                                 /
//  Method to initialise the datafile.                             /
//  Parameters: numberoffields and an array of types corresponding /
//	to the types of data each field accepts                        /
//  
//  Throws : badcastexception                                                        /
////////////////////////////////////////////////////////////////////
void datafile::initialise( std::vector<TREETYPE> &typearray,
						  std::vector<std::string> &fieldnames)
{
	tree ** fptr;
	numberoffields = typearray.size();
	field_ptr = new tree*[numberoffields];
	type_array = new TREETYPE[numberoffields];
	fptr = field_ptr;

	for(int i =0; i<numberoffields; i++)
	{
		type_array[i] = typearray[i];
		if(type_array[i] == STRINGTYPE)
		{
			*fptr = new AVLtree<std::string>;
			AVLtree<std::string> * temp = dynamic_cast<AVLtree<std::string>*>(*fptr);
			if(!temp)
			{
				std::cout << "Error.  Exception at line " << __LINE__ << "in file " << __FILE__;
				throw badcastexception();
			}
			temp->SetFieldNum (i);
			temp->SetFieldName (fieldnames[i]);
		}
		else if(type_array[i] == INTTYPE)
		{
			*fptr = new AVLtree<int>;
			AVLtree<int> * temp = dynamic_cast<AVLtree<int>*>(*fptr);
			if(!temp)
			{
				std::cout << "Error.  Exception at line " << __LINE__ << "in file " << __FILE__;
				throw badcastexception();
			}
			temp->SetFieldNum (i);
			temp->SetFieldName (fieldnames[i]);
		}
		else if(type_array[i] == CHARTYPE)
		{
			*fptr = new AVLtree<char>;
			AVLtree<char> * temp = dynamic_cast<AVLtree<char>*>(*fptr);
			if(!temp)
			{
				std::cout << "Error.  Exception at line " << __LINE__ << "in file " << __FILE__;
				throw badcastexception();
			}
			temp->SetFieldNum (i);
			temp->SetFieldName (fieldnames[i]);
		}
		else if(type_array[i] == FLOATTYPE)
		{
			*fptr = new AVLtree<float>;
			AVLtree<float> * temp = dynamic_cast<AVLtree<float>*>(*fptr);
			if(!temp)
			{
				std::cout << "Error.  Exception at line " << __LINE__ << "in file " << __FILE__;
				throw badcastexception();
			}
			temp->SetFieldNum (i);
			temp->SetFieldName (fieldnames[i]);
		}
		
		fptr++;
	}
}


// Function name	: datafile::newrecord
// Description	    : asks user for data prompting for correct type
//					  and adds it to tree.
// Return type		: void 
// Throws           : badcastexception
void datafile::newrecord()
{
	AVLtree<std::string> * avlstringptr;
	AVLtree<int> * avlintptr;
	AVLtree<char> * avlcharptr;
	AVLtree<float> * avlfloatptr;
	tree ** fptr = field_ptr;
    	//if field_ptr = 0 then exception "not initialised";
	Records::record * temp = new Records::record(numberoffields);
	
	if (therecords.size())
	{
		temp->setrecordnumber (therecords.back()->getrecordnumber() + 1);
	}
	else
	{
		temp->setrecordnumber (1);
	}

	//now ask punter to enter data and add data to and record to tree
	for(int j = 0; j < numberoffields; j++)
	{
		avlstringptr = dynamic_cast<AVLtree<std::string>*>(*fptr);
		if(!avlstringptr)
		{
			avlintptr = dynamic_cast<AVLtree<int>*>(*fptr);
			if(!avlintptr)
			{
				avlcharptr = dynamic_cast<AVLtree<char>*>(*fptr);
				if(!avlcharptr)
				{
					avlfloatptr = dynamic_cast<AVLtree<float>*>(*fptr);
					if(!avlfloatptr)
					{
						std::cout << "Error.  Exception at line " << __LINE__ << "in file " << __FILE__;
						throw badcastexception();
					}
					else
					{	
						float tempf;
						std::cout << "enter data for field number " << j+1 << " (type = float)" << std::endl;
						std::cin >> tempf;//
						avlfloatptr->add_item(tempf,temp, j);
					}
				}
				else
				{
					char tempc;
					std::cout << "enter data for field number " << j+1 << " (type = char)" << std::endl;
					std::cin >> tempc;//
					avlcharptr->add_item(tempc,temp, j);
				}
			}
			else
			{
				int tempi;
				std::cout << "enter data for field number " << j+1 << " (type = int)" << std::endl;
				std::cin >> tempi;//
				avlintptr->add_item(tempi,temp, j);
			}
		}
		else
		{
			std::string temps;
			std::cout << "enter data for field number " << j+1 << " (type = string)" << std::endl;
			std::cin >> temps;//
			avlstringptr->add_item(temps,temp, j);
		}
		fptr++;
	}
	
	therecords.push_back(temp);
}

// Function name	: datafile::newrecord
// Description	    : adds records to correctly casted tree from array
//                    parameter.   Used only by load function for console program
// Return type		: void 
// Argument         : char * field_entry[]
// Throws           : badcastexception()
void datafile::newrecord(std::vector<std::string> field_entry)
{
	AVLtree<std::string> * avlstringptr;
	AVLtree<int> * avlintptr;
	AVLtree<char> * avlcharptr;
	AVLtree<float> * avlfloatptr;
	tree ** fptr = field_ptr;
    	//if field_ptr = 0 then exception "not initialised";
	Records::record * temp = new Records::record(numberoffields);
	
	if (therecords.size())
	{
		temp->setrecordnumber (therecords.back()->getrecordnumber() + 1);
	}
	else
	{
		temp->setrecordnumber (1);
	}

	//now ask punter to enter data and add data to and record to tree
	for(int j = 0; j < numberoffields; j++)
	{
		avlstringptr = dynamic_cast<AVLtree<std::string>*>(*fptr);
		if(!avlstringptr)
		{
			avlintptr = dynamic_cast<AVLtree<int>*>(*fptr);
			if(!avlintptr)
			{
				avlcharptr = dynamic_cast<AVLtree<char>*>(*fptr);
				if(!avlcharptr)
				{
					avlfloatptr = dynamic_cast<AVLtree<float>*>(*fptr);
					if(!avlfloatptr)
					{
						std::cout << "Error.  Exception at line " << __LINE__ << "in file " << __FILE__;
						throw badcastexception();
					}
					else
					{	
						float tempf = atof(field_entry[j].c_str());//
						avlfloatptr->add_item(tempf,temp, j);
					}
				}
				else
				{
					char tempc = field_entry[j][0];//
					avlcharptr->add_item(tempc,temp, j);
				}
			}
			else
			{
				int tempi = atoi(field_entry[j].c_str());
				avlintptr->add_item(tempi,temp, j);
			}
		}
		else
		{
			std::string temps = field_entry[j];//
			avlstringptr->add_item(temps,temp, j);
		}
		fptr++;
	}
	
	therecords.push_back(temp);
}


// Function name	: datafile::showrecord
// Description	    : overloaded version that uses inbuilt type 
//                    mechanism to display field contents
// Return type		: bool 
// Argument         : int dummy
// Throws           : nothing
bool datafile::showrecord(RecordStruct::recordstruct & testrec, int recordnum)
{
	int tempint;
	float tempfloat;
	char tempchar;

	int recordsize = therecords.size();

	if(!recordsize)
	{
		return false;
	}

	if(recordnum > recordsize)
	{
		return false;
	}
	
	Records::record * temp = therecords[recordnum - 1];

	tree ** fptr = field_ptr;

	for(int j = 0; j< numberoffields; j++)
	{
		switch (type_array[j])
		{
		case STRINGTYPE:
			testrec.AddField (recordnum, temp->getfieldcontents("dummystring", j));
			break;
		case INTTYPE:
			tempint = temp->getfieldcontents(3, j);
			testrec.AddField (recordnum, ToString(tempint));
			break;
		case CHARTYPE:
			tempchar = temp->getfieldcontents('j', j);
			testrec.AddField (recordnum, ToString(tempchar));
			break;
		case FLOATTYPE:
			tempfloat = temp->getfieldcontents(4.5f, j);
			testrec.AddField (recordnum, ToString(tempfloat));
			break;
		default:
			break;
		}
		fptr++;
	}
	return true;
}
/////////////////////////////////////////////////////////////////////
// FUNCTION : showrecord() : unoverloaded version that uses dynamic
//                           casting to cast correct type of tree
//                           before displaying records.
//THROWS : badcastexception
//RETURNS: boolean status
//
/////////////////////////////////////////////////////////////////////

bool datafile::showrecord ()
{

	if(!therecords.size())
	{
		return false;
	}
	Records::record * temp = therecords.front();

	AVLtree<std::string> * avlstringptr;
	AVLtree<int> * avlintptr;
	AVLtree<char> * avlcharptr;
	AVLtree<float> * avlfloatptr;
	tree ** fptr = field_ptr;

	for(int j = 0; j < numberoffields; j++)
	{
		avlstringptr = dynamic_cast<AVLtree<std::string>*>(*fptr);
		if(!avlstringptr)
		{
			avlintptr = dynamic_cast<AVLtree<int>*>(*fptr);
			if(!avlintptr)
			{
				avlcharptr = dynamic_cast<AVLtree<char>*>(*fptr);
				if(!avlcharptr)
				{
					avlfloatptr = dynamic_cast<AVLtree<float>*>(*fptr);
					if(!avlfloatptr)
					{
						std::cout << "Error.  Exception at line " << __LINE__ << "in file " << __FILE__;
						throw badcastexception();
					}
					else
					{
						float dummyfloat = 0;
						std::cout << temp->getfieldcontents(dummyfloat, j);
					}
				}
				else
				{
					char dummychar = 0;
					std::cout << temp->getfieldcontents(dummychar, j);
				}
			}
			else
			{
				int dummyint = 0;
				std::cout << temp->getfieldcontents(dummyint, j);
			}
		}
		else
		{
			std::string dummystring;
			std::cout << temp->getfieldcontents(dummystring, j);
		}
	fptr++;
	}

	return true;					
}

std::string datafile::getthefieldname (int fieldnumber)
{
	return field_ptr[fieldnumber]->GetFieldName();
}

void datafile::removerecord (int recordnum)
{

	for(int i = 0; i <numberoffields; i++)
	{
		switch(type_array[i])
		{
		case STRINGTYPE:
			{
				std::string dummy = "";
				std::string * addressofitem;
				addressofitem = therecords[recordnum -1]->getfieldpointer(dummy, i);
				AVLtree<std::string> * temp = dynamic_cast<AVLtree<std::string>*>(field_ptr[i]);
				if(temp == NULL)
				{
					throw Win::Exception ("Bad Cast in Remove function");
				}
				else
				{
					temp->delete_item (addressofitem);
				}
			}
			break;
		case INTTYPE:
			{
				int dummy = 0;
				int * addressofitem;
				addressofitem = therecords[recordnum -1]->getfieldpointer(dummy, i);
				AVLtree<int> * temp = dynamic_cast<AVLtree<int>*>(field_ptr[i]);
				if(temp == NULL)
				{
					throw Win::Exception ("Bad Cast in Remove function");
				}
				else
				{
					temp->delete_item (addressofitem);
				}
			}
			break;
		case CHARTYPE:
			{
				char dummy = ' ';
				char * addressofitem;
				addressofitem = therecords[recordnum -1]->getfieldpointer(dummy, i);
				AVLtree<char> * temp = dynamic_cast<AVLtree<char>*>(field_ptr[i]);
				if(temp == NULL)
				{
					throw Win::Exception ("Bad Cast in Remove function");
				}
				else
				{
					temp->delete_item (addressofitem);
				}
			}
			break;
		case FLOATTYPE:
			{
				float dummy = 0;
				float * addressofitem;
				addressofitem = therecords[recordnum -1]->getfieldpointer(dummy, i);
				AVLtree<float> * temp = dynamic_cast<AVLtree<float>*>(field_ptr[i]);
				if(temp == NULL)
				{
					throw Win::Exception ("Bad Cast in Remove function");
				}
				else
				{
					temp->delete_item (addressofitem);
				}
			}
			break;
		}//end switch
	}//end loop i

	therecords.erase(therecords.begin() + recordnum);
	for(i = 0; i < therecords.size(); i++)
	{
		therecords[i]->setrecordnumber(i+1);
	}
}
