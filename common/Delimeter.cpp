#include "Delimeter.hpp"

#include <fstream>

bool yermakov::IsStreamGood(std::istream& in)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return false;
  }
  return true;
}

std::istream& yermakov::operator>>(std::istream& in, Delimeter&& data)
{
  if (!IsStreamGood(in))
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != data.ch_))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
