#if !defined (PARAMS_H)
#define PARAMS_H
// Bartosz Milewski (c) 2000
#include <windows.h>

const UINT MSG_RECORDSMSG  = WM_USER;
const UINT MSG_CONTROLMSG = WM_USER + 1;
const UINT MSG_INVALIDATE = WM_USER + 2;
const UINT MSG_ADDABUTTON = WM_USER + 3;
const UINT MSG_ADDDBASPTR = WM_USER + 4;
const UINT MSG_BUTTONPRES = WM_USER + 5;
const UINT MSG_ADDSCROLLMSG = WM_USER + 6;
const UINT MSG_RECORDSHOW = WM_USER + 7;
const UINT MSG_RECORDFIND = WM_USER + 8;
const UINT MSG_RECORDDEL  = WM_USER + 9;

enum TREETYPE
{
	STRINGTYPE,
	INTTYPE,
	CHARTYPE,
	FLOATTYPE,
	TYPEERROR
};

enum CTRL_MSGS
{
	CTRL_ENABLE,
	CTRL_DISABLE,
	CTRL_HIDE,
	CTRL_SHOW
};

enum
{
	LABEL_CHARS = 18, 
};

enum
{
	WIN_WIDTH = 400,
	WIN_HEIGHT = 400
};

#endif
