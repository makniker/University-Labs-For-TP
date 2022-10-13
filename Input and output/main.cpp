#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "DataStruct.hpp"

int main()
{
  using in = std::istream_iterator< yermakov::DataStruct >;
  using out = std::ostream_iterator< yermakov::DataStruct >;

  std::vector< yermakov::DataStruct > dataArray;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::copy(in(std::cin), in(), std::back_inserter(dataArray));
  }

  std::sort(dataArray.begin(), dataArray.end());

  std::copy(dataArray.begin(), dataArray.end(), out(std::cout, "\n"));
  return 0;
}
