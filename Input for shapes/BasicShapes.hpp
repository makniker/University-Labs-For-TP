#ifndef BASICSHAPES_HPP
#define BASICSHAPES_HPP

#include <vector>
#include <iosfwd>
#include <string>

namespace yermakov
{
  struct Point
  {
    Point() = default;
    bool operator==(const Point& p) const;
    int x_, y_;
  };

  std::istream& operator>>(std::istream& in, Point&);

  struct Polygon
  {
    Polygon() = default;
    bool operator==(const Polygon&) const;
    std::vector< Point > points_;
  };

  std::istream& operator>>(std::istream& in, Polygon&);
}

#endif
