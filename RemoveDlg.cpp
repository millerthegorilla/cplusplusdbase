#include "RemoveDlg.h"
// Bartosz Milewski (c) 2000
#include "Dialog.h"
#include "Util.h"


RemoveCtrl::RemoveCtrl(int numberofrecords)
{
	_numOfRecords = numberofrecords;
}

void RemoveCtrl::OnInitDialog () throw (Win::Exception)
{
	_edit.Init (GetWindow (), IDC_RECORDNUM);
	_numRecs.Init (GetWindow (), IDC_NUMOFRECS);
	_numRecs.SetText (ToString(_numOfRecords).c_str());
}

bool RemoveCtrl::OnCommand (int ctrlId, int notifyCode) throw (Win::Exception)
{
    switch(ctrlId)
	{	
	case IDOK:
		{
			_toRemove = atoi(_edit.GetText().c_str ());
			if(_toRemove > 0 && _toRemove <= _numOfRecords)
			{
				EndOk ();
				return true;
			}
        
		}
		break;
	case IDCANCEL:
		{
			EndCancel ();
			return true;
		}
		break;
	}
	return false;
}
