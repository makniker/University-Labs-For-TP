#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <functional>
#include <stdexcept>

#include <Messages.hpp>

#include "Commands.hpp"
#include "BasicShapes.hpp"

int main(int argc, char* argv[])
{
  std::ifstream inputFile;
  if (argc == 2)
  {
    inputFile.open(argv[1]);
    if (!inputFile.is_open())
    {
      std::cerr << "Cannot open file\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "Wrong number of args\n";
    return 1;
  }

  using in = std::istream_iterator< yermakov::Polygon >;
  using funcObj = std::function< void(std::ostream&, std::vector< yermakov::Polygon >&, const std::string&) >;

  std::vector< yermakov::Polygon > dataArray;
  while (!inputFile.eof())
  {
    if (!inputFile)
    {
      inputFile.clear();
      inputFile.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(in(inputFile), in(), std::back_inserter(dataArray));
  }

  std::map< std::string, funcObj > commandSet
  {
    {"AREA", yermakov::doAREA},
    {"MAX", yermakov::doMAX},
    {"MIN", yermakov::doMIN},
    {"COUNT", yermakov::doCOUNT},
    {"RMECHO", yermakov::doRMECHO},
    {"MAXSEQ", yermakov::doMAXSEQ}
  };

  std::string description;
  while (!std::cin.eof())
  {
    try
    {
      std::getline(std::cin, description);
      std::string command = description.substr(0, description.find_first_of(" "));
      std::string argument = description.substr(description.find_first_of(" ") + 1);
      if (description.empty())
      {
        break;
      }
      else if (argument.empty())
      {
        yermakov::printInvalid(std::cout) << "\n";
        continue;
      }
      commandSet.at(command)(std::cout, dataArray, argument);
    }
    catch (...)
    {
      yermakov::printInvalid(std::cout) << "\n";
    }
  }

  return 0;
}
