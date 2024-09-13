#if !defined (PROCEDURE_H)
#define PROCEDURE_H
// (c) Bartosz Milewski 2000
#include <windows.h>

namespace Win
{
    class CreateData: public CREATESTRUCT
    {
    public:
        void * GetCreationData () const { return lpCreateParams; }
        int GetHeight () const { return cy; }
        int GetWidth () const { return cx; }
        int GetX () const { return x; }
        int GetY () const { return y; }
        char const * GetWndName () const { return lpszName; }
    };

	class ActiveAction
	{
	public:
		ActiveAction (int code)
			: _code (code)
		{}

		bool IsActive () const { return _code == WA_ACTIVE; }
		bool IsClickActive () const { return _code == WA_CLICKACTIVE; }
		bool IsInActive () const { return _code == WA_INACTIVE; }

	private:
		int	_code;
	};

	// Window procedures

	typedef LRESULT (CALLBACK * ProcPtr)
		(HWND win, UINT message, WPARAM wParam, LPARAM lParam);


	LRESULT CALLBACK Procedure
		(HWND win, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK SubProcedure
		(HWND win, UINT message, WPARAM wParam, LPARAM lParam);
}

#endif
