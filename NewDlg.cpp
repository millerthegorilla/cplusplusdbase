#include "NewDlg.h"
//James Miller (c) 2005
#include "Dialog.h"
#include <sstream>
#include "Util.h"

NewCtrl::NewCtrl()
{
	_step = 0;
	_numoffields = 0;
	
}
void NewCtrl::OnInitDialog () throw (Win::Exception)
{
int index;

	_edit.Init (GetWindow (), IDC_EDIT1);
	_edit2.Init(GetWindow (), IDC_FNAMEEDIT);
	_button.Init (GetWindow (), IDC_NEXT);
	_button2.Init (GetWindow (), IDOK);
	_static.Init (GetWindow (), IDC_NEWSTATIC);
	_combo.Init (GetWindow (), IDC_COMBO1);
	index = _combo.AddItem ("String");
	_combo.SetItem (index, (DWORD)STRINGTYPE);
	index = _combo.AddItem ("Integer");
	_combo.SetItem (index, (DWORD)INTTYPE);
	index = _combo.AddItem ("Character");
	_combo.SetItem (index, (DWORD)CHARTYPE);
	index = _combo.AddItem ("Float");
	_combo.SetItem (index, (DWORD)FLOATTYPE);
	_combo.SetCurrentSelection (0);



}

bool NewCtrl::OnCommand (int ctrlId, int notifyCode) throw (Win::Exception)
{

	switch(ctrlId)
	{
	case IDOK:
		if(IsWindowVisible(GetDlgItem(GetWindow(),IDOK)))
		{
			EndOk ();
			return true;
		}
		break;
	case IDCANCEL:
		EndCancel ();
		return true;
		break;
	case IDC_NEXT:
		if(_step == 0)
		{
			_numoffields = atoi(_edit.GetText ().c_str ());
			if(_numoffields)
			{
				_edit.Hide();
				_edit2.Show();
				_combo.Show ();
				
				std::string text = "Enter Name and Data Type for field number 1";
				_static.SetText (text.c_str ());

				_step++;
				break;
			}
			else
			{
				_edit.Clear ();
				break;
			}
		}
		else if(_numoffields != 0 && _step <= _numoffields)
		{
			_fieldnames.push_back(_edit2.GetText());
			_edit2.Clear();
			_typearray.push_back((TREETYPE)_combo.GetCurrentSelectedItem ());
			
			if(_step < _numoffields)
			{
				std::stringstream out;
				out << "Enter Name and Data Type for field number ";
				char buffer[20];
				out << _itoa ( _step + 1,buffer,10);
				_static.SetText (&out.str()[0]);
			}
			else if(_step == _numoffields)
			{
				_static.SetText ("Press OK to continue");
				_button.Hide ();
				_combo.Hide ();
				_edit2.Hide ();
				_button2.Show ();
			}
			_step++;

		}

	}
	return false;
}