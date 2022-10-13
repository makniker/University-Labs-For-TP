#ifndef REGULAR_HPP
#define REGULAR_HPP

#include "Shape.hpp"

namespace yermakov
{
  class Regular: public Shape
  {
  public:
    Regular(const point_t&, const point_t&, const point_t&);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(double, double) override;
  private:
    point_t a_;
    point_t b_;
    point_t c_;
    void doScale(double) override;
    void swap(Regular&);
  };
}

#endif
