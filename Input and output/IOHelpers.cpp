#include "IOHelpers.hpp"

#include <Delimeter.hpp>

#include <fstream>
#include <string>

yermakov::sll_lit::sll_lit(long long key):
  key_(key)
{}

std::ostream& yermakov::operator<<(std::ostream& out, const sll_lit&& number)
{
  out << number.key_ << "ll:";
  return out;
}

std::istream& yermakov::operator>>(std::istream& in, sll_lit& number)
{
  if (!IsStreamGood(in))
  {
    return in;
  }
  long long key;
  in >> key;
  char lit = in.peek();
  if (isupper(lit))
  {
    in >> Delimeter{'L'} >> Delimeter{'L'};
  }
  else
  {
    in >> Delimeter{'l'} >> Delimeter{'l'};
  }
  if (in)
  {
    number.key_ = key;
  }
  return in;
}

yermakov::rat_lsp::rat_lsp(const std::pair< long long, unsigned long long >& key):
  key_(key)
{}

std::ostream& yermakov::operator<<(std::ostream& out, const rat_lsp&& number)
{
  out << "(:N " << number.key_.first << ":D " << number.key_.second << ":):";
  return out;
}

std::istream& yermakov::operator>>(std::istream& in, rat_lsp& number)
{
  if (!IsStreamGood(in))
  {
    return in;
  }
  long long nkey;
  unsigned long long dkey;
  in >> Delimeter{'('} >> Delimeter{':'} >> Delimeter{'N'} >> nkey >> Delimeter{':'} >> Delimeter{'D'} >> dkey >>
      Delimeter{':'} >> Delimeter{')'};
  if (in)
  {
    number.key_ = {nkey, dkey};
  }
  return in;
}

yermakov::data_string::data_string(const std::string& key):
  key_(key)
{}

std::ostream& yermakov::operator<<(std::ostream& out, const data_string&& data)
{
  out << "\"" << data.key_ << "\"" << ":";
  return out;
}

std::istream& yermakov::operator>>(std::istream& in, data_string& data)
{
  if (!IsStreamGood(in))
  {
    return in;
  }
  std::string dataString;
  in >> Delimeter{'\"'};
  std::getline(in, dataString, '\"');
  if (in)
  {
    data.key_ = dataString;
  }
  return in;
}
