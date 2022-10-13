#include <iostream>
#include <string>
#include <iomanip>

#include "ShapeFunctions.hpp"
#include "InputProcessingFunctions.hpp"

int main()
{
  using shapePtr = std::unique_ptr< yermakov::Shape >;
  std::string description;
  std::getline(std::cin, description);
  if (yermakov::getType(description) == "SCALE")
  {
    std::cerr << "scale without shapes!\n";
    return 2;
  }
  std::size_t size = 0;
  std::size_t capacity = 1;
  std::size_t capacityOArr = 3;
  std::unique_ptr< shapePtr[] > ShObjs = std::make_unique< shapePtr[] >(capacity);
  yermakov::point_t centerOfScale{0, 0};
  bool isScale = false;
  double factor = 0;
  while (!std::cin.eof())
  {
    try
    {
      if (description.empty())
      {
        std::getline(std::cin, description);
        continue;
      }
      if (!yermakov::isRightShape(description) && yermakov::getType(description) != "SCALE")
      {
        throw std::logic_error("Wrong shapes!");
      }
      else
      {
        if (yermakov::getType(description) == "SCALE")
        {
          centerOfScale = yermakov::getScalePoint(description);
          factor = yermakov::getScaleFactor(description);
          std::getline(std::cin, description);
          isScale = true;
          continue;
        }
        else
        {
          std::unique_ptr< yermakov::point_t[] > points = std::make_unique< yermakov::point_t[] >(capacityOArr);
          yermakov::makeArray(std::move(points), description);
          if (yermakov::getType(description) == "REGULAR")
          {
            shapePtr shObj = std::move(yermakov::createRegular(std::move(points)));
            yermakov::pushBack< shapePtr, yermakov::GoldenRatio >(std::move(ShObjs), size, capacity, std::move(shObj));
          }
          else if (yermakov::getType(description) == "RECTANGLE")
          {
            shapePtr shObj = std::move(yermakov::createRectangle(std::move(points)));
            yermakov::pushBack< shapePtr, yermakov::GoldenRatio >(std::move(ShObjs), size, capacity, std::move(shObj));
          }
          else if (yermakov::getType(description) == "PARALLELOGRAM")
          {
            shapePtr shObj = std::move(yermakov::createParallelogram(std::move(points)));
            yermakov::pushBack< shapePtr, yermakov::GoldenRatio >(std::move(ShObjs), size, capacity, std::move(shObj));
          }
          else
          {
            throw std::logic_error("Wrong shape!");
          }
        }
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
    }
    std::getline(std::cin, description);
  }
  if (!isScale)
  {
    std::cerr << "scale without shapes!\n";
    return 2;
  }

  try
  {
    std::cout << std::fixed << std::setprecision(1);
    yermakov::printArray(std::cout, std::move(ShObjs), size);
    ShObjs = yermakov::scaleArray(std::move(ShObjs), size, centerOfScale, factor);
    yermakov::printArray(std::cout, std::move(ShObjs), size);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 2;
  }
  return 0;
}
