#include "SearchDlg.h"
// Bartosz Milewski (c) 2000
#include "Dialog.h"
#include "resource.h"

// Absolutely minimal implementation
void SearchCtrl::OnInitDialog () throw (Win::Exception)
{
	_edit.Init(GetWindow (), IDC_SEARCHSTRING);
}

bool SearchCtrl::OnCommand (int ctrlId, int notifyCode) throw (Win::Exception)
{
    switch(ctrlId)
	{
	case IDOK:
		_searchString = _edit.GetText ();
        EndOk ();
        return true;
		break;
	case IDCANCEL:
		EndCancel ();
		return true;
		break;
	}
	return false;
}