#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

namespace yermakov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(const point_t&, const point_t&);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(double, double) override;

  private:
    point_t a_;
    point_t c_;
    void doScale(double) override;
    void swap(Rectangle&);
    point_t calculateCenter() const;
  };
}

#endif
