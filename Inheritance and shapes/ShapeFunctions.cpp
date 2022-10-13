#include "ShapeFunctions.hpp"

#include <cmath>
#include <ostream>

#include "Rectangle.hpp"
#include "Regular.hpp"
#include "Parallelogram.hpp"
#include "InputProcessingFunctions.hpp"

std::ostream& yermakov::printArray(std::ostream& out, arr&& sArr, std::size_t size)
{
  double allArea = 0;
  for (size_t i = 0; i < size; i++)
  {
    allArea += sArr[i]->getArea();
  }
  out << allArea;
  for (size_t i = 0; i < size; i++)
  {
    out << sArr[i]->getFrameRect();
  }
  return out << "\n";
}

std::unique_ptr< yermakov::Shape > yermakov::isoScale(shapePtr&& shObj, const point_t& cp, double sf)
{
  shObj->scale(sf);
  double moveX = cp.x_ * (1 - sf) + sf * shObj->getFrameRect().pos_.x_;
  double moveY = cp.y_ * (1 - sf) + sf * shObj->getFrameRect().pos_.y_;
  yermakov::point_t newCenter(moveX, moveY);
  shObj->move(newCenter);
  return std::move(shObj);
}

yermakov::arr&& yermakov::scaleArray(arr&& sArr, std::size_t size, const point_t& cp, double sf)
{
  for (size_t i = 0; i < size; i++)
  {
    sArr[i] = std::move(isoScale(std::move(sArr[i]), cp, sf));
  }
  return std::move(sArr);
}

void yermakov::makeArray(yermakov::descArr&& arrayOfPoints, std::string description)
{
  description = description.substr(description.find_first_of(" ") + 1);
  std::size_t count = 0;
  std::size_t numOfPoints = 3;
  while (!description.empty())
  {
    pushBack< point_t, GoldenRatio >(std::move(arrayOfPoints), count, numOfPoints, getPoint(description));
    description = skipPoint(description);
  }
}

std::unique_ptr< yermakov::Shape > yermakov::createParallelogram(descArr descr)
{
  return std::make_unique< Parallelogram >(descr[0], descr[1], descr[2]);
}

std::unique_ptr< yermakov::Shape > yermakov::createRegular(descArr descr)
{
  return std::make_unique< Regular >(descr[0], descr[1], descr[2]);
}

std::unique_ptr< yermakov::Shape > yermakov::createRectangle(descArr descr)
{
  return std::make_unique< Rectangle >(descr[0], descr[1]);
}
