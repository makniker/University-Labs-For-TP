#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iosfwd>

namespace yermakov
{
  struct DataStruct
  {
    long long key1_;
    std::pair< long long, unsigned long long > key2_;
    std::string key3_;
  };

  std::ostream& operator<<(std::ostream&, const DataStruct&);
  std::istream& operator>>(std::istream&, DataStruct&);
  bool operator<(const DataStruct&, const DataStruct&);
}

#endif
