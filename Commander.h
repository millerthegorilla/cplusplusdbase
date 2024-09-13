#if !defined (COMMANDER_H)
#define COMMANDER_H
// Bartosz Milewski (c) 2000

#include "Command.h"
#include "Win.h"

class Commander;
class database;

namespace Cmd
{
	extern Cmd::Item<Commander> const Table [];
}

typedef Cmd::VectorExec<Commander> CmdVector;

class Commander
{
public:
	Commander (Win::Dow win, database & database);

	void Database_New ();
	Cmd::Status can_Database_New () const;
	void Database_Open ();
	Cmd::Status can_Database_Open () const { return Cmd::Enabled; }
	void Database_Save ();
	Cmd::Status can_Database_Save () const { return Cmd::Enabled; }
    void Database_About ();
	Cmd::Status can_Database_About () const { return Cmd::Enabled; }
    void Database_Exit ();
	Cmd::Status can_Database_Exit () const { return Cmd::Enabled; }
	void Record_Add ();
	Cmd::Status can_Record_Add () const;
	void Record_Remove ();
	Cmd::Status can_Record_Remove () const;
	void Record_DisplayAll ();
	Cmd::Status can_Record_DisplayAll () const;
	void Record_ViewSet ();
	Cmd::Status can_Record_ViewSet () const;
	void Record_Search ();
	Cmd::Status can_Record_Search () const;
private:
	Win::Dow _win;
	database & _database;
};

#endif
