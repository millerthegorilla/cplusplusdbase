#include "ContextCommander.h"
// Bartosz Milewski (c) 2000
#include "Model\database.h"
#include "AboutDlg.h"
#include "NewDlg.h"
#include "resource.h"
#include "Params.h"
#include "Exception.h"

namespace Cmd
{
	const Cmd::Item<ContextCommander> ContextTable [] =
	{
		{ "Database_About",	&ContextCommander::Database_About,	
							&ContextCommander::can_Database_About,	
		  "About this program"},
		{ 0, 0, 0}
	};
}

ContextCommander::ContextCommander (Win::Dow win, database & database)
 : _win (win), _database (database)
{}

void ContextCommander::Database_About ()
{
	AboutCtrl ctrl;
	Dialog::Modal dialog (_win, IDD_ABOUT, ctrl);
}
