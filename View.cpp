#include "View.h"
// Bartosz Milewski (c) 2000
#include "Model\database.h"
#include "params.h"
#include "Tools.h"
#include "Class.h"
//#include "Maker.h"

View::View (Win::Dow win,
			Cmd::Vector * cmdVector,
			Cmd::Vector * contextcmdVector,
			database & database,
			std::vector<Menu::Item const *> contextItems)
		: _menu (Menu::barItems, *cmdVector),
		_context( contextItems , *contextcmdVector),
		  _database (database),
		  _win(win)
{
	Win::StatusBarMaker status (win, 0);
	_status.Init (status.Create ());
	_vControlVector.push_back(_status);
	// Create child windows

	
/*	Win::ChildWinMaker cwmaker(className, win, 1);

	cwmaker.SetSize(clrect.right, clrect.bottom);
	_childwin.Init(cwmaker.Create());
*/		
	//_childwin.Show ();

	char className[] = "ChildWin";

	Win::ClassMaker winClass (className, _win.GetInstance());
//	winClass.SetIcons (IDI_MAIN);
	winClass.Register ();

	Win::Maker wcmaker(className,_win.GetInstance());
	wcmaker.SetParent(_win);
	RECT clrect;
	_win.GetClientSize (clrect);
	wcmaker.SetSize(clrect.right, clrect.bottom - _status.Height());
	wcmaker.SetStyle(WS_CHILD | WS_HSCROLL | WS_VSCROLL);
	
	_childwin = wcmaker.Create(_childCtrl,"ChildWindow");
	_childwin.SendMessage(MSG_ADDDBASPTR, reinterpret_cast<WPARAM>(&_database));
	

//	_historyView.SetFont (fixed);

}

void View::Init (Win::Dow win)
{
	_menu.AttachToWindow (win);
}

void View::Size (int width, int height)
{
	int statusHeight = _status.Height ();
	_status.Move  (0, height - statusHeight, width, statusHeight); 
	_childwin.Move (0, 0, width, height - statusHeight);
}

void View::SetStatus (char const * str)
{
	_status.SetText (str);
}

void View::SendControlMessage(int ControlId, CTRL_MSGS Msg)
{
	Win::SimpleCtrl temp = _vControlVector[ControlId];

	switch(Msg)
	{
	case CTRL_ENABLE:
		temp.Enable ();
		break;
	case CTRL_DISABLE:
		temp.Disable ();
		break;
	case CTRL_HIDE:
		temp.Hide ();
		break;
	case CTRL_SHOW:
		temp.Show();
		break;
	}
}

void View::SetContext(Win::Dow win, int x, int y)
{
	RECT  windowrect;
	::GetWindowRect(win,&windowrect);
	_context.TrackMenu(win, windowrect.left + x, windowrect.top + y + 20);
}

void View::AddRecord()
{	
	_childwin.SendMessage(MSG_RECORDSMSG);
	_childwin.SendMessage(MSG_ADDABUTTON);
	_childwin.Display();
//	_childwin.Invalidate();
//	_childwin.Update();

}

bool View::CheckIsContext (HMENU menu)
{
	if(_context.GetHandle() == menu)
	{
		return true;
	}
	return false;
}

void View::ShowRecord (int recordbegin, int recordend)
{
	_childwin.SendMessage(MSG_RECORDSHOW, recordbegin, recordend);
	_childwin.Display();
}

void View::SearchRecord (std::string * SearchString)
{
	_childwin.SendMessage(MSG_RECORDFIND, WPARAM(SearchString));
	_childwin.Display();
}

void View::RemoveRecord (int toremove)
{
	_childwin.SendMessage(MSG_RECORDDEL, WPARAM(toremove));
	_childwin.Display();
}

// Turn the return key into IDOK and send to parent
bool EditController::OnKeyDown (int vKey, int flags) throw ()
{
	if (vKey == VK_RETURN)
	{
		_h.GetParent ().SendMessage (WM_COMMAND, 
			MAKEWPARAM (IDOK, 0),
			reinterpret_cast<LPARAM> (static_cast<HWND> (_h)));
		return true;
	}
	return false;
};

bool ButtonController::OnLButtonDown (int x, int y, Win::KeyState kState) throw ()
{		
	return false;
}

bool ButtonController::OnLButtonUp (int x, int y, Win::KeyState kState) throw ()
{
	return false;
}


