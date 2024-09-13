#if !defined (NEWDLG_H)
#define NEWDLG_H

#pragma warning (disable:4786)	//Disable warning about name truncated to 255 chars in debug info


#include "Dialog.h"
#include "Edit.h"
#include "Button.h"
#include "ComboBox.h"
#include "Static.h"
#include "Params.h"
#include "resource.h"
#include <vector>
#include <stdlib.h>

class NewCtrl : public Dialog::ModalController
{
public:
	NewCtrl();
	void OnInitDialog () throw (Win::Exception);
	bool OnCommand (int ctrlId, int notifyCode) throw (Win::Exception);
	std::vector <TREETYPE>	GetTypeArray() const { return _typearray;}
	std::vector <std::string> GetFieldNames () const { return _fieldnames;}

private:
	Win::Edit		_edit;
	Win::Edit		_edit2;	
	Win::Button		_button;
	Win::Button		_button2;
	Win::ComboBox	_combo;
	Win::Static		_static;

	std::vector<TREETYPE>	_typearray;
	std::vector<std::string> _fieldnames;
	int				_step;
	int				_numoffields;
};

#endif