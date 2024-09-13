#if !defined (MAKER_H)
#define MAKER_H
// (c) Bartosz Milewski 2000
#include <windows.h>
#include "Controller.h"

namespace Win
{
	class Maker
	{
	public:
		Maker (char const * className, HINSTANCE hInst);
		HWND Create (Controller & control, char const * title);
		void SetStyle (DWORD style) { _style = style; }
		void SetExStyle (DWORD style) { _exStyle = style; }
		void SetSize (int width, int height)
		{
			_width = width;
			_height = height;
		}
		void SetMenu (char const * menuName);
		void SetParent (Win::Dow parent)
		{
			_winParent = parent;
		}
	protected:
		HINSTANCE	_hInst;			// program instance
		char const *_className;		// name of Window class
		DWORD		_style;			// window style
		DWORD		_exStyle;		// window extended style
		char const *_title;			// window title
		int         _x;             // horizontal position of window
		int         _y;             // vertical position of window
		int         _width;         // window width  
		int         _height;        // window height
		HWND        _winParent;     // handle to parent or owner window
		HMENU       _menu;          // handle to menu, or child-window identifier
		void *      _data;          // pointer to window-creation data
	};

	class ChildMaker: public Maker
	{
	public:
		ChildMaker (char const * className, Win::Dow winParent, int childId);
		HWND Create (char const * text = "");
	};
}
#endif
