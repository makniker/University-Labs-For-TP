#ifndef CHECKFUNCTIONS_HPP
#define CHECKFUNCTIONS_HPP

#include "base-types.hpp"

namespace yermakov
{
  bool isOnePointBelowOther(const point_t&, const point_t&);
  bool isTriangle(const point_t&, const point_t&, const point_t&);
  bool isParallel(const point_t&, const point_t&, const point_t&);
  bool isOnOneLine(const point_t&, const point_t&, const point_t&);
  bool isRightTriangle(const point_t&, const point_t&, const point_t&);
  double countNumberOfSides(const point_t&, const point_t&, const point_t&);
  bool isOneOfRightTriangle(const point_t&, const point_t&, const point_t&);
  bool isCorrectNumberOfSides(const point_t&, const point_t&, const point_t&);
  double calculateRadiusOfCircumCircle(const point_t&, const point_t&, const point_t&);
  double calculateradiusOfInscribedCircle(const point_t&, const point_t&, const point_t&);
}
#endif
