#if !defined (CONTEXTMENUTABLE_H)
#define CONTEXTMENUTABLE_H

#include <vector>
#include "Menu.h"

namespace Menu
{
	const Item ContextItem1 = {END,		0,			0};
	const Item ContextItem2 = {CMD,		"&About...","Database_About"};
	const Item ContextItem3 = {SEPARATOR,	0,			0};
	const Item ContextItem4 = {END,		0,			0};

}


#endif