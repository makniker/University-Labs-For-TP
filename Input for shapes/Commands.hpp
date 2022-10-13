#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <string>

#include "BasicShapes.hpp"

namespace yermakov
{
  void doAREA(std::ostream&, std::vector< Polygon >&, const std::string&);
  void doMAX(std::ostream&, std::vector< Polygon >&, const std::string&);
  void doMIN(std::ostream&, std::vector< Polygon >&, const std::string&);
  void doCOUNT(std::ostream&, std::vector< Polygon >&, const std::string&);
  void doRMECHO(std::ostream&, std::vector< Polygon >&, const std::string&);
  void doMAXSEQ(std::ostream&, std::vector< Polygon >&, const std::string&);
}

#endif
