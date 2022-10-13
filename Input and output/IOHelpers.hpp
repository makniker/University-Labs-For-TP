#ifndef IOHELPERS_HPP
#define IOHELPERS_HPP

#include <iosfwd>
#include <utility>
#include <string>

namespace yermakov
{
  struct sll_lit
  {
    sll_lit() = default;
    sll_lit(long long);
    long long key_;
  };

  std::ostream& operator<<(std::ostream&, const sll_lit&&);
  std::istream& operator>>(std::istream&, sll_lit&);

  struct rat_lsp
  {
    rat_lsp() = default;
    rat_lsp(const std::pair< long long, unsigned long long >&);
    std::pair< long long, unsigned long long > key_;
  };

  std::ostream& operator<<(std::ostream&, const rat_lsp&&);
  std::istream& operator>>(std::istream&, rat_lsp&);

  struct data_string
  {
    data_string() = default;
    data_string(const std::string&);
    std::string key_;
  };

  std::ostream& operator<<(std::ostream&, const data_string&&);
  std::istream& operator>>(std::istream&, data_string&);
}

#endif
