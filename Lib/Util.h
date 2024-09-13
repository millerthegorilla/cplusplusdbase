#if !defined (UTIL_H)
#define UTIL_H
// (c) Bartosz Milewski 2000

#include <cstring>
#include <sstream>
#include <string>

template<class T>
inline std::string ToString (T & val)
{
	std::ostringstream out;
	out << val;
	return out.str ();
}

std::string GetStringIn(std::string string);

class NocaseCmp
{
public:
	bool operator () (char const * str1, char const * str2) const
	{
		return (_stricmp (str1, str2) < 0);
	}
};



#endif
