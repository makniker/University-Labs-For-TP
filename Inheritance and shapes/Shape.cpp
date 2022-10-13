#include "Shape.hpp"

#include <stdexcept>

void yermakov::Shape::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::logic_error("Wrong scale factor!");
  }
  doScale(factor);
}
