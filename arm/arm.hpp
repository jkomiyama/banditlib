#pragma once

#include "../bandit/util.hpp"

namespace bandit{

//arm base class
class Arm{
public:
  //base functions should not be called
  virtual double pull(){
    std::cout << "unexpected base Arm::pull function call" << std::endl;
    abort();
    return 0;
	}
  virtual double getExpectedReward(){
    std::cout << "unexpected base Arm::getExpectedReward function call" << std::endl;
    abort();
    return 0;
  }
  virtual std::string toString(){
    std::cout << "unexpected base Arm::toString function call" << std::endl;
    abort();
    return "";
  }
};

} //namespace
