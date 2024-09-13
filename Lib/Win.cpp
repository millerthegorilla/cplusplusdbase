#include "Win.h"
// Bartosz Milewski (c) 2000
#include "Controller.h"
#include "Procedure.h"

void Win::Dow::SubClass (SubController * subCtrl)
{
	// get previous window procedure and controller (if any)
	ProcPtr prevProc = GetLong<ProcPtr> (_h, GWL_WNDPROC);
	Controller * prevCtrl = GetLong<Controller *> (_h);
	// remember them in the new controller
	subCtrl->Init (_h, prevProc, prevCtrl);
	// attach new controller to window
	SetLong<Controller *> (_h, subCtrl);
	// attach new window procedure to window
	SetLong<ProcPtr> (_h, SubProcedure, GWL_WNDPROC);
}

void Win::Dow::UnSubClass ()
{
	// Get the current subclass controller
	SubController * pCtrl = GetLong<SubController *> (_h);
	// restore previous window procedure and controller (if any)
	SetLong<ProcPtr> (_h, pCtrl->GetPrevProc (), GWL_WNDPROC);
	SetLong<Controller *> (_h, pCtrl->GetPrevController ());
}