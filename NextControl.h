#if !defined (NEXTCONTROL_H)
#define NEXTCONTROL_H
// (c) Bartosz Milewski 2000

#include "Controller.h"

class NextController: public Win::Controller
{
public:
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
private:

};


#endif
