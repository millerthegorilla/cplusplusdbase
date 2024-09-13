#if !defined STATUS_H
#define STATUS_H
// (c) Bartosz Milewski 2000
#include "win.h"
#include <string>

const int idNotFound = -1;

class Syntax 
{
public:
	Syntax (std::string const & str)
		: _str (str)
	{}
	Syntax (char const * str = "")
		: _str (str)
	{}
	char const * GetString () const
	{
		if (_str.length () == 0)
			return "Syntax error.";
		return _str.c_str ();
	}
private:
	std::string _str;
};

class Output
{
public:
	void Init (Win::Dow win)
	{
		_win.Init (win);
	}
	void Error (std::string str)
	{
		Error (str.c_str ());
	}
	void Error (char const * str);
private:
	Win::Dow _win;
};

extern Output TheOutput;
extern Output TheChildOutput;

#endif