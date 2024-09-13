#if !defined (CHILDWIN_H)
#define CHILDWIN_H
// (c) James Miller 2005
#include "controls.h"

namespace Win
{
	class ChildWin: public Win::Dow 
	{
	public:
		ChildWin (HWND win = 0)
			: Win::Dow (win)
		{}

	};

}
#endif
