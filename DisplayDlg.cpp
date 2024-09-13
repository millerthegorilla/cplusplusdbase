#include "DisplayDlg.h"
// Bartosz Milewski (c) 2000
#include "Dialog.h"
#include "Util.h"

// Absolutely minimal implementation

DisplayCtrl::DisplayCtrl(int numberofrecords)
{
	_numOfRecords = numberofrecords;
}

void DisplayCtrl::OnInitDialog () throw (Win::Exception)
{
	_fromEdit.Init (GetWindow (), IDC_FROMREC);
	_toEdit.Init (GetWindow (), IDC_TOREC);
	_numRecs.Init (GetWindow (), IDC_NUMRECS);
	_numRecs.SetText (ToString(_numOfRecords).c_str());
}

bool DisplayCtrl::OnCommand (int ctrlId, int notifyCode) throw (Win::Exception)
{

    if (ctrlId == IDOK)
    {
		if( (_from = atoi(_fromEdit.GetText ().c_str ())) \
			&& (_to = atoi(_toEdit.GetText ().c_str()))  \
			&& (_from <= _numOfRecords && _to <= _numOfRecords))
		{
			EndOk ();
			return true;
		}
    }
	return false;
}