#include "MenuTable.h"
// Bartosz Milewski (c) 2000

namespace Menu
{
	//
	// Menu Popup Items
	//

	const Item databaseItems [] =
	{
		{CMD,		"&New",		"Database_New"},
		{CMD,		"&Open",	"Database_Open"},
		{CMD,		"&Save",	"Database_Save"},
		{SEPARATOR,	0,			0},
		{CMD,		"&About...","Database_About"},
		{SEPARATOR,	0,			0},
		{CMD,		"E&xit",	"Database_Exit"},
		{END,		0,			0}
	};
	const Item recordItems [] =
	{
		{CMD,		"&Add",		"Record_Add"},
		{CMD,		"&Remove",	"Record_Remove"},
		{CMD,		"&Display All",	"Record_DisplayAll"},
		{CMD,		"&View Set",	"Record_ViewSet"},
		{CMD,		"&Search",	"Record_Search"},
		{END,		0,			0}
	};

	//
	// Menu Bar Items
	//

	const BarItem barItems [] =
	{
		{POP,   "&Database",	"Database",	databaseItems},
		{POP,	"&Records",		"Records",	recordItems},
		{END,   0,			0,			0}
	};
}
