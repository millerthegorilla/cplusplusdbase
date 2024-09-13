#include "Edit.h"
// (c) Bartosz Milewski 2000

using namespace Win;

std::string Edit::GetText () const
{
    int len = GetLen ();
	std::string val;
    if (len > 0)
    {
		val.reserve (len + 1);
        val.resize (len);
        GetText (&val [0], len + 1);
    }
	return val;
}

void Edit::Append (char const * buf)
{
	int len = GetLen ();
	Select (len, -1);
	SendMessage (EM_REPLACESEL, 0, reinterpret_cast<LPARAM> (buf));
}

void Edit::SelectLine (int lineNo)
{
	int lineStart = SendMessage (EM_LINEINDEX, lineNo);
	int lineLen = SendMessage (EM_LINELENGTH, lineNo);
	Select (lineStart, lineStart + lineLen);
}

void Edit::Clear ()
{
	Select ();
	SendMessage (WM_CLEAR, 0, 0);
}
