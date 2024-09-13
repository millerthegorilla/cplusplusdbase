#include "ComboBox.h"

using namespace Win;

int ComboBox::AddItem (char *stringtoadd)
{ 
	return SendMessage(CB_ADDSTRING,
                0,
                (LPARAM) (LPCTSTR)stringtoadd);
}

void ComboBox::SetItem (int index, DWORD data)
{
	SendMessage(CB_SETITEMDATA, (WPARAM)index, (LPARAM)data);
}

DWORD ComboBox::GetCurrentSelectedItem ()
{
	int index;
	index = SendMessage(CB_GETCURSEL, 0, 0L);
	return SendMessage(CB_GETITEMDATA, (WPARAM)index, 0);
}

void ComboBox::SetCurrentSelection (int index)
{
	SendMessage(CB_SETCURSEL, (WPARAM)index, 0);
}