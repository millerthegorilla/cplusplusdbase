#include "Status.h"
// Bartosz Milewski (c) 2000

Output TheOutput;
Output TheChildOutput;

void Output::Error (char const * str)
{
	::MessageBox (_win, str, "Database Error", MB_OK | MB_ICONERROR);
}