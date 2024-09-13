#include "Control.h"
// (c) Bartosz Milewski 2000
#include "status.h"
#include "Params.h"
#include "util.h"
#include "Exception.h"
#include <sstream>
#include "ContextMenuTable.h"
#include "winuser.h"

bool TopController::OnDestroy () throw ()
{
    ::PostQuitMessage (0);
    return true;
}

bool TopController::OnCreate (Win::CreateData const * create) throw ()
{
	try
	{
		TheOutput.Init (_h);
		std::vector<Menu::Item const *> contextItems;
		
		contextItems.push_back(&Menu::ContextItem1 );
		contextItems.push_back(&Menu::ContextItem2 );
		contextItems.push_back(&Menu::ContextItem3 );
		contextItems.push_back(&Menu::ContextItem4 );
		// create a Commander to execute commands
		//_commander.reset (new Commander (_h));
		_commander = std::auto_ptr<Commander> (new Commander (_h, _database));
		_contextcommander = std::auto_ptr <ContextCommander> (new ContextCommander (_h, _database));
		// Create a command vector based on global Cmd::Table and Commander
		//_cmdVector.reset (new CmdVector (Cmd::Table, _commander.get ()));
		_cmdVector = std::auto_ptr<CmdVector> (new CmdVector (Cmd::Table, _commander.get ()));
		_contextcmdVector = std::auto_ptr<ContextCmdVector> (new ContextCmdVector (Cmd::ContextTable, _contextcommander.get ()));
		// Create a view which contains a menu
		//_view.reset(new View (_h, _cmdVector.get (), _calc));
		_view = std::auto_ptr<View>(new View (_h, _cmdVector.get (), _contextcmdVector.get (), _database, contextItems));
		// view must be fully constructed before calling these
		_view->Init (_h);
		_view->SetStatus ("Ready");
	}
	catch (...)
	{
		TheOutput.Error ("Internal Error:\nFailure to initialize.");
	}
	return true;
}

bool TopController::OnFocus (Win::Dow winPrev) throw ()
{
	_view->SetFocus ();
	return true;
}

bool TopController::OnSize (int width, int height, int flags) throw ()
{
	if (flags != SIZE_MINIMIZED)
	{
		_view->Size (width, height);
	}
	return true;
}

bool TopController::OnCommand (int cmdId, bool isAccel) throw ()
{
	if(_contextinit)
	{
		_contextinit = false;
		_contextcmdVector->Execute (cmdId);
	}
	else
	{
		try
		{
			_cmdVector->Execute (cmdId);
		}
		catch (Win::ExitException)
		{
			_h.Destroy ();
		}
		catch (Win::Exception const & e)
		{
			TheOutput.Error (e.GetMessage ());
		}
		catch (...)
		{
			TheOutput.Error ("Internal error");
		}
	}
	return true;
}


bool TopController::OnControl (Win::Dow control, int controlId, int notifyCode) throw ()
{
	if (controlId == IDOK)
	{
		try
		{
		}
		catch (Syntax const & err)
		{
			TheOutput.Error (err.GetString ());
		}
		return true;
	}
	return false;
}

bool TopController::OnInitPopup (HMENU menu, int pos) throw ()
{
	//if menu = cmd menu then set contextinit to false

	if(!_view->CheckIsContext(menu))
	{
		_contextinit = false;
		try
		{
			_view->RefreshPopup (menu, pos);
		}
		catch (...) 
		{}
	}
	
	return true;
}

bool TopController::OnMenuSelect (int id, int flags, HMENU menu) throw ()
{
	if (flags == 0xffff && menu == NULL)
	{
		// menu dismissed
		_view->SetStatus ("Ready");
		return true;
	}
	if ((flags & MF_SEPARATOR) || (flags & MF_SYSMENU))
	{
		return false;
	}
	if (!(flags & MF_POPUP))
	{
		// menu item selected
		_view->SetStatus (_cmdVector->GetHelp (id));
		return true;
	}
	return false;
}

bool TopController::OnUserMessage ( UINT msg, 
									WPARAM wParam, 
									LPARAM lParam, 
									LRESULT & result) throw ()
{
	switch(msg)
	{
	case MSG_CONTROLMSG:
		_view->SendControlMessage(wParam,CTRL_MSGS(lParam));
		return true;
		break;
	case MSG_RECORDSMSG:
		_view->AddRecord();
		return true;
		break;
	case MSG_RECORDSHOW:
		_view->ShowRecord(int(wParam), int(lParam));
		return true;
		break;
	case MSG_RECORDFIND:
		_view->SearchRecord(reinterpret_cast <std::string *>(wParam));
		return true;
		break;
	case MSG_RECORDDEL:
		_view->RemoveRecord(int(wParam));
		return true;
		break;
	}
	return false;
}


bool TopController::OnRButtonDown (int x, int y, Win::KeyState kState)
{
	_contextinit = true;
	_view->SetContext(_h,x,y);
	return true;
}