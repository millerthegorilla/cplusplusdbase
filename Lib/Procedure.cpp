#include "Procedure.h"
// (c) Bartosz Milewski 2000
#include "Controller.h"
#include "Win.h"
#include "Mouse.h"

// generic window procedure

LRESULT CALLBACK Win::Procedure (HWND win, 
                                 UINT message, 
                                 WPARAM wParam, 
                                 LPARAM lParam)
{
    Controller * pCtrl = Win::GetLong<Controller *> (win);
    switch (message)
    {
    case WM_NCCREATE:
        {
            CreateData const * create = 
                reinterpret_cast<CreateData const *> (lParam);
            pCtrl = static_cast<Controller *> (create->GetCreationData ());
            pCtrl->SetWindowHandle (win);
            Win::SetLong<Controller *> (win, pCtrl);
        }
        break;
	case WM_CREATE:
		if (pCtrl->OnCreate (reinterpret_cast<CreateData const *> (lParam)))
			return 0;
		break;
    case WM_DESTROY:
        // We're no longer on screen
        pCtrl->OnDestroy ();
        return 0;
	case WM_ACTIVATE:
		{
			HWND wndPrev = reinterpret_cast<HWND> (lParam);
			ActiveAction activate (LOWORD (wParam));
			if (pCtrl->OnActivate (activate, HIWORD (wParam) != FALSE, wndPrev))
				return 0;
		}
		break;
	case WM_SETFOCUS:
		{
			HWND wndPrev = reinterpret_cast<HWND> (wParam);
			if (pCtrl->OnFocus (wndPrev))
				return 0;
		}
		break;
	case WM_SIZE:
		if (pCtrl->OnSize (LOWORD (lParam), HIWORD (lParam), wParam))
			return 0;
		break;
	case WM_PAINT:
		if (pCtrl->OnPaint ())
			return 0;
		break;
	case WM_COMMAND:
		if (lParam == 0)
		{
			if (pCtrl->OnCommand (LOWORD (wParam), HIWORD (wParam) == 1))
				return 0;
		}
		else
		{
			HWND hCtrl = reinterpret_cast<HWND>(lParam);
			if (pCtrl->OnControl (hCtrl, LOWORD (wParam), HIWORD (wParam)))
				return 0;
		}
		break;
	case WM_INITMENUPOPUP:
		if (HIWORD (lParam) == 0)
		{
			if (pCtrl->OnInitPopup (reinterpret_cast<HMENU>(wParam), LOWORD (lParam)))
				return 0;
		}
		else // system menu
		{
			if (pCtrl->OnInitSystemPopup (reinterpret_cast<HMENU>(wParam), LOWORD (lParam)))
				return 0;
		}
		break;
	case WM_MENUSELECT:
		if (pCtrl->OnMenuSelect (LOWORD(wParam), HIWORD(wParam), 
					reinterpret_cast<HMENU> (lParam)))
		{
			return 0;
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnMouseMove (p.x, p.y, kState))
				return 0;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnLButtonDown (p.x, p.y, kState))
				return 0;
		}
		break;
	case WM_LBUTTONUP:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnLButtonUp (p.x, p.y, kState))
				return 0;
		}
		break;
	case WM_RBUTTONDOWN:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnRButtonDown (p.x, p.y, kState))
				return 0;
		}
		break;
	case WM_CAPTURECHANGED:
		if (pCtrl->OnCaptureChanged (reinterpret_cast<HWND> (lParam)))
			return 0;
		break;
	case WM_KEYDOWN:
		if (pCtrl->OnKeyDown (wParam, lParam))
			return 0;
		break;
	case WM_HSCROLL:
		if (pCtrl->OnHScroll((int) LOWORD(wParam),(short int) HIWORD(wParam),(HWND) lParam))
			return 0;
		break;
	case WM_VSCROLL:
		if (pCtrl->OnVScroll((int) LOWORD(wParam),(short int) HIWORD(wParam),(HWND) lParam))
			return 0;
		break;
	default:
		if (message >= WM_USER)
		{
			LRESULT result = 0;
			if (pCtrl->OnUserMessage (message, wParam, lParam, result))
				return result;
		}
		break;
    }
    return ::DefWindowProc (win, message, wParam, lParam);
}

// window subclassing procedure

LRESULT CALLBACK Win::SubProcedure (HWND win, 
                                 UINT message, 
                                 WPARAM wParam, 
                                 LPARAM lParam)
{
    SubController * pCtrl = Win::GetLong<SubController *> (win);
    switch (message)
    {
	case WM_SETFOCUS:
		{
			HWND wndPrev = reinterpret_cast<HWND> (wParam);
			if (pCtrl->OnFocus (wndPrev))
				return 0;
		}
		break;
	case WM_KEYDOWN:
		{
			if (pCtrl->OnKeyDown (wParam, lParam))
				return 0;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnLButtonDown (p.x, p.y, kState))
				return 0;
		}
		break;
	case WM_LBUTTONUP:
		{
			POINTS p = MAKEPOINTS (lParam);
			KeyState kState (wParam);
			if (pCtrl->OnLButtonUp (p.x, p.y, kState))
				return 0;
		}
		break;
	}
	return pCtrl->CallPrevProc (message, wParam, lParam);
}