#pragma once

#include "policy.hpp"

namespace bandit{

//UCB-V 
class UCBVPolicy : public Policy{
  const uint K;
  const double amp, zeta;
  std::vector<int> Ni;
  std::vector<double> Gi;
  std::vector<double> Gi2;
  double getVariance(int k){
    double v = Gi2[k]/Ni[k] - (Gi[k]*Gi[k]/(Ni[k]*Ni[k]));
    if(v<0){
      std::cout << "WARNING:variance smaller than 0!!!" << std::endl;
    }
    return v;
  }
public:
  UCBVPolicy(uint K, double amp=1, double zeta=1): K(K), amp(amp), zeta(zeta) {
    reset();
  }
  void reset(){
    Ni = std::vector<int>(K, 0);
    Gi = std::vector<double>(K, 0.0);
    Gi2 = std::vector<double>(K, 0.0);
  }
  virtual int selectNextArm(){
    double n = vectorSum(Ni);
    std::vector<double> indices = std::vector<double>(K, 0.0);
    for(uint k=0;k<K;++k){
      if(Ni[k]==0){
        return k;
      }
      double variance = getVariance(k);
      //UCB-V index
      indices[k] = (Gi[k]/Ni[k]) + sqrt( (2 * zeta * variance * log(n)) / (double)Ni[k] ) + 3 * amp * zeta * log(n)/(double)Ni[k];
    }

    int targetArm = vectorMaxIndex(indices);

    return targetArm;
  }
  virtual void updateState(int k, double r){
    Ni[k]+=1;
    Gi[k]+=r;
    Gi2[k]+=r*r;
  }
  virtual std::string toString(){
    std::string str="UCB-V Arm with amp=";
    str+=dtos(amp);
    str+=" zeta=";
    str+=dtos(zeta);
    return str;
  }
};

} //namespace
