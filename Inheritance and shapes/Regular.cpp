#include "Regular.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

#include "CheckFunctions.hpp"

yermakov::Regular::Regular(const point_t& a, const point_t& b, const point_t& c):
  a_(a),
  b_(b),
  c_(c)
{
  bool isRightTriangle = isOneOfRightTriangle(a, b, c);
  bool isCorrectSides = isCorrectNumberOfSides(a, b, c);
  if (!isRightTriangle || !isCorrectSides || isOnOneLine(a, b, c))
  {
    throw std::logic_error("Wrong args!");
  }
}

double yermakov::Regular::getArea() const
{
  double r1 = std::pow(calculateRadiusOfCircumCircle(a_, b_, c_), 2);
  double r2 = std::pow(calculateradiusOfInscribedCircle(a_, b_, c_), 2);
  double thirdSide = std::sqrt(r1 - r2);
  return countNumberOfSides(a_, b_, c_) * calculateradiusOfInscribedCircle(a_, b_, c_) * thirdSide;
}

yermakov::rectangle_t yermakov::Regular::getFrameRect() const
{
  double r2 = calculateRadiusOfCircumCircle(a_, b_, c_);
  double r1 = calculateradiusOfInscribedCircle(a_, b_, c_);
  double cos = r1 / r2;
  double angle = 2 * (4 * std::atan(1)) / countNumberOfSides(a_, b_, c_);
  double angleCord = std::acos(cos);
  double Ry = getDistance(a_, b_) == r2 ? b_.y_ : c_.y_;
  double rY = getDistance(a_, b_) == r2 ? c_.y_ : b_.y_;
  double r = Ry < rY ? 2 * r1 : r2;
  double minX = a_.x_ + r * std::cos(angleCord);
  double maxX = a_.x_ + r * std::cos(angleCord);
  double minY = a_.y_ + r * std::sin(angleCord);
  double maxY = a_.y_ + r * std::sin(angleCord);
  for (std::size_t i = 0; i < countNumberOfSides(a_, b_, c_); i++)
  {
    double x = a_.x_ + r * std::cos(angleCord + i * angle);
    double y = a_.y_ + r * std::sin(angleCord + i * angle);
    maxX = std::max(maxX, x);
    minX = std::min(minX, x);
    minY = std::min(minY, y);
    maxY = std::max(maxY, y);
  }
  point_t center = {(maxX + minX) / 2, (maxY + minY) / 2};
  rectangle_t frameRect(std::abs(maxX - minX), std::abs(maxY - minY), center);
  return frameRect;
}

void yermakov::Regular::move(double x, double y)
{
  point_t a = a_;
  point_t b = b_;
  point_t c = c_;
  yermakov::move(a, x, y);
  yermakov::move(b, x, y);
  yermakov::move(c, x, y);
  Regular tmp(a, b, c);
  swap(tmp);
}

void yermakov::Regular::move(const point_t& newCenter)
{
  move(newCenter.x_ - a_.x_, newCenter.y_ - a_.y_);
}

void yermakov::Regular::doScale(double factor)
{
  point_t a = a_;
  point_t b = b_;
  point_t c = c_;
  yermakov::scale(a, a_, factor);
  yermakov::scale(b, a_, factor);
  yermakov::scale(c, a_, factor);
  Regular tmp(a, b, c);
  swap(tmp);
}

void yermakov::Regular::swap(Regular& other)
{
  std::swap(a_, other.a_);
  std::swap(b_, other.b_);
  std::swap(c_, other.c_);
}
