#if !defined (REMOVEDLG_H)
#define REMOVEDLG_H

#include "Dialog.h"
#include "Edit.h"
#include "resource.h"

class RemoveCtrl : public Dialog::ModalController
{
public:
	RemoveCtrl(int numberofrecords);
	void OnInitDialog () throw (Win::Exception);
    bool OnCommand (int ctrlId, int notifyCode) throw (Win::Exception);
	int GetToRemove() const { return _toRemove; }
private:
	Win::Edit	_edit;
	Win::StaticText _numRecs;
	int			_numOfRecords;
	int			_toRemove;
};

#endif