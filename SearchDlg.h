#if !defined (SEARCHDLG_H)
#define SEARCHDLG_H
// Bartosz Milewski (c) 2000
#include "Dialog.h"
#include "Edit.h"
#include <string>

class SearchCtrl : public Dialog::ModalController
{
public:
	void OnInitDialog () throw (Win::Exception);
    bool OnCommand (int ctrlId, int notifyCode) throw (Win::Exception);
	std::string GetSearchString() const {return _searchString;}
private:
	std::string _searchString;
	Win::Edit	_edit;
};

#endif