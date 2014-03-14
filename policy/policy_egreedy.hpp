#pragma once

#include "policy.hpp"

namespace bandit{

class EGreedyPolicy : public Policy{
  const uint K;
  std::vector<int> Ni;
  std::vector<double> Gi; 
  const double epsilonCoef; //epsilon (random play prob) - epsilon_base/(current)t
                      //epsilonbase = cK/d2
public:
  EGreedyPolicy(int K, double epsilonCoef=0.1): K(K), epsilonCoef(epsilonCoef) {
    reset();
  }
  void reset(){
    Ni = std::vector<int>(K, 0);
    Gi = std::vector<double>(K, 0.0);
  }
  virtual int selectNextArm(){
    double n = vectorSum(Ni);
    double en = epsilonCoef/n;
    double rand = std::uniform_real_distribution<double>(0.0,1.0)(randomEngine);
    if(en > rand){ //random choice
      return std::uniform_int_distribution<int>(0, K-1)(randomEngine);
    }else{
      std::vector<double> eExpectations = std::vector<double>(K, 0.0);
      for(uint k=0;k<K;++k){
        if(Ni[k]==0){
          return k;
        }
        eExpectations[k] = Gi[k]/Ni[k] ;
      }
      int targetArm = vectorMaxIndex(eExpectations);
      return targetArm;
    }
  }
  virtual void updateState(int k, double r){
    Ni[k]+=1;
    Gi[k]+=r;
  }
  virtual std::string toString(){
    std::string str="Egreedy Policy with epsilonCoef=";
    str+=dtos(epsilonCoef);
    return str;
  }
};

} //namespace
