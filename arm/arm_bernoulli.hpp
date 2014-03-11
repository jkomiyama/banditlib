#pragma once

#include "arm.hpp"

namespace bandit{

class BernoulliArm : public Arm{
  const double theta;
  std::uniform_real_distribution<double> unif;
public:
  BernoulliArm(double theta): theta(theta), unif(0.0, 1.0) {
  }
  virtual double pull(){
    double rand = unif(randomEngine);
    if(rand <= theta){
      return 1;
    }else{
      return 0;
    }
  }
  virtual double getExpectedReward(){
    return theta;
  }
  virtual std::string toString(){
    std::string str="Bernoulli Arm with theta="+dtos(theta);
    return str;
  }
};

} //namespace
