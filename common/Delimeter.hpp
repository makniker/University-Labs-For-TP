#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iosfwd>
#include <utility>

namespace yermakov
{
  struct Delimeter
  {
    char ch_;
  };

  std::istream& operator>>(std::istream&, Delimeter&&);
  bool IsStreamGood(std::istream&);
}

#endif
