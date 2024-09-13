// (c) Bartosz Milewski 2000
#include "Control.h"
#include "resource.h"
#include "status.h"
#include "Params.h"
// library
#include "Class.h"
#include "Maker.h"
#pragma warning (disable:4786)
#include "MsgLoop.h"
#include <new.h>

int NewHandler (size_t size)
{
    throw Win::Exception ("Out of memory");
    return 0;
}

void UnexpectedHandler ()
{
	::MessageBox (0, "My First Database", "Unexpected exception", MB_OK | MB_ICONERROR);
	terminate ();
}

int WINAPI WinMain
   (HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow)
{
	_set_new_handler (NewHandler);
	set_unexpected (UnexpectedHandler);
    char className[] = "My first Database";
	try
	{
		Win::ClassMaker winClass (className, hInst);
		winClass.SetIcons (IDI_MAIN);
		winClass.Register ();
		Win::Maker maker (className, hInst);
		maker.SetSize (WIN_WIDTH, WIN_HEIGHT);
		TopController ctrl;
		Win::Dow win = maker.Create (ctrl, "My First Database");
		win.Display (cmdShow);
		Win::MsgPrepro loop;
		return loop.Pump ();
	}
	catch (Win::Exception const & e)
	{
		TheOutput.Error (e.GetMessage ());
	}
	catch (Win::ExitException)
	{
	}
	catch (...)
	{
		TheOutput.Error ("Unknown exception");
	}
	return -1;
}
