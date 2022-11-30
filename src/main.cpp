#include "command.hh"
#include "xmlhandler.hh"
#include "client.hh"

using namespace std;

int main()
{

	Configuration   Config;

   	if (!ReadFile("config/config.xml",Config)) return 1;

	startClient( Scene( Config.getCubes() ) );

	addLibs(Config.getLibraries());

	executeCmdFile("command.txt");

	return 0;
}
