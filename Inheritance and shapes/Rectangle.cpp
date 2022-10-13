#include "Rectangle.hpp"

#include <cmath>
#include <stdexcept>

#include "CheckFunctions.hpp"

yermakov::Rectangle::Rectangle(const point_t& a, const point_t& c):
  a_(a),
  c_(c)
{
  if (!isOnePointBelowOther(a, c))
  {
    throw std::logic_error("Wrong args!");
  }
}

yermakov::point_t yermakov::Rectangle::calculateCenter() const
{
  point_t center(getCenterPoint(a_, c_));
  return center;
}

double yermakov::Rectangle::getArea() const
{
  return getXDistance(c_, a_) * getYDistance(a_, c_);
}

yermakov::rectangle_t yermakov::Rectangle::getFrameRect() const
{
  rectangle_t frameRect(getXDistance(c_, a_), getYDistance(a_, c_), calculateCenter());
  return frameRect;
}

void yermakov::Rectangle::move(double x, double y)
{
  point_t a = a_;
  point_t c = c_;
  yermakov::move(a, x, y);
  yermakov::move(c, x, y);
  Rectangle tmp(a, c);
  swap(tmp);
}

void yermakov::Rectangle::move(const point_t& newCenter)
{
  move(newCenter.x_ - calculateCenter().x_, newCenter.y_ - calculateCenter().y_);
}

void yermakov::Rectangle::doScale(double factor)
{
  point_t a = a_;
  point_t c = c_;
  yermakov::scale(a, calculateCenter(), factor);
  yermakov::scale(c, calculateCenter(), factor);
  Rectangle tmp(a, c);
  swap(tmp);
}

void yermakov::Rectangle::swap(Rectangle& other)
{
  std::swap(a_, other.a_);
  std::swap(c_, other.c_);
}
