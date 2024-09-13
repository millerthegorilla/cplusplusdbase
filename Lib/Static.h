#if !defined (STATIC_H)
#define STATIC_H
// (c) James Miller 2005
#include "controls.h"

namespace Win
{
	class Static: public SimpleCtrl
	{
	public:
		Static (HWND winParent, int id)
			: SimpleCtrl (winParent, id), _winParent(winParent)
		{}

		Static (HWND win = 0) : SimpleCtrl (win) {}

	private:
		HWND	_winParent;
	};

	class StaticMaker: public ControlMaker
	{
	public:
		StaticMaker (HWND winParent, int id) : ControlMaker ("STATIC", winParent, id)
		{
			_style = SS_CENTER;
		}
		
	};
}
#endif