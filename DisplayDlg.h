#if !defined (DISPLAYDLG_H)
#define DISPLAYDLG_H
// Bartosz Milewski (c) 2000
#include "Dialog.h"
#include "Edit.h"
#include "resource.h"

class DisplayCtrl : public Dialog::ModalController
{
public:
	DisplayCtrl(int numberofrecords);
	void OnInitDialog () throw (Win::Exception);
    bool OnCommand (int ctrlId, int notifyCode) throw (Win::Exception);
	int GetFrom () const { return _from;}
	int GetTo () const { return _to;}
private:
	Win::StaticText _numRecs;
	Win::Edit	_fromEdit;
	Win::Edit	_toEdit;
	int			_from;
	int			_to;
	int			_numOfRecords;
};

#endif