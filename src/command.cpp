#include "command.hh"

#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <memory>
#include <map>
#include <limits>
#include "Interp4Command.hh"
#include "LibInterface.hh"
#include "MobileObj.hh"
#include "command.hh"

using namespace std;

#define LINE_SIZE 500
#define LIMIT numeric_limits<streamsize>::max()

map<string,shared_ptr<LibInterface>> libs;


bool ExecPreprocesor( const char* NazwaPliku, istringstream &IStrm4Cmds )
{
	string Cmd4Preproc = "cpp -P ";
	char Line[LINE_SIZE];
	ostringstream OTmpStrm;
	
	Cmd4Preproc += NazwaPliku;
	FILE* pProc = popen(Cmd4Preproc.c_str(),"r");
	
	if (!pProc) return false;
	
	while (fgets(Line,LINE_SIZE,pProc)) {
		OTmpStrm << Line;
	}
	
	IStrm4Cmds.str(OTmpStrm.str());
	
	return pclose(pProc) == 0;
}


void printPluginInfo( Interp4Command* pCmd ){
	cout << endl;
	cout << pCmd->GetCmdName() << endl;
	cout << endl;
	pCmd->PrintSyntax();
	cout << endl;
	pCmd->PrintCmd();
	cout << endl;
}

void addLib( string name ){
	string file = name;
	shared_ptr<LibInterface> libp( new LibInterface(file.c_str()) );
	int p = name.find('4')+1;
	int k = name.find('.')-p;
	libs[name.substr(p,k)] = libp;
}

void addLibs( vector<string> names ){
	for( string name: names  )
		addLib(name);
}

void executeCmdFile( const char* fname ){
    istringstream cmds;
	ExecPreprocesor(fname,cmds);
	while( cmds.peek() != EOF ){
		string cmd;
		cmds >> cmd;
		if( libs[cmd] != NULL ){
				Interp4Command* pCmd = libs[cmd]->pCreateCmd();
				pCmd->ReadParams(cmds);
				printPluginInfo( pCmd );
				delete pCmd;
		}
		else cout<<"Brak biblioteki " <<  cmd <<endl;

		cmds.ignore(LIMIT,'\n');
	}
}