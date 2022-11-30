#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "Cube.hh"
#include <vector>
#include <string>

class Configuration {
  
  std::vector<std::string> _Libraries;
  std::vector<Cube> _Cubes;

public:
  void addLibrary(std::string name);
  void addCube( Cube obj );
  std::vector<std::string> getLibraries();
  std::vector<Cube> getCubes();
  
};

#endif
