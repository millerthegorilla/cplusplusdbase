#if !defined (ICON_H)
#define ICON_H
// (c) Bartosz Milewski 2000
#include <windows.h>

namespace Win
{
	class Icon
	{
	public:
	    Icon (HINSTANCE hInst, 
	          int id, 
	          int dx = 0, 
	          int dy = 0, 
	          unsigned flag = LR_DEFAULTCOLOR)
	    {
	        Load (hInst, id, dx, dy, flag);
	    }
	    ~Icon ();
	    operator HICON () const { return _h; }
	protected:
	    Icon () : _h (0) {}
	    void Load (HINSTANCE hInst, 
	            int id, 
	            int dx = 0, 
	            int dy = 0, 
	            unsigned flag = LR_DEFAULTCOLOR);
	protected:
	    HICON _h;
	};

	class SmallIcon: public Icon
	{
	public:
		SmallIcon () {}
		SmallIcon (HINSTANCE hInst, int id);
		void Load (HINSTANCE hInst, int id);
	};

	class StdIcon: public Icon
	{
	public:
		StdIcon () {}
		StdIcon (HINSTANCE hInst, int id);
		void Load (HINSTANCE hInst, int id);
	};
}

#endif
