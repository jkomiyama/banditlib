#pragma once

#include "policy.hpp"

namespace bandit{

class MOSSPolicy : public Policy{
  const uint K;
  std::vector<int> Ni;
  std::vector<double> Gi;
public:
  MOSSPolicy(uint K): K(K) {
    reset();
  }
  void reset(){
    Ni = std::vector<int>(K, 0);
    Gi = std::vector<double>(K, 0.0);
  }
  virtual int selectNextArm(){
    double n = vectorSum(Ni);
    std::vector<double> indices = std::vector<double>(K, 0.0);
    for(uint k=0;k<K;++k){
      if(Ni[k]==0){
        return k;
      }
      indices[k] = (Gi[k]/Ni[k]) + sqrt( std::max<double>( log(n/(K*Ni[k])) , 0.0) / (double)Ni[k] );
    }

    int targetArm = vectorMaxIndex(indices);
    return targetArm;
  }
  virtual void updateState(int k, double r){
    Ni[k]+=1;
    Gi[k]+=r;
  }
  virtual std::string toString(){
    std::string str="MOSS";
    return str;
  }
};

} //namespace
