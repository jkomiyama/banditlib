#pragma once

#include "util.hpp"
#include "../arm/arm.hpp"
#include "../policy/policy.hpp"

class SimpleLog{
public:
  uint K, P, T;
  std::vector<double> cumulativeRewards;
  std::vector<double> cumulativeRegrets;
  SimpleLog(uint K, uint P, uint T): K(K), P(P), T(T) {
    cumulativeRewards = std::vector<double>(P, 0.0);
    cumulativeRegrets = std::vector<double>(P, 0.0);
  }
  //policy p at round t chose arm k and received reward r, and possible optimal reward was "optimal"
  void record(uint p, uint t, uint k, double r, double optimal){
    cumulativeRewards[p]+=r;
    cumulativeRegrets[p]+=optimal-r;
  }
};

class SimpleLogWriter{
public:
  static void multiLogWrite(std::vector<SimpleLog> &logs,
       std::vector<std::string> armNames, std::vector<std::string> policyNames,
       uint T, std::string filename){
    const uint K = armNames.size();
    const uint P = policyNames.size();
    std::ofstream ofs( filename );
    ofs << "#averaged result over " << logs.size() << " trials" << std::endl;
    for(uint i=0;i<K;++i){
      ofs << "#arm" << i << " " << armNames[i] << std::endl;
    }
    for(uint p=0;p<P;++p){
      ofs << "#policy " << p << " " << policyNames[p] << std::endl;
    }
    ofs.setf(std::ios::fixed, std::ios::floatfield);

    ofs << "reward";
    std::vector<double> cumulativeRewards = std::vector<double>(P, 0.0);
    std::vector<double> cumulativeRegrets = std::vector<double>(P, 0.0);
    for(uint l=0;l<logs.size();++l){
      for(uint p=0;p<P;++p){
        cumulativeRewards[p] += logs[l].cumulativeRewards[p];
        cumulativeRegrets[p] += logs[l].cumulativeRegrets[p];
      }
    }
    for(uint p=0;p<P;++p){
      cumulativeRewards[p] /= logs.size();
      cumulativeRegrets[p] /= logs.size();
    }
    for(uint p=0;p<P;++p){
      ofs << " " << cumulativeRewards[p] ;
    }
    ofs << std::endl;
    ofs << "regret" ;
    std::vector<double> expectedRewards(K, 0.0);
    for(uint p=0;p<P;++p){
      ofs << " " << cumulativeRegrets[p];
    }
    ofs << std::endl;
  }
};
