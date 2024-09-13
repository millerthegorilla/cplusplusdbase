#include "Maker.h"
// (c) Bartosz Milewski 2000
#include <cassert>
#include "Exception.h"

using namespace Win;

Maker::Maker (char const * className, HINSTANCE hInst)
  : _style (WS_OVERLAPPEDWINDOW),
    _exStyle (0),
    _className (className),
    _x (CW_USEDEFAULT), // horizontal position of window
    _y (0),             // vertical position of window
    _width (CW_USEDEFAULT), // window width  
    _height (0),        // window height
    _winParent (0),    // handle to parent or owner window
    _menu (0),         // handle to menu, or child-window identifier
    _data (0),          // pointer to window-creation data
	_hInst (hInst)
{
}

HWND Maker::Create (Controller & controller, char const * title)
{
	HWND win = ::CreateWindowEx (
		_exStyle,
		_className,
		title,
		_style,
		_x,
		_y,
		_width,
		_height,
		_winParent,
		_menu,
		_hInst,
		&controller);

	if (win == 0)
		throw "Internal error: Window Creation Failed.";
	return win;
}

void Maker::SetMenu (char const * menuName)
{
	_menu = ::LoadMenu (_hInst, menuName);
	if (_menu == 0)
		throw Win::Exception ("Cannot load menu from resources");
}

ChildMaker::ChildMaker (char const * className, Win::Dow winParent, int childId)
    : Maker (className, winParent.GetInstance ())
{
    _style = WS_CHILD;
    _winParent = winParent;
    _menu = reinterpret_cast<HMENU> (childId);
}

HWND ChildMaker::Create (char const * text)
{
	HWND win = ::CreateWindowEx (
		_exStyle,
		_className,
		text,
		_style,
		_x,
		_y,
		_width,
		_height,
		_winParent,
		_menu,
		_hInst,
		0);

	if (win == 0)
		throw "Internal error: Child Window Creation Failed.";
	return win;
}

