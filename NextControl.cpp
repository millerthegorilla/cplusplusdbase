#include "NextControl.h"
// (c) Bartosz Milewski 2000
#include "Params.h"
#include "util.h"
#include "Exception.h"
#include <sstream>

bool NextController::OnDestroy () throw ()
{
    ::PostQuitMessage (0);
    return true;
}

bool NextController::OnCreate (Win::CreateData const * create) throw ()
{
	try
	{

	}
	catch (...)
	{
	
	}
	return true;
}

bool NextController::OnFocus (Win::Dow winPrev) throw ()
{
	return true;
}

bool NextController::OnSize (int width, int height, int flags) throw ()
{
	if (flags != SIZE_MINIMIZED)
	{
		_view->Size (width, height);
		_view->ReDisplayMemory (); // changed column size
	}
	return true;
}

bool NextController::OnControl (Win::Dow control, int controlId, int notifyCode) throw ()
{
	if (controlId == IDOK)
	{
		try
		{
		
		}
		catch (Syntax const & err)
		{

		}
		return true;
	}
	return false;
}


bool NextController::OnUserMessage ( UINT msg, 
									WPARAM wParam, 
									LPARAM lParam, 
									LRESULT & result) throw ()
{
	if (msg == MSG_MEMCLEAR)
	{
		return true;
	}
	return false;
}


