#pragma once

#include "policy.hpp"

namespace bandit{

//Thompson sampling (binary reward and beta prior)
class ThompsonBinaryPolicy : public Policy{
  const uint K;
  std::vector<double> alphas, betas;
public:
  ThompsonBinaryPolicy(uint K, double alpha=1, double beta=1): K(K){
    for(uint i=0;i<K;++i){
      alphas.push_back(alpha);
      betas.push_back(beta);
    }
  }
  virtual int selectNextArm(){
    std::vector<double> thetas(K, 0.0);
    for(uint i=0;i<K;++i){
      thetas[i] = beta_distribution<double>(alphas[i], betas[i])(randomEngine) ;
    }
    return vectorMaxIndex(thetas);
  }
  virtual void updateState(int k, double r){
    if(r>0.5){
      alphas[k]+=1;
    }else{
      betas[k] +=1;
    }
  }
  virtual std::string toString(){
    std::string str="Thompson sampling";
    return str;
  }
};

} //namespace
