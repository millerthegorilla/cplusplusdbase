#if !defined (WIN_H)
#define WIN_H
// (c) Bartosz Milewski 2000

#pragma warning (disable:4786)

#include <windows.h>

namespace Win
{
	class SubController;

	// if the compiler doesn't support member templates
    template <class T>
    inline T GetLong (HWND win, int which = GWL_USERDATA)
    {
        return reinterpret_cast<T> (::GetWindowLong (win, which));
    }

    template <class T>
    inline void SetLong (HWND win, T value, int which = GWL_USERDATA)
    {
        ::SetWindowLong (win, which, reinterpret_cast<long> (value));
    }

	class Dow
	{
	public:
		Dow (HWND win = 0) : _h (win) {}
		void Init (HWND win) { _h = win; }
		operator HWND () const { return _h; }
		Win::Dow GetParent () { return ::GetParent (_h); }
		HINSTANCE GetInstance () const
		{
			return reinterpret_cast<HINSTANCE> (
				::GetWindowLong (_h, GWL_HINSTANCE));
		}
#if 0
		template <class T>
		inline T GetLong (int which = GWL_USERDATA)
		{
			return reinterpret_cast<T> (::GetWindowLong (_h, which));
		}

		template <class T>
		inline void SetLong (T value, int which = GWL_USERDATA)
		{
			::SetWindowLong (_h, which, reinterpret_cast<long> (value));
		}
#endif
		LRESULT SendMessage (UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
		{
			return ::SendMessage (_h, msg, wparam, lparam);
		}
		bool PostMessage (UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
		{
			return ::PostMessage (_h, msg, wparam, lparam) != FALSE;
		}
		void Destroy ()
		{
			::DestroyWindow (_h);
		}
		// Focus
		void SetFocus ()
		{ 
			::SetFocus (_h); 
		}
		bool HasFocus () const
		{
			return ::GetFocus () == _h;
		}
		// Capture
		void CaptureMouse ()
		{
			::SetCapture (_h);
		}
		void ReleaseMouse ()
		{
			if (HasCapture ())
				::ReleaseCapture ();
		}
		bool HasCapture () const
		{
			return ::GetCapture () == _h;
		}
		// Text/Caption
		void SetText (char const * text) 
		{ 
			::SetWindowText (_h, text); 
		}
		int GetText (char * buf, int len) const// len includes null
		{ 
			return ::GetWindowText (_h, buf, len); 
		}
		// Font
		void SetFont (HFONT hFont)
		{
			BOOL fRedraw = TRUE;
			SendMessage (WM_SETFONT, 
						 reinterpret_cast<WPARAM> (hFont), 
						 MAKELPARAM (fRedraw, 0));
		}
		// Window visibility
		void Show (int cmdShow = SW_SHOW) 
		{ 
			::ShowWindow (_h, cmdShow); 
		}
		void Hide () 
		{ 
			::ShowWindow (_h, SW_HIDE); 
		}
		void Update () 
		{ 
			::UpdateWindow (_h); 
		}
		void Display (int cmdShow = SW_SHOW)
		{
			Show (cmdShow);
			Update ();
		}
		void Enable ()
		{
			::EnableWindow (_h, TRUE);
		}
		void Disable ()
		{
			::EnableWindow (_h, FALSE);
		}
		// Moving
		void Move (int x, int y, int width, int height)
		{
			::MoveWindow (_h, x, y, width, height, TRUE);
		}

		void MoveDelayPaint (int x, int y, int width, int height)
		{
			::MoveWindow (_h, x, y, width, height, FALSE);
		}

		void Invalidate()
		{
			::InvalidateRect (_h,0,TRUE);
		}
		
		void StyleAugment(LONG style)
		{
			LONG styleb4 = ::GetWindowLong (_h,GWL_STYLE);
			styleb4 |= style;
			::SetWindowLong (_h,GWL_STYLE, styleb4);
			::SetWindowPos (_h,
							 NULL,
							 0,
							 0,
							 0,
							 0,
							 SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE); 
		}
		
		void GetClientSize (RECT & rect)
		{
			::GetClientRect (_h, &rect);
		}
		// Subclassing
		void SubClass (SubController * ctrl);
		void UnSubClass ();
	protected:
		HWND _h;
	};
}
#endif
