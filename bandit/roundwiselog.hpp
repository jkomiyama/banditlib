#pragma once

#include "util.hpp"
#include "../arm/arm.hpp"
#include "../policy/policy.hpp"

namespace bandit{

class RoundwiseLog{
public:
  uint K, P, T, run;
  std::vector<std::vector<double> > roundwiseRewards;
  std::vector<std::vector<double> > roundwiseRegrets;
  RoundwiseLog(uint K, uint P, uint T): K(K), P(P), T(T) {
    roundwiseRewards = std::vector<std::vector<double> >(P, std::vector<double>(T, 0.0));
    roundwiseRegrets = std::vector<std::vector<double> >(P, std::vector<double>(T, 0.0));
    run=0;
  }
  //start new run
  void startRun(){
    run+=1;
  }
  //policy p at round t chose arm k and received reward r
  void record(uint p, uint t, uint k, double r, double regretDelta){
    roundwiseRewards[p][t]+=r;
    roundwiseRegrets[p][t]+=regretDelta;
  }
};

class RoundwiseLogWriter{
public:
  static void logWrite(RoundwiseLog &log,
       std::vector<std::string> armNames, std::vector<std::string> policyNames,
       uint T, std::string filename, bool rewardPlot=true, bool regretPlot=true){
    const uint K = armNames.size();
    const uint P = policyNames.size();
    std::ofstream ofs( filename );
    ofs << "#averaged result over " << log.run << " trials" << std::endl;
    for(uint i=0;i<K;++i){
      ofs << "#arm" << i << " " << armNames[i] << std::endl;
    }
    for(uint p=0;p<P;++p){
      ofs << "#policy " << p << " " << policyNames[p] << std::endl;
    }
    ofs.setf(std::ios::fixed, std::ios::floatfield);

    ofs << "#results:" << std::endl;
    ofs << "#T" ;
    for(uint p=0;p<P;++p){
      if(rewardPlot){
        ofs << " reward" << p;
      }
      if(regretPlot){
        ofs << " regret" << p ;
      }
    }
    ofs << std::endl;
    std::vector<double> cumulatedRewards(P, 0.0);
    std::vector<double> cumulatedRegrets(P, 0.0);
    for(uint t=0;t<T;++t){
      ofs << (t+1);
      for(uint p=0;p<P;++p){
        cumulatedRewards[p]+=log.roundwiseRewards[p][t];
        cumulatedRegrets[p]+=log.roundwiseRegrets[p][t];
        if(rewardPlot){
          ofs << std::setprecision(2) << " " << cumulatedRewards[p]/log.run;
        }
        if(regretPlot){
          ofs << std::setprecision(2) << " " << cumulatedRegrets[p]/log.run ;
        }
      }
      ofs << std::endl;
    }
  }
};

} //namespace
