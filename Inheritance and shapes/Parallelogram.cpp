#include "Parallelogram.hpp"

#include <cmath>
#include <stdexcept>

#include "CheckFunctions.hpp"

yermakov::Parallelogram::Parallelogram(const point_t& a, const point_t& b, const point_t& c):
  a_(a),
  b_(b),
  c_(c)
{
  if (!isTriangle(a, b, c) || !isParallel(a, b, c) || isOnOneLine(a, b, c))
  {
    throw std::logic_error("Wrong args!");
  }
}

yermakov::point_t yermakov::Parallelogram::calculateCenter() const
{
  return getCenterPoint(a_, c_);
}

double yermakov::Parallelogram::getArea() const
{
  double height = getYDistance(a_, c_);
  double width = b_.y_ == c_.y_ ? getXDistance(b_, c_) : getXDistance(b_, a_);
  return height * width;
}

yermakov::rectangle_t yermakov::Parallelogram::getFrameRect() const
{
  rectangle_t frameRect(getXDistance(c_, a_), getYDistance(a_, c_), calculateCenter());
  return frameRect;
}

void yermakov::Parallelogram::move(double x, double y)
{
  point_t a = a_;
  point_t b = b_;
  point_t c = c_;
  yermakov::move(a, x, y);
  yermakov::move(b, x, y);
  yermakov::move(c, x, y);
  Parallelogram tmp(a, b, c);
  swap(tmp);
}

void yermakov::Parallelogram::move(const point_t& newCenter)
{
  move(newCenter.x_ - calculateCenter().x_, newCenter.y_ - calculateCenter().y_);
}

void yermakov::Parallelogram::doScale(double factor)
{
  point_t a = a_;
  point_t b = b_;
  point_t c = c_;
  yermakov::scale(a, calculateCenter(), factor);
  yermakov::scale(b, calculateCenter(), factor);
  yermakov::scale(c, calculateCenter(), factor);
  Parallelogram tmp(a, b, c);
  swap(tmp);
}

void yermakov::Parallelogram::swap(Parallelogram& other)
{
  std::swap(a_, other.a_);
  std::swap(c_, other.c_);
  std::swap(b_, other.b_);
}
