#pragma once

#include "policy.hpp"

namespace bandit{

//DMED policy for binary rewards
class DMEDBinaryPolicy : public Policy{
  const uint K;
  const double EPS;
  uint t;
  std::vector<double> Ni;
  std::vector<double> Gi;
  std::set<int> LC,LRc,LN; //Note: LRc is the complementary set of L_R
public:
  DMEDBinaryPolicy(uint K): K(K), EPS(0.0001) {
    for(uint i=0;i<K;++i){
      Ni.push_back(0);
      Gi.push_back(0);
      LC.insert(i);
    }
    LRc.clear();
    LN.clear(); 
    t = 0;
  }
  double dualDivergence(double mu, double mu_opt){
    double nu = (mu_opt-mu)/((1-mu_opt)*mu_opt);
    return log(1+mu_opt*nu) * (1-mu) + log(1 - (1-mu_opt) * nu ) * mu;
  }
  virtual int selectNextArm(){
    for(uint i=0;i<K;++i){
      if(Ni[i]==0){ //pull all arms at least once
        return i;
      }
    }
    return (*LC.begin());
  }
  virtual void updateState(int k, double r){
    t++;
    Ni[k]+=1;
    Gi[k]+=r;
    if(t<=K){ //initial exploration
      return; 
    }
    std::vector<double> mus(K, 0.0);
    for(uint i=0;i<K;++i){
      mus[i] = std::max(std::min( Gi[i] / Ni[i], 1.0-EPS), EPS);
    }
    LC.erase(k);
    LRc.insert(k);
    double mu_opt = vectorMax(mus);
    for(std::set<int>::iterator it=LRc.begin(); it!=LRc.end(); ++it){
      int j = (*it);
      double dj = dualDivergence(mus[j], mu_opt);
      if(Ni[j]*dj <= log((double)t/Ni[j])){
        LN.insert(j);
      }
    }
    if(LC.empty()){
      LC = LN;
      LRc.clear();
      for(uint i=0;i<K;++i){
        if(LC.find(i) == LC.end()){
          LRc.insert(i);
        }
      }
      LN.clear();
    }
  }
  virtual std::string toString(){
    std::string str="DMED (binary)";
    return str;
  }
};

} //namespace
