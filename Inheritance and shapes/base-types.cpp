#include "base-types.hpp"

#include <ostream>
#include <algorithm>
#include <cmath>

yermakov::point_t::point_t(double x, double y):
  x_(x),
  y_(y)
{}

std::ostream& yermakov::operator<<(std::ostream& output, const point_t& point)
{
  return output << " " << point.x_ << " " << point.y_;
}

yermakov::rectangle_t::rectangle_t(double width, double height, const point_t& center):
  width_(width),
  height_(height),
  pos_(center)
{}

std::ostream& yermakov::operator<<(std::ostream& output, const rectangle_t& rect)
{
  point_t a(rect.pos_.x_ - (rect.width_ / 2), rect.pos_.y_ - (rect.height_ / 2));
  point_t b(rect.pos_.x_ + (rect.width_ / 2), rect.pos_.y_ + (rect.height_ / 2));
  return output << a << b;
}

void yermakov::move(point_t& p, double x, double y)
{
  p.x_ += x;
  p.y_ += y;
}

void yermakov::move(point_t& p, const point_t& destination)
{
  p.x_ = destination.x_;
  p.y_ = destination.y_;
}

void yermakov::scale(point_t& p, const point_t& center, double factor)
{
  p.x_ = center.x_ - (center.x_ - p.x_) * factor;
  p.y_ = center.y_ - (center.y_ - p.y_) * factor;
}

double yermakov::getDistance(const point_t& a, const point_t& b)
{
  return std::sqrt(std::pow(a.x_ - b.x_, 2) + std::pow(a.y_ - b.y_, 2));
}

double yermakov::getXDistance(const point_t& a, const point_t& b)
{
  return std::abs(a.x_ - b.x_);
}

double yermakov::getYDistance(const point_t& a, const point_t& b)
{
  return std::abs(a.y_ - b.y_);
}

yermakov::point_t yermakov::getCenterPoint(const point_t& a, const point_t& c)
{
  return {(a.x_ + c.x_) / 2, (a.y_ + c.y_) / 2};
}

double yermakov::getArea(const rectangle_t& r)
{
  return r.height_ * r.width_;
}
