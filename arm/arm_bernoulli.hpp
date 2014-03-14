#pragma once

#include "arm.hpp"

namespace bandit{

class BernoulliArm : public Arm{
  const double mu;
  std::uniform_real_distribution<double> unif;
public:
  BernoulliArm(double mu): mu(mu), unif(0.0, 1.0) {
  }
  virtual double pull(){
    double rand = unif(randomEngine);
    if(rand <= mu){
      return 1;
    }else{
      return 0;
    }
  }
  virtual double getExpectedReward(){
    return mu;
  }
  virtual std::string toString(){
    std::string str="Bernoulli Arm with mu="+dtos(mu);
    return str;
  }
};

} //namespace
