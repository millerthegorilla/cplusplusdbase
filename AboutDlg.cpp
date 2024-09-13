#include "AboutDlg.h"
// Bartosz Milewski (c) 2000
#include "Dialog.h"

// Absolutely minimal implementation

bool AboutCtrl::OnCommand (int ctrlId, int notifyCode) throw (Win::Exception)
{
    if (ctrlId == IDOK)
    {
        EndOk ();
        return true;
    }
	return false;
}
