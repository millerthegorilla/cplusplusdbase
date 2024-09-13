#if !defined (CONTROL_H)
#define CONTROL_H
// (c) Bartosz Milewski 2000

#include "Controller.h"
#include "View.h"
#include "Commander.h"
#include "ContextCommander.h"
#include "ContextMenuTable.h"
#include "Model\database.h"

class TopController: public Win::Controller
{
public:
	TopController() : _contextinit(false){}
	bool OnCreate (Win::CreateData const * create) throw ();
    bool OnDestroy () throw ();
	bool OnFocus (Win::Dow winPrev) throw ();
	bool OnSize (int width, int height, int flags) throw ();
	bool OnCommand (int cmdId, bool isAccel) throw ();
	bool OnControl (Win::Dow control, int controlId, int notifyCode) throw ();
	bool OnInitPopup (HMENU menu, int pos) throw ();
	bool OnMenuSelect (int id, int flags, HMENU menu) throw ();
	bool OnUserMessage (UINT msg, 
						WPARAM wParam, 
						LPARAM lParam, 
						LRESULT & result) throw ();
	bool OnRButtonDown (int x, int y, Win::KeyState kState) throw ();
private:
	std::auto_ptr<Commander>	_commander;
	std::auto_ptr<ContextCommander> _contextcommander;
	std::auto_ptr<CmdVector>	_cmdVector;
	std::auto_ptr<ContextCmdVector>    _contextcmdVector;
	std::auto_ptr<View>			_view;

	// this is the Model
	database	_database;
	bool		_contextinit;
};

#endif
