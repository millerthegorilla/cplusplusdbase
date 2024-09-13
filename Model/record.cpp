#include "record.h"

using namespace Records;

record::record(int numoffields)
{
	fptr = new fieldpointers[numoffields];
	numberoffields = numoffields;
}

record::~record ()
{
	delete [] fptr;
}

record::record(const record &rhs)
{
	recordnumber = rhs.getrecordnumber ();
	numberoffields = rhs.numberoffields;
	fptr = new fieldpointers[numberoffields];
	for(int i = 0; i < numberoffields; i++)
	{
		fptr[i] = rhs.fptr[i];
	}
}

record& record::operator=(const record &rhs)
{
	if(this == &rhs)
	{
		return *this;
	}
	
	recordnumber = rhs.getrecordnumber ();
	numberoffields = rhs.numberoffields;
	fptr = new fieldpointers[numberoffields];
	for(int i = 0; i < numberoffields; i++)
	{
		fptr[i] = rhs.fptr[i];
	}
	return * this;
}

void record::setfieldpointer(int *x, int fieldnumber)
{
	fptr[fieldnumber].intptr = x;
}

void record::setfieldpointer(std::string *x, int fieldnumber)
{
	fptr[fieldnumber].stringptr = x;
}

void record::setfieldpointer(char *x, int fieldnumber)
{
	fptr[fieldnumber].charptr = x;
}

void record::setfieldpointer(float *x, int fieldnumber)
{
	fptr[fieldnumber].floatptr = x;
}

float record::getfieldcontents(float dummy, int fieldnumber)
{
	return *fptr[fieldnumber].floatptr;
}

int record::getfieldcontents(int dummy, int fieldnumber)
{
	return *fptr[fieldnumber].intptr;
}

char record::getfieldcontents(char dummy, int fieldnumber)
{
	return *fptr[fieldnumber].charptr;
}

std::string record::getfieldcontents(std::string dummy, int fieldnumber)
{
	return *fptr[fieldnumber].stringptr;
}

int record::getrecordnumber () const
{
	return recordnumber;
}

void record::setrecordnumber (int num)
{
	recordnumber = num;
}