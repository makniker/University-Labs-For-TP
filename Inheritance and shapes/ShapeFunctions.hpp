#ifndef SHAPEARRAY_HPP
#define SHAPEARRAY_HPP

#include <memory>
#include <cmath>
#include <string>

#include "Shape.hpp"

namespace yermakov
{
  using shapePtr = std::unique_ptr< yermakov::Shape >;
  using arr = std::unique_ptr< shapePtr[] >;
  using descArr = std::unique_ptr< yermakov::point_t[] >;
  std::ostream& printArray(std::ostream&, arr&&, std::size_t);
  arr&& scaleArray(arr&&, std::size_t, const point_t&, double);
  void makeArray(descArr&&, std::string);

  template < typename T, typename Strategy >
  void pushBack(std::unique_ptr< T[] >&&, std::size_t&, std::size_t&, T&&);

  std::unique_ptr< yermakov::Shape > isoScale(shapePtr&&, const point_t&, double);
  std::unique_ptr< yermakov::Shape > createParallelogram(descArr);
  std::unique_ptr< yermakov::Shape > createRegular(descArr);
  std::unique_ptr< yermakov::Shape > createRectangle(descArr);

  struct GoldenRatio
  {
    static size_t increase(size_t capacity)
    {
      const double goldenRatio = 1.6;
      return std::ceil(capacity * goldenRatio) + 1;
    }
  };

  template < typename T, typename Strategy = yermakov::GoldenRatio >
  void pushBack(std::unique_ptr< T[] >&& Arr, std::size_t& used, std::size_t& size, T&& moveObj)
  {
    if (used >= size)
    {
      double newCapacity = Strategy::increase(used);
      auto newArray = std::make_unique< T[] >(newCapacity);
      for (size_t i = 0; i < used; i++)
      {
        newArray[i] = std::move(Arr[i]);
      }
      Arr = std::move(newArray);
      size = newCapacity;
    }
    Arr[used] = std::move(moveObj);
    used++;
  }
}

#endif
