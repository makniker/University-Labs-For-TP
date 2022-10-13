#include "CheckFunctions.hpp"

#include <cmath>
#include <algorithm>
#include <limits>

bool yermakov::isParallel(const point_t& a, const point_t& b, const point_t& c)
{
  return (a.y_ == b.y_) || (b.y_ == c.y_);
}

bool yermakov::isTriangle(const point_t& a, const point_t& b, const point_t& c)
{
  double perimetr = getDistance(a, b) + getDistance(b, c) + getDistance(c, a);
  return perimetr > 2 * std::fmax(std::fmax(getDistance(a, b), getDistance(b, c)), getDistance(c, a));
}

bool yermakov::isRightTriangle(const point_t& a, const point_t& b, const point_t& c)
{
  double hyp = getDistance(a, b);
  return hyp == std::hypot(getDistance(a, c), getDistance(b, c));
}

bool yermakov::isOnOneLine(const point_t& a, const point_t& b, const point_t& c)
{
  bool yLine = std::max(std::max(a.x_, b.x_), c.x_) == std::min(std::min(a.x_, b.x_), c.x_);
  bool xLine = std::max(std::max(a.y_, b.y_), c.y_) == std::min(std::min(a.y_, b.y_), c.y_);
  return xLine && yLine;
}

bool yermakov::isOneOfRightTriangle(const point_t& a, const point_t& b, const point_t& c)
{
  return isTriangle(a, b, c) && (isRightTriangle(a, b, c) || isRightTriangle(a, c, b));
}

bool yermakov::isOnePointBelowOther(const point_t& a, const point_t& c)
{
  return a.x_ < c.x_ || a.y_ < c.y_;
}

double yermakov::countNumberOfSides(const point_t& a, const point_t& b, const point_t& c)
{
  double radiusOfInscribedCircle = calculateradiusOfInscribedCircle(a, b, c);
  double radiusOfCircumCircle = calculateRadiusOfCircumCircle(a, b, c);
  double halfCos = (radiusOfInscribedCircle / radiusOfCircumCircle);
  double angle = std::acos(halfCos) * 2 * 180 / (std::atan(1) * 4);
  double n = 2 / (1 - (angle / 180));
  return n;
}

bool yermakov::isCorrectNumberOfSides(const point_t& a, const point_t& b, const point_t& c)
{
  double epsilon = std::numeric_limits< double >::epsilon() * 10;
  return ((countNumberOfSides(a, b, c) - static_cast< int >(countNumberOfSides(a, b, c))) < epsilon);
}

double yermakov::calculateRadiusOfCircumCircle(const point_t& a, const point_t& b, const point_t& c)
{
  return isRightTriangle(a, b, c) ? getDistance(a, b) : getDistance(a, c);
}

double yermakov::calculateradiusOfInscribedCircle(const point_t& a, const point_t& b, const point_t& c)
{
  return isRightTriangle(a, b, c) ? getDistance(a, c) : getDistance(a, b);
}
