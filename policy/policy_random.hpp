#pragma once

#include "policy.hpp"

namespace bandit{

class RandomPolicy : public Policy{
  const uint K;
public:
  RandomPolicy(uint K): K(K) {
  }
  virtual int selectNextArm(){
    return std::uniform_int_distribution<int>(0, K-1)(randomEngine); 
  }
  virtual void updateState(int, double){
  }
  virtual std::string toString(){
    std::string str="Random";
    return str;
  }
};

} //namespace
