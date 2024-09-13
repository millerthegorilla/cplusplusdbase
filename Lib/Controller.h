#if !defined (CONTROLLER_H)
#define CONTROLLER_H
// (c) Bartosz Milewski 2000
#include "Win.h"
#include "Mouse.h"
#include "Procedure.h"

namespace Win
{
    class Controller
    {
        friend LRESULT CALLBACK Procedure (HWND win, 
                        UINT message, WPARAM wParam, LPARAM lParam);
	protected:
        void SetWindowHandle (HWND win) { _h.Init (win); }
    public:
		virtual ~Controller () {}
		virtual bool OnCreate (CreateData const * create) throw ()
			{ return false; }
        virtual bool OnDestroy () throw ()
			{ return false; }
		virtual bool OnActivate (ActiveAction activate, bool isMinimized, Win::Dow prevWnd) throw ()
			{ return false; }
		virtual bool OnFocus (Win::Dow winPrev) throw ()
			{ return false; }
		virtual bool OnSize (int width, int height, int flag) throw ()
			{ return false; }
		virtual bool OnPaint () throw ()
			{ return false; }

		virtual bool OnCommand (int cmdId, bool isAccel) throw ()
			{ return false; }
		virtual bool OnControl (Win::Dow control, int controlId, int notifyCode) throw ()
			{ return false; }
		virtual bool OnInitPopup (HMENU menu, int pos) throw ()
			{ return false; }
		virtual bool OnInitSystemPopup (HMENU menu, int pos) throw ()
			{ return false; }
		virtual bool OnMenuSelect (int id, int flags, HMENU menu) throw ()
			{ return false; }
		// Mouse
		virtual bool OnMouseMove (int x, int y, KeyState kState) throw ()
			{ return false; }
		virtual bool OnLButtonDown (int x, int y, KeyState kState) throw ()
			{ return false; }
		virtual bool OnLButtonUp (int x, int y, KeyState kState) throw ()
			{ return false; }
		virtual bool OnRButtonDown (int x, int y, KeyState kState) throw ()
			{ return false; }
		virtual bool OnCaptureChanged (Win::Dow newCaptureWin) throw ()
			{ return false; }
		// Keyboard
		virtual bool OnKeyDown (int vKey, int flags) throw ()
			{ return false; }
		virtual bool OnHScroll (int scrollcode, short int scrollpos, HWND scrollHwnd) throw ()
			{ return false; }
		virtual bool OnVScroll (int scrollcode, short int scrollpos, HWND scrollHwnd) throw ()
			{ return false; }
		virtual bool OnUserMessage (UINT msg, 
									WPARAM wParam, 
									LPARAM lParam, 
									LRESULT & result) throw ()
			{ return false; }
    protected:
        Win::Dow  _h;
    };

	class SubController: public Controller
	{
	public:
		SubController () : _prevProc (0), _prevController (0) {}
		void Init (HWND win, ProcPtr prevProc, Controller * prevCtrl)
		{
			SetWindowHandle (win);
			_prevProc = prevProc;
			_prevController = prevCtrl;
		}
		LRESULT CallPrevProc (UINT message, WPARAM wParam, LPARAM lParam)
		{
			return ::CallWindowProc (_prevProc, _h, message, wParam, lParam);
		}
		ProcPtr GetPrevProc ()
		{
			return _prevProc;
		}
		Controller * GetPrevController ()
		{
			return _prevController;
		}
	protected:
		ProcPtr _prevProc;
		Controller * _prevController;
	};
}
#endif
