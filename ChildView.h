#if !defined (CHILDVIEW_H)
#define CHILDVIEW_H
// Bartosz Milewski (c) 2000
#include "MenuTable.h"
#include "StatusBar.h"
#include "ListBox.h"
#include "Edit.h"
#include "Button.h"
#include "Win.h"
#include "Params.h"
#include "ContextMenuTable.h"
#include "Static.h"
#include "Tools.h"
#include <list>

class database;


class ThisEditController : public Win::SubController 
{
public:
	bool OnKeyDown (int vKey, int flags) throw ();

};



class ThisButtonController: public Win::SubController 
{
public:
	bool OnLButtonDown (int x, int y, Win::KeyState kState) throw ();
	bool OnLButtonUp (int x, int y, Win::KeyState kState) throw ();
};

class ChildView
{
public:
	ChildView (Win::Dow win,  
		  Cmd::Vector * contextcmdVector, 
		  std::vector<Menu::Item const *> contextItems);
	~ChildView();
	void Size (int width, int height);
	void SetFocus ()
	{
		//_edit.SetFocus ();
	}
	void SendControlMessage (int ControlId, CTRL_MSGS Msg);
	void SetContext (Win::Dow win, int x, int y);
	void SetHScrollBar (int scrollcode, short scrollpos, HWND scrollHwnd);
	void SetVScrollBar (int scrollcode, short scrollpos, HWND scrollHwnd);
	void MakeTable (int numofrows = 1);
	void Redraw ();
	void AddButton ();
	void SetDbase (database * database);
	void ButtonPressed();
	void DestroyTable ();
	void ShowRecords(int recordbegin, int recordend);
	void ShowSearchRecords(std::vector<int> & resultlist);
	void SetRecordLabel();
	void SetScrollBars();
	void MoveContents();
	void SearchRecord(std::string * SearchString);
	void RemoveRecord(int toremove);
private:
	std::vector <Win::Edit> _vControlVector;
	
	int _charWidth, _charHeight;
	int _columnWidth;
	int _firstColumnWidth;
	int _rowHeight;
	int _labelHeight;
	Font::OemFixed  _font;
	Font::SysFont _font2;

	Menu::Context	_context;
	int				_scrollHPos;
	int				_scrollVPos;
	int				_scrollHMax;
	int				_scrollVMax;
	
	Win::Edit		* _edit;
	
	ThisEditController	* _editCtrl;
	int				_editPosX;
	int				_editPosY;

	ThisButtonController _buttonCtrl;
	Win::Button		_button;
	bool			_buttonPresent;
	
	Win::StaticText * _columnLabels;
	Win::StaticText * _rowLabels;
	Win::StaticText * _cornerLabel;

	int				_numOfColumns;
	int				_numOfRows;
	
	Win::Dow		_win;
	database		*_database;
};
#endif