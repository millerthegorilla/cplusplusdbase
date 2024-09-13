#ifndef _DATAFILE_H_
#define _DATAFILE_H_
#pragma warning (disable:4786)
#include <vector>

#include "record.h"
#include "AVLtreeIMP.h"
#include "..\Params.h"
#include "RecordStruct.h"


class datafile
{
public:
	//methods
	datafile();
	~datafile();
	datafile(const datafile &rhs);
	datafile& operator=(const datafile &rhs);
	void initialise(std::vector<TREETYPE> &typearray,
					std::vector<std::string> &fieldnames);
	void newrecord();
	void newrecord(std::vector<std::string> fieldentry); //used by load function in database
	bool showrecord(); 
	bool showrecord(RecordStruct::recordstruct & testrec, int recordnum);
	TREETYPE gettypearray(int index);
	TREETYPE * getthetypearray() const { return type_array; }
	std::vector <Records::record*> gettherecords () const { return therecords; }
	tree ** getthefieldptr () const { return field_ptr; }
	std::string getthefieldname (int fieldnumber);
	int getnumberoffields() const { return numberoffields; }
	int getnumberofrecords() const { return therecords.size(); }
	tree * getfieldptr (int index) { return field_ptr[index];}
	void removerecord(int recordnum);
		
	class badcastexception
	{
	public:
		badcastexception(){ msg = "Bad Cast.  Unable to continue"; }
		std::string msg; 
	};
	
private:
	TREETYPE * type_array;
	int numberoffields;
	std::vector<Records::record *> therecords;
	tree ** field_ptr;
};


#endif