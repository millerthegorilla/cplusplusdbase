#if !defined (BUTTON_H)
#define BUTTON_H
// (c) James Miller 2005
#include "controls.h"

namespace Win
{
	class Button: public SimpleCtrl
	{
	public:
		Button (HWND winParent, int id)
			: SimpleCtrl (winParent, id)
		{}

		Button (HWND win = 0) : SimpleCtrl (win) {}

		void SetText (char const * buf)
		{
			SendMessage(WM_SETTEXT, 0, reinterpret_cast<LPARAM> (buf));
		}

	};

	class ButtonMaker: public ControlMaker
	{
	public:
		ButtonMaker (HWND winParent, int id) : ControlMaker ("BUTTON", winParent, id)
		{
			_exStyle = WS_EX_WINDOWEDGE;
			_style |= BS_DEFPUSHBUTTON;
		}
		void CheckBox () { _style |= BS_AUTOCHECKBOX; }
		
	};

}
#endif
