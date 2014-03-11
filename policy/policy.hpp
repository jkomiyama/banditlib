#pragma once

#include "../bandit/util.hpp"
#include "../bandit/distributions.hpp"

namespace bandit{

//policy base class
class Policy{
public:
  //base functions should not be called
  virtual int selectNextArm(){
    std::cout << "unexpected base Policy::selectNextArm function call" << std::endl;
    return -1;
	}
  virtual void updateState(int, double){
    std::cout << "unexpected base Policy::updateState function call" << std::endl;
  }
  virtual std::string toString(){
    std::cout << "unexpected base Policy::toString function call" << std::endl;
    return "";
  }
};

} //namespace
