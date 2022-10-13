#include "BasicShapes.hpp"

#include <Delimeter.hpp>

#include <fstream>
#include <cmath>

std::istream& yermakov::operator>>(std::istream& in, Polygon& figure)
{
  std::size_t numberOfPoints = 0;
  in >> numberOfPoints;
  std::vector< Point > data;
  std::size_t i = 0;
  Point point{};
  while (i != numberOfPoints && in >> point )
  {
    data.push_back(point);
    ++i;
  }
  if (data.size() != numberOfPoints || data.size() < 3)
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    figure.points_ = std::move(data);
  }
  return in;
}

bool yermakov::Point::operator==(const Point& p) const
{
  return p.x_ == x_ && p.y_ == y_;
}

bool yermakov::Polygon::operator==(const Polygon& p) const
{
  return p.points_ == points_;
}

std::istream& yermakov::operator>>(std::istream& in, Point& point)
{
  if (!IsStreamGood(in))
  {
    return in;
  }
  int x;
  int y;
  in >> Delimeter{'('} >> x >> Delimeter{';'} >> y >> Delimeter{')'};
  if (in)
  {
    point.x_ = x;
    point.y_ = y;
  }
  return in;
}
