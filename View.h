#if !defined (VIEW_H)
#define VIEW_H
// Bartosz Milewski (c) 2000
#include "ChildControl.h"
#include "MenuTable.h"
#include "StatusBar.h"
#include "ListBox.h"
#include "Edit.h"
#include "Button.h"
#include "Win.h"
#include "Params.h"
#include "ContextMenuTable.h"

class database;

class EditController: public Win::SubController
{
public:
	bool OnKeyDown (int vKey, int flags) throw ();
};

class ButtonController: public Win::SubController 
{
public:
	bool OnLButtonDown (int x, int y, Win::KeyState kState) throw ();
	bool OnLButtonUp (int x, int y, Win::KeyState kState) throw ();
};

class View
{
public:
	View (Win::Dow win, 
		  Cmd::Vector * cmdVector, 
		  Cmd::Vector * contextcmdVector, 
		  database & database,
		  std::vector<Menu::Item const *> contextItems);
	void Init (Win::Dow winTop);
	void Size (int width, int height);
	void RefreshPopup (HMENU menu, int pos)
	{
			_menu.RefreshPopup (menu, pos);
	}
	void SetStatus (char const * str);
	void SetFocus ()
	{
		//_edit.SetFocus ();
	}
	void SendControlMessage(int ControlId, CTRL_MSGS Msg);
	void SetContext(Win::Dow win, int x, int y);
	void AddRecord();
	bool CheckIsContext(HMENU menu);
	void ShowRecord(int recordbegin, int recordend);
	void SearchRecord(std::string * SearchString);
	void RemoveRecord(int toremove);
private:
	std::vector <Win::SimpleCtrl> _vControlVector;
	

	Menu::DropDown	_menu;
	Win::StatusBar	_status;
	Menu::Context	_context;

	ChildController _childCtrl;
	Win::Dow    	_childwin;
/*	EditController	_editCtrl;*/
	Win::Button		_button;
	ButtonController _buttonCtrl;
	Win::Dow		&_win;
	database		&_database;
};
#endif
