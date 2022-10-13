#include "DataStruct.hpp"

#include <Delimeter.hpp>

#include "IOHelpers.hpp"

#include <fstream>

std::ostream& yermakov::operator<<(std::ostream& out, const DataStruct& data)
{
  out << "(:" << "key1 " << sll_lit{data.key1_};
  out << "key2 " << rat_lsp{data.key2_};
  out << "key3 " << data_string{data.key3_} << ")";
  return out;
}

std::istream& yermakov::operator>>(std::istream& in, DataStruct& inputData)
{
  if (!IsStreamGood(in))
  {
    return in;
  }
  DataStruct data;
  in >> Delimeter{'('} >> Delimeter{':'};
  std::string key;
  for (std::size_t i = 0; i < 3; ++i)
  {
    in >> key;
    if (key == "key1")
    {
      sll_lit key1{};
      in >> key1;
      data.key1_ = key1.key_;
    }
    else if (key == "key2")
    {
      rat_lsp key2{};
      in >> key2;
      data.key2_ = key2.key_;
    }
    else if (key == "key3")
    {
      data_string key3{};
      in >> key3;
      data.key3_ = key3.key_;
    }
    else
    {
      in.setstate(std::ios::failbit);
      break;
    }
    in >> Delimeter{':'};
  }
  in >> Delimeter{')'};
  if (in)
  {
    inputData = data;
  }
  return in;
}

bool yermakov::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1_ != rhs.key1_)
  {
    return lhs.key1_ < rhs.key1_;
  }
  else if (lhs.key2_.first != rhs.key2_.first || lhs.key2_.second != rhs.key2_.second)
  {
    return 1.f * lhs.key2_.first / lhs.key2_.second < 1.f * rhs.key2_.first / rhs.key2_.second;
  }
  else
  {
    return lhs.key3_.size() < rhs.key3_.size();
  }
}
