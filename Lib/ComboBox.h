#if !defined (COMBOBOX_H)
#define COMBOBOX_H
// (c) James Miller 2005
#include "controls.h"

namespace Win
{
	class ComboBox: public SimpleCtrl
	{
	public:
		ComboBox (HWND winParent, int id)
			: SimpleCtrl (winParent, id), _winParent(winParent)
		{}

		ComboBox (HWND win = 0) : SimpleCtrl (win) {}

		int AddItem(char * stringtoadd);
		void SetItem(int index, DWORD data);
		DWORD GetCurrentSelectedItem();
		void SetCurrentSelection(int index);

	private:
		HWND	_winParent;
	};
}
#endif