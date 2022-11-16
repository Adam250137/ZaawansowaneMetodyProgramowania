#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <memory>
#include <map>
#include "Interp4Command.hh"
#include "LibInterface.hh"
#include "MobileObj.hh"

#include <cstdio>
#define LINE SIZE 500

bool ExecPreprocesor( const char ∗ NazwaPliku, istringstream &IStrm4Cmds )
{
	string Cmd4Preproc = ”cpp -P ”;
	char Line[LINE SIZE];
	ostringstream OTmpStrm;
	
	Cmd4Preproc += NazwaPliku;
	FILE∗ pProc = popen(Cmd4Preproc.c str(),”r”);
	
	if (!pProc) return false;
	
	while (fgets(Line,LINE SIZE,pProc)) {
		OTmpStrm << Line;
	}
	
	IStrm4Cmds.str(OTmpStrm.str());
	
	return pclose(pProc) == 0;
}

using namespace std;

void printPluginInfo( Interp4Command* pCmd ){
	cout << endl;
	cout << pCmd->GetCmdName() << endl;
	cout << endl;
	pCmd->PrintSyntax();
	cout << endl;
	pCmd->PrintCmd();
	cout << endl;
}

int main()
{

	shared_ptr<LibInterface> liMove( new LibInterface("libInterp4Move.so") );
	shared_ptr<LibInterface> liTest( new LibInterface("libInterp4Test.so") );
	
	map<string,shared_ptr<LibInterface>> libs;
	libs["move"] = liMove;
	libs["test"] = liTest;


	while(true){
		string text;
		cin >> text;
		
		if( text == "exit" ) return 0;
		
		Interp4Command *pCmd = libs[text]->pCreateCmd();

		printPluginInfo( pCmd );
		
		delete pCmd;
	}	
}
