#ifndef  COMMAND_HH
#define  COMMAND_HH

#include <cstdio>
#include <sstream>
#include <vector>


bool ExecPreprocesor( const char* NazwaPliku, std::istringstream &IStrm4Cmds );

void addLibs( std::vector<std::string> names );

void executeCmdFile( const char* fname );

#endif