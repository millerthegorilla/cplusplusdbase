#include "Commander.h"
// Bartosz Milewski (c) 2000
#include "Model\database.h"
#include "AboutDlg.h"
#include "NewDlg.h"
#include "DisplayDlg.h"
#include "SearchDlg.h"
#include "RemoveDlg.h"
#include "resource.h"
#include "Params.h"
#include "Exception.h"

namespace Cmd
{
	const Cmd::Item<Commander> Table [] =
	{
		{ "Database_New",	&Commander::Database_New,
							&Commander::can_Database_New,
		  "Create a new Database"},
		{ "Database_Open",  &Commander::Database_Open,
							&Commander::can_Database_Open,
		  "Open an existing Database"},
		{ "Database_Save",  &Commander::Database_Save,
							&Commander::can_Database_Save,
		  "Save the open database"},
		{ "Database_About",	&Commander::Database_About,	
							&Commander::can_Database_About,	
		  "About this program"},
		{ "Database_Exit",	&Commander::Database_Exit,	
							&Commander::can_Database_Exit,	
		  "Exit program"},
		{ "Record_Add",		&Commander::Record_Add,	
							&Commander::can_Record_Add,	
		   "Add a new record"},
		{ "Record_Remove",	&Commander::Record_Remove,	
							&Commander::can_Record_Remove,	
		  "Remove a record"},
		{ "Record_DisplayAll",	&Commander::Record_DisplayAll,	
							&Commander::can_Record_DisplayAll ,	
		  "Display all records"},
		{ "Record_ViewSet",	&Commander::Record_ViewSet,	
							&Commander::can_Record_ViewSet,	
		  "View a single record"},
		{ "Record_Search",	&Commander::Record_Search,	
							&Commander::can_Record_Search,	
		  "Search Records"},
		{ 0, 0, 0}
	};
}

Commander::Commander (Win::Dow win, database & database)
 : _win (win), _database (database)
{}

Cmd::Status Commander::can_Database_New () const
{
	if(_database.IsDataFileOpen())
	{
		return Cmd::Disabled;
	}
	return Cmd::Enabled;
}

void Commander::Database_New ()
{
	NewCtrl ctrl;
	Dialog::Modal dialog (_win, IDD_NEWDBASE, ctrl);
	if(dialog.IsOk())
	{
		_database.NewDataFile(ctrl.GetTypeArray(), ctrl.GetFieldNames());
	}
}

void Commander::Database_Open ()
{
/*	OpenCtrl ctrl;
	Dialog::Modal dialog (_win, IDD_OPENDBASE, ctrl);*/
}

void Commander::Database_Save ()
{

}

void Commander::Database_About ()
{
	AboutCtrl ctrl;
	Dialog::Modal dialog (_win, IDD_ABOUT, ctrl);
}

void Commander::Database_Exit ()
{
	if(_database.IsDataFileOpen ())
	{
		_database.CloseDataFile ();
	}
	throw Win::ExitException ();
}

Cmd::Status Commander::can_Record_Add () const
{
	if(_database.IsDataFileOpen())
	{
		return Cmd::Enabled;
	}
	return Cmd::Disabled;
}

void Commander::Record_Add ()
{
	_win.SendMessage(MSG_RECORDSMSG);
}

Cmd::Status Commander::can_Record_Remove () const
{
	if(_database.IsDataFileOpen())
	{
		return Cmd::Enabled;
	}
	return Cmd::Disabled;
}

void Commander::Record_Remove ()
{
	RemoveCtrl ctrl(_database.GetNumberofRecords());
	Dialog::Modal dialog (_win, IDD_REMOVEDLG, ctrl);
	if(dialog.IsOk())
	{
		_win.SendMessage(MSG_RECORDDEL, ctrl.GetToRemove());
	}
}

Cmd::Status Commander::can_Record_DisplayAll () const
{
	if(_database.IsDataFileOpen() && _database.GetNumberofRecords())
	{
		return Cmd::Enabled;
	}
	return Cmd::Disabled;
}

void Commander::Record_DisplayAll ()
{
	int i = _database.GetNumberofRecords();
	_win.SendMessage(MSG_RECORDSHOW, 1, i);
}

Cmd::Status Commander::can_Record_ViewSet () const
{
	if(_database.IsDataFileOpen())
	{
		return Cmd::Enabled;
	}
	return Cmd::Disabled;
}

void Commander::Record_ViewSet ()
{
	DisplayCtrl ctrl(_database.GetNumberofRecords());
	Dialog::Modal dialog (_win, IDD_DISPLAYDLG, ctrl);
	if(dialog.IsOk())
	{
		_win.SendMessage(MSG_RECORDSHOW, ctrl.GetFrom(), ctrl.GetTo());
	}
}

Cmd::Status Commander::can_Record_Search () const
{
	if(_database.IsDataFileOpen())
	{
		return Cmd::Enabled;
	}
	return Cmd::Disabled;
}

void Commander::Record_Search ()
{
	SearchCtrl ctrl;
	Dialog::Modal dialog (_win, IDD_SEARCHDLG, ctrl);
	if(dialog.IsOk())
	{
		_win.SendMessage(MSG_RECORDFIND, (WPARAM)&ctrl.GetSearchString());
	}
}



