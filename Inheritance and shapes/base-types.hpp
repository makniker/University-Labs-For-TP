#ifndef BASETYPES_HPP
#define BASETYPES_HPP

#include <iosfwd>

namespace yermakov
{
  struct point_t
  {
  public:
    double x_;
    double y_;
    point_t() = default;
    point_t(const point_t&) = default;
    point_t(point_t&&) = default;
    point_t& operator=(const point_t&) = default;
    point_t& operator=(point_t&&) = default;
    point_t(double, double);
  };

  std::ostream& operator<<(std::ostream& out, const point_t& point);
  void move(point_t&, double, double);
  void move(point_t&, const point_t&);
  void scale(point_t&, const point_t&, double);
  double getDistance(const point_t&, const point_t&);
  double getXDistance(const point_t&, const point_t&);
  double getYDistance(const point_t&, const point_t&);

  struct rectangle_t
  {
  public:
    double width_;
    double height_;
    point_t pos_;
    rectangle_t(double, double, const point_t&);
  };

  std::ostream& operator<<(std::ostream& output, const rectangle_t& rect);
  double getArea(const rectangle_t&);
  point_t getCenterPoint(const point_t&, const point_t&);
}

#endif
