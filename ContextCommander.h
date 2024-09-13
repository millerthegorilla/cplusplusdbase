#if !defined (CONTEXTCOMMANDER_H)
#define CONTEXTCOMMANDER_H
// Bartosz Milewski (c) 2000

#include "Command.h"
#include "Win.h"

class ContextCommander;
class database;

namespace Cmd
{
	extern Cmd::Item<ContextCommander> const ContextTable [];
}

typedef Cmd::VectorExec<ContextCommander> ContextCmdVector;

class ContextCommander
{
public:
	ContextCommander (Win::Dow win, database & database);

    void Database_About ();
	Cmd::Status can_Database_About () const { return Cmd::Enabled; }

private:
	Win::Dow _win;
	database & _database;
};

#endif
