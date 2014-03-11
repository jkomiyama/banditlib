#pragma once

#include "arm.hpp"

namespace bandit{

class NormalArm : public Arm{
  const double mu, sigma;
  std::normal_distribution<double> norm;
public:
  NormalArm(double mu, double sigma): mu(mu), sigma(sigma), norm(mu, sigma) {
  }
  virtual double pull(){
    return norm(randomEngine);
  }
  virtual double getExpectedReward(){
    return mu;
  }
  virtual std::string toString(){
    std::string str="Normal Arm with mu="+dtos(mu)+" sigma="+dtos(sigma);
    return str;
  }
};

} //namespace
