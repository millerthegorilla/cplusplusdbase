#if !defined (CHILDCONTROL_H)
#define CHILDCONTROL_H
// (c) Bartosz Milewski 2000

#include "Controller.h"
#include "ChildView.h"
#include "ContextCommander.h"
#include "ContextMenuTable.h"
#include "Model\database.h"

class ChildController: public Win::Controller
{
public:

	bool OnCreate (Win::CreateData const * create) throw ();
    bool OnDestroy () throw ();
	bool OnFocus (Win::Dow winPrev) throw ();
	bool OnSize (int width, int height, int flags) throw ();
	bool OnCommand (int cmdId, bool isAccel) throw ();
	bool OnControl (Win::Dow control, int controlId, int notifyCode) throw ();
	bool OnUserMessage (UINT msg, 
						WPARAM wParam, 
						LPARAM lParam, 
						LRESULT & result) throw ();
	bool OnRButtonDown (int x, int y, Win::KeyState kState) throw ();
	bool OnHScroll (int scrollcode, short scrollpos, HWND scrollHwnd) throw ();
	bool OnVScroll (int scrollcode, short scrollpos, HWND scrollHwnd) throw ();
private:
	std::auto_ptr<ContextCommander> _contextcommander;
	std::auto_ptr<ContextCmdVector>    _contextcmdVector;
	std::auto_ptr<ChildView>			_view;

	// this is the Model
	database	*_database;
	bool		_contextinit;
};

#endif