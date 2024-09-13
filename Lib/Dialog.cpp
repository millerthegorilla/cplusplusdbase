#include "Dialog.h"
// (c) Bartosz Milewski 2000
#include "Win.h"

namespace Dialog
{

	BOOL CALLBACK ModalProc (HWND win, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Controller * ctrl = Win::GetLong<Controller *> (win);
		try
		{
			switch (message)
			{
			case WM_INITDIALOG:
				{
					ctrl = reinterpret_cast<Controller *> (lParam);
					Win::SetLong<Controller *> (win, ctrl);
					ctrl->SetWindow (win);
					ctrl->OnInitDialog ();
				}
				return TRUE;

			case WM_COMMAND:
				if (ctrl && ctrl->OnCommand (LOWORD(wParam), HIWORD (wParam)))
					return TRUE;    // Windows doesn't understand bool::true
				break;
			}
		}
		catch (Win::Exception & e)
		{
			::MessageBox (win, "Unexpected error", e.GetMessage ().c_str (), MB_OK | MB_ICONERROR);
		}
		return FALSE;
	}

	BOOL CALLBACK ModelessProc (HWND win, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Controller * ctrl = Win::GetLong<Controller *> (win);
		try
		{
			switch (message)
			{
			case WM_INITDIALOG:
				{
					std::auto_ptr<Controller> * ap 
						= reinterpret_cast<std::auto_ptr<Controller> *> (lParam);
					ctrl = ap->release ();
					Win::SetLong<Controller *> (win, ctrl);
					ctrl->SetWindow (win);
					ctrl->OnInitDialog ();
				}
				return TRUE;

			case WM_COMMAND:
				if (ctrl && ctrl->OnCommand (LOWORD(wParam), HIWORD (wParam)))
					return TRUE;    // Windows doesn't understand bool::true
				break;

			case WM_DESTROY:
				delete ctrl;
				break;
			}
		}
		catch (Win::Exception & e)
		{
			::MessageBox (win, "Unexpected error", e.GetMessage ().c_str (), MB_OK | MB_ICONERROR);
		}
		return FALSE;
	}
}
