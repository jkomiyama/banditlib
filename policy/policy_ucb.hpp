#pragma once

#include "policy.hpp"

namespace bandit{

class UCBPolicy : public Policy{
  const uint K;
  const double alpha;
  std::vector<double> Ni;
  std::vector<double> Gi; 
public:
  UCBPolicy(uint K, double alpha=1.0): K(K), alpha(alpha) {
    reset();
  }
  void reset(){
    Ni = std::vector<double>(K, 0.0);
    Gi = std::vector<double>(K, 0.0);
  }
  virtual int selectNextArm(){
    double n = vectorSum(Ni);
    std::vector<double> indices = std::vector<double>(K, 0.0); 
    for(uint k=0;k<K;++k){
      if(Ni[k]==0){
        return k;
      }
      //UCB index
      indices[k] = (Gi[k]/Ni[k]) + sqrt( (alpha * log(n)) / (double)Ni[k] );
    }

    int targetArm = vectorMaxIndex(indices);

    return targetArm;
  }
  virtual void updateState(int k, double r){
    Ni[k]+=1;
    Gi[k]+=r;
  }
  virtual std::string toString(){
    std::string str="UCB Arm with alpha=";
    str+=dtos(alpha);
    return str;
  }
};

} //namespace
