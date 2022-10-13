#include <string>
#include <memory>

#include "Shape.hpp"

namespace yermakov
{
  double getNumber(std::string, std::size_t);
  point_t getPoint(std::string);
  std::string skipPoint(std::string);
  bool isRightShape(std::string);
  std::string getType(std::string);
  bool checkObject(std::string);
  std::unique_ptr< Shape > createShapeObject(std::string);
  point_t getScalePoint(std::string);
  double getScaleFactor(std::string);
  bool checkIsArgsRight(std::string, const point_t&, const point_t&, const point_t&);
  bool checkIsArgsRight(std::string, const point_t&, const point_t&);
}
