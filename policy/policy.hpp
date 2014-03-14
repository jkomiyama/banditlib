#pragma once

#include "../bandit/util.hpp"
#include "../bandit/distributions.hpp"

namespace bandit{

//policy base class
class Policy{
public:
  //base functions should not be called
  virtual int selectNextArm() = 0;
  virtual void updateState(int, double) = 0;
  virtual std::string toString() = 0;
};

} //namespace
