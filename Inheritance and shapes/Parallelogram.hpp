#ifndef PARALLELOGRAM_HPP
#define PARALLELOGRAM_HPP

#include "Shape.hpp"
namespace yermakov
{
  class Parallelogram: public Shape
  {
  public:
    Parallelogram(const point_t&, const point_t&, const point_t&);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t&) override;
    void move(double, double) override;

  private:
    point_t a_;
    point_t b_;
    point_t c_;
    void doScale(double) override;
    void swap(Parallelogram&);
    point_t calculateCenter() const;
  };
}

#endif
