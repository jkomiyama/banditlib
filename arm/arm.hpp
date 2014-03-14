#pragma once

#include "../bandit/util.hpp"

namespace bandit{

//arm base class
class Arm{
public:
  //base functions should not be called
  virtual double pull() = 0;
  virtual double getExpectedReward() = 0;
  virtual std::string toString() = 0;
};

} //namespace
