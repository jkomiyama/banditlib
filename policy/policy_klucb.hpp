#pragma once

#include "policy.hpp"

namespace bandit{

class KLUCBPolicy : public Policy{
  const uint K;
  std::vector<int> Ni;
  std::vector<double> Gi;
  const double DELTA;
  const double EPS;
  double kl(double p, double q){ //calculate kl-divergence
    const double v =  p * log(p/q) + (1-p)*log((1-p)/(1-q));
    return v;
  }
  double dkl(double p, double q){
    return (q-p)/(q*(1.0-q));
  }
public:
  KLUCBPolicy(int K): K(K), DELTA(1e-8), EPS(1e-12) {
    reset();
  }
  void reset(){
    Ni = std::vector<int>(K, 0);
    Gi = std::vector<double>(K, 0.0);
  }
  double getKLUCBUpper(int k, int n){
    const double logndn = log(n)/(double)Ni[k];
    const double p = std::max(Gi[k]/(double)Ni[k], DELTA);
    if(p>=1) return 1;
    bool converged=false;
    double q = p + DELTA;
    for(int t=0;(t<20&&!converged);++t){
      const double f  = logndn - kl(p, q);
      const double df = - dkl(p, q);
      if(f*f < EPS){
        converged=true;
        break;
      }
      q = std::min(1-DELTA , std::max(q - f/df, p+DELTA) );
    }
    if(!converged){
      //std::cout << "WARNING:Newton iteration in KL-UCB algorithm did not converge!! p=" << p << " logndn=" << logndn  << std::endl;
    }
    return q;
  }
  virtual int selectNextArm(){
    const double n = vectorSum(Ni);
    std::vector<double> indices = std::vector<double>(K, 0.0);
    for(uint k=0;k<K;++k){
      if(Ni[k]==0){
        return k;
      }
      //KL-UCB index
      indices[k] = getKLUCBUpper(k, n);
    }

    int targetArm = vectorMaxIndex(indices);
    return targetArm;
  }
  virtual void updateState(int k, double r){
    Ni[k]+=1;
    Gi[k]+=r;
  }
  virtual std::string toString(){
    std::string str="KL-UCB Policy with c=0";
    return str;
  }
};

} //namespace
