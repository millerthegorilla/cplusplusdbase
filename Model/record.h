#ifndef _RECORD_H_
#define _RECORD_H_

#include <iostream>
namespace Records
{
	class record
	{
	public:
		record(int numoffields);
		~record();
		record(const record &rhs);
		record& operator=(const record &rhs);
		void setfieldpointer(int *x, int fieldnumber);
		void setfieldpointer(std::string *x, int fieldnumber);
		void setfieldpointer(char *x, int fieldnumber);
		void setfieldpointer(float *x, int fieldnumber);
		float getfieldcontents(float dummy, int fieldnumber);
		int getfieldcontents(int dummy, int fieldnumber);
		char getfieldcontents(char dummy, int fieldnumber);
		std::string getfieldcontents(std::string dummy, int fieldnumber);
		int getrecordnumber() const;
		void setrecordnumber(int num);
		template <typename T>
		T * getfieldpointer(T type, int fieldnumber)
		{   
			if(typeid(type) == typeid(std::string))
			{
				return reinterpret_cast<T*>(fptr[fieldnumber].stringptr);
			}
			else if(typeid(type) == typeid(int))
			{
				return reinterpret_cast<T*>(fptr[fieldnumber].intptr);
			}
			else if(typeid(type) == typeid(char))
			{
				return reinterpret_cast<T*>(fptr[fieldnumber].charptr);
			}
			else if(typeid(type) == typeid(float))
			{
				return reinterpret_cast<T*>(fptr[fieldnumber].floatptr);
			}
			return NULL;
		}
	private:
		union fieldpointers
		{
			int * intptr;
			char *charptr;
			float *floatptr;
			std::string * stringptr;
		};
		fieldpointers * fptr;
		int numberoffields;
		int recordnumber;
	};
}

#endif