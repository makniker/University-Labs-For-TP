#include "InputProcessingFunctions.hpp"

#include <iostream>
#include <stdexcept>

#include "CheckFunctions.hpp"
#include "Rectangle.hpp"
#include "Regular.hpp"
#include "Parallelogram.hpp"

double yermakov::getNumber(std::string descr, std::size_t firstPos)
{
  return std::atof(descr.substr(firstPos, descr.find_first_of(" ", firstPos)).c_str());
}

yermakov::point_t yermakov::getPoint(std::string description)
{
  std::size_t firstPos = 0;
  double x = getNumber(description, firstPos);
  firstPos = description.find(" ") + 1;
  double y = getNumber(description, firstPos);
  yermakov::point_t A(x, y);
  return A;
}
std::string yermakov::skipPoint(std::string description)
{
  if (description.find_first_of(" ") == std::string::npos)
  {
    return "";
  }
  description = description.substr(description.find_first_of(" ") + 1);
  description = description.substr(description.find_first_of(" ") + 1);
  return description;
}

bool yermakov::isRightShape(std::string description)
{
  std::string shape = yermakov::getType(description);
  return shape == "REGULAR" || shape == "PARALLELOGRAM" || shape == "RECTANGLE";
}

std::string yermakov::getType(std::string description)
{
  return description.substr(0, description.find_first_of(" "));
}

yermakov::point_t yermakov::getScalePoint(std::string descr)
{
  descr = descr.substr(descr.find_first_of(" ") + 1);
  return getPoint(descr);
}

double yermakov::getScaleFactor(std::string descr)
{
  double factor = getNumber(descr, descr.find_last_of(" "));
  return factor;
}
