#include "Commands.hpp"

#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include <Messages.hpp>

namespace
{
  double calculateArea(const yermakov::Polygon& p)
  {
    std::vector< yermakov::Point > toCalc = p.points_;
    yermakov::Point toPush = p.points_[0];
    toCalc.push_back(toPush);
    double xSumm = 0;
    double ySumm = 0;
    for (size_t i = 0; i < toCalc.size() - 1; i++)
    {
      xSumm += (toCalc[i].x_ * toCalc[i + 1].y_);
      ySumm += (toCalc[i].y_ * toCalc[i + 1].x_);
    }
    return std::abs(xSumm - ySumm) / 2;
  }

  bool isEven(const yermakov::Polygon& p)
  {
    return p.points_.size() % 2 == 0;
  }

  bool isOdd(const yermakov::Polygon& p)
  {
    return !isEven(p);
  }

  struct isRightNum
  {
    isRightNum(std::size_t number):
      numOfVertex_(number)
    {
    }

    bool operator()(const yermakov::Polygon& p) const
    {
      return p.points_.size() == numOfVertex_;
    }

    std::size_t numOfVertex_;
  };

  struct ComparatorOfVertex
  {
    bool operator()(const yermakov::Polygon& p1, const yermakov::Polygon& p2) const
    {
      return p1.points_.size() < p2.points_.size();
    }
  };

  struct ComparatorOfArea
  {
    bool operator()(const yermakov::Polygon& p1, const yermakov::Polygon& p2) const
    {
      return calculateArea(p1) < calculateArea(p2);
    }
  };

  struct isSeq
  {
    isSeq(const yermakov::Polygon& toFind): toFind_(toFind)
    {}

    bool operator()(const yermakov::Polygon& p1, const yermakov::Polygon& p2) const
    {
      return toFind_ == p1 && toFind_ == p2;
    }

    yermakov::Polygon toFind_;
  };

   struct isMaxSeq
  {
    isMaxSeq(const yermakov::Polygon& toFind): toFind_(toFind)
    {}

    std::size_t operator()(long unsigned int seq, const yermakov::Polygon& p)
    {
      if (p == toFind_)
      {
        return ++seq;
      }
      else if (seq > maxSeq)
      {
        maxSeq = seq;
      }
      return maxSeq;
    }

    long unsigned int maxSeq = 0;
    const yermakov::Polygon toFind_;
  };

  double countArea(double result, const yermakov::Polygon& p)
  {
    return result + calculateArea(p);
  }
}

void yermakov::doAREA(std::ostream& out, std::vector< Polygon >& data, const std::string& arg)
{
  std::vector< Polygon > tmp;
  try
  {
    std::size_t vertexes = std::stoi(arg);
    if (vertexes < 3)
    {
      printInvalid(out) << "\n";
      return;
    }
    isRightNum isRightNumber(vertexes);
    std::copy_if(data.begin(), data.end(), std::back_inserter(tmp), isRightNumber);
    tmp.shrink_to_fit();
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(tmp.begin(), tmp.end(), 0., countArea) << "\n";
  }
  catch (...)
  {
    if (arg == "MEAN")
    {
      if (data.size() > 0)
      {
        out << std::fixed << std::setprecision(1);
        out << (std::accumulate(data.begin(), data.end(), 0., countArea) / data.size()) << "\n";
        return;
      }
      printInvalid(out) << "\n";
      return;
    }
    else if (data.empty())
    {
      out << std::fixed << std::setprecision(1);
      out << 0. << "\n";
      return;
    }
    else if (arg == "EVEN")
    {
      std::copy_if(data.begin(), data.end(), std::back_inserter(tmp), isEven);
    }
    else if (arg == "ODD")
    {
      std::copy_if(data.begin(), data.end(), std::back_inserter(tmp), isOdd);
    }
    else
    {
      printInvalid(out) << "\n";
      return;
    }
    out << std::fixed << std::setprecision(1) << std::accumulate(tmp.begin(), tmp.end(), 0., countArea) << "\n";
  }
}

void yermakov::doMAX(std::ostream& out, std::vector< Polygon >& data, const std::string& arg)
{
  if (data.empty())
  {
    printInvalid(out) << "\n";
    return;
  }
  if (arg == "AREA")
  {
    out << std::fixed << std::setprecision(1);
    out << calculateArea(*std::max_element(data.begin(), data.end(), ComparatorOfArea{})) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    out << (*std::max_element(data.begin(), data.end(), ComparatorOfVertex{})).points_.size() << "\n";
  }
  else
  {
    printInvalid(out) << "\n";
  }
}

void yermakov::doMIN(std::ostream& out, std::vector< Polygon >& data, const std::string& arg)
{
  if (data.empty())
  {
    printInvalid(out) << "\n";
    return;
  }
  if (arg == "AREA")
  {
    out << calculateArea(*std::min_element(data.begin(), data.end(), ComparatorOfArea{})) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    out << (*std::min_element(data.begin(), data.end(), ComparatorOfVertex{})).points_.size() << "\n";
  }
  else
  {
    printInvalid(out) << "\n";
  }
}

void yermakov::doCOUNT(std::ostream& out, std::vector< Polygon >& data, const std::string& arg)
{
  try
  {
    std::size_t vertexes = std::stoi(arg);
    if (vertexes < 3)
    {
      printInvalid(out) << "\n";
      return;
    }
    isRightNum isRightNumber(vertexes);
    out << std::count_if(data.begin(), data.end(), isRightNumber) << "\n";
  }
  catch (...)
  {
    if (data.empty())
    {
      out << 0 << "\n";
      return;
    }
    else if (arg == "EVEN")
    {
      out << std::count_if(data.begin(), data.end(), isEven) << "\n";
    }
    else if (arg == "ODD")
    {
      out << std::count_if(data.begin(), data.end(), isOdd) << "\n";
    }
    else
    {
      printInvalid(out) << "\n";
    }
  }
}

void yermakov::doRMECHO(std::ostream& out, std::vector< Polygon >& data, const std::string& arg)
{
  try
  {
    std::stringstream input(arg);
    Polygon polygonToDelete;
    input >> polygonToDelete;
    isSeq toDelete(polygonToDelete);
    std::size_t oldSize = data.size();
    auto it = std::unique(data.begin(), data.end(), toDelete);
    data.resize(std::distance(data.begin(), it));
    out << oldSize - data.size() << "\n";
  }
  catch (...)
  {
    printInvalid(out) << "\n";
  }
}

void yermakov::doMAXSEQ(std::ostream& out, std::vector< Polygon >& data, const std::string& arg)
{
  std::stringstream input(arg);
  Polygon polygonToDelete;
  input >> polygonToDelete;
  std::size_t pc = std::stoi(arg.substr(0, arg.find_first_of(" ")));
  if (input.fail() || polygonToDelete.points_.size() != pc)
  {
    printInvalid(out) << "\n";
    return;
  }
  isMaxSeq countFunc(polygonToDelete);
  long unsigned int count = std::accumulate(data.begin(), data.end(), 0, countFunc);
  if (!count)
  {
    printInvalid(out) << "\n";
    return;
  }
  out << count << "\n";
}
