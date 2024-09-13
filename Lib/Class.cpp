#include "Class.h"
// (c) Bartosz Milewski 2000
#include "Procedure.h"

using namespace Win;

ClassMaker::ClassMaker
    (char const * className, HINSTANCE hInst)
{
    _class.lpfnWndProc = Win::Procedure;   // window procedure: mandatory
    _class.hInstance = hInst;         // owner of the class: mandatory
    _class.lpszClassName = className; // mandatory
	_class.cbSize = sizeof (WNDCLASSEX);
    _class.hCursor = ::LoadCursor (0, IDC_ARROW); // optional
    _class.hbrBackground = reinterpret_cast<HBRUSH> (COLOR_WINDOW + 1); // optional
    _class.style = 0;
    _class.cbClsExtra = 0;
    _class.cbWndExtra = 0;
    _class.hIcon = 0;
	_class.hIconSm = 0;
    _class.lpszMenuName = 0;
}

void ClassMaker::SetIcons (int id)
{
    _stdIcon.Load (_class.hInstance, id);
    _smallIcon.Load (_class.hInstance, id);
    _class.hIcon = _stdIcon;
    _class.hIconSm = _smallIcon;
}

void ClassMaker::SetBkColor (int r, int g, int b)
{
	_class.hbrBackground = ::CreateSolidBrush (RGB (r, g, b));
}
