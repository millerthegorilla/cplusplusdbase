#include "ChildControl.h"
// (c) Bartosz Milewski 2000
#include "status.h"
#include "Params.h"
#include "util.h"
#include "Exception.h"
#include <sstream>
#include "ContextMenuTable.h"
#include "winuser.h"

bool ChildController::OnDestroy () throw ()
{
    ::PostQuitMessage (0);
    return true;
}

bool ChildController::OnCreate (Win::CreateData const * create) throw ()
{
	try
	{
		TheChildOutput.Init (_h);
		std::vector<Menu::Item const *> contextItems;
		
		contextItems.push_back(&Menu::ContextItem1 );
		contextItems.push_back(&Menu::ContextItem2 );
		contextItems.push_back(&Menu::ContextItem3 );
		contextItems.push_back(&Menu::ContextItem4 );
		// create a Commander to execute commands
		//_commander.reset (new Commander (_h));
		_contextcommander = std::auto_ptr <ContextCommander> (new ContextCommander (_h, *_database));
		// Create a command vector based on global Cmd::Table and Commander
		//_cmdVector.reset (new CmdVector (Cmd::Table, _commander.get ()));
		_contextcmdVector = std::auto_ptr<ContextCmdVector> (new ContextCmdVector (Cmd::ContextTable, _contextcommander.get ()));
		// Create a view which contains a menu
		//_view.reset(new View (_h, _cmdVector.get (), _calc));
		_view = std::auto_ptr<ChildView>(new ChildView (_h, _contextcmdVector.get (), contextItems));
		// view must be fully constructed before calling these

	}
	catch (...)
	{
		TheChildOutput.Error ("Internal Error:\nFailure to initialize.");
	}
	return true;
}

bool ChildController::OnFocus (Win::Dow winPrev) throw ()
{
	_view->SetFocus ();
	return true;
}

bool ChildController::OnSize (int width, int height, int flags) throw ()
{
	if (flags != SIZE_MINIMIZED)
	{
		_view->Size (width, height);
	}
	return true;
}

bool ChildController::OnCommand (int cmdId, bool isAccel) throw ()
{
	
	_contextcmdVector->Execute (cmdId);
	
	return true;
}


bool ChildController::OnControl (Win::Dow control, int controlId, int notifyCode) throw ()
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

bool ChildController::OnUserMessage ( UINT msg, 
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
		_view->MakeTable();
		_view->SetRecordLabel();
		return true;
		break;
	case MSG_INVALIDATE:
		_view->Redraw();
		return true;
		break;
	case MSG_ADDABUTTON:
		_view->AddButton();
		return true;
		break;
	case MSG_ADDDBASPTR:
		_database = reinterpret_cast<database*>(wParam);
		_view->SetDbase(_database);
		return true;
		break;
	case MSG_BUTTONPRES:
		_view->ButtonPressed();
		return true;
		break;
	case MSG_RECORDSHOW:
		if(lParam == wParam)
		{
			_view->MakeTable();
		}
		else
		{
			_view->MakeTable(int(lParam - wParam) + 1);
		}
		_view->ShowRecords(int(wParam), int(lParam));
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


bool ChildController::OnRButtonDown (int x, int y, Win::KeyState kState)
{
	_contextinit = true;
	_view->SetContext(_h,x,y);
	return true;
}

bool ChildController::OnHScroll (int scrollcode, short int scrollpos, HWND scrollHwnd) throw ()
{
	_view->SetHScrollBar(scrollcode, scrollpos, scrollHwnd);
	return true;
}

bool ChildController::OnVScroll (int scrollcode, short int scrollpos, HWND scrollHwnd) throw ()
{
	_view->SetVScrollBar(scrollcode, scrollpos, scrollHwnd);
	return true;
}