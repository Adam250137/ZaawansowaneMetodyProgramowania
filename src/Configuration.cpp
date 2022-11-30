#include "Configuration.hh"

using namespace std;

void Configuration::addLibrary(std::string name){
    _Libraries.push_back(name);
}

void Configuration::addCube( Cube obj ){
    _Cubes.push_back(obj);
}

vector<string> Configuration::getLibraries(){
    return _Libraries;
}

vector<Cube> Configuration::getCubes(){
    return _Cubes;
}