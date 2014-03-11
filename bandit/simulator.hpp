#pragma once

#include "util.hpp"
#include "../arm/arm.hpp"
#include "../policy/policy.hpp"
#include "../bandit/roundwiselog.hpp"

namespace bandit{

typedef std::shared_ptr<Arm> ArmPtr;
typedef std::shared_ptr<Policy> PolicyPtr;

template<class Log = RoundwiseLog>
class Simulator{
  std::vector<ArmPtr>    arms;
  std::vector<PolicyPtr> policies;
  uint optimalArm;
public:
  Simulator(const std::vector<ArmPtr> &arms, const std::vector<PolicyPtr> &policies):
    arms(arms), policies(policies) {
    std::vector<double> expectedRewards(arms.size(), 0.0);
    for(uint i=0;i<arms.size();++i){
      expectedRewards[i] = arms[i]->getExpectedReward();
    }
    optimalArm = vectorMaxIndex(expectedRewards);
  }
  void debugPrint(){
    for(uint i=0;i<arms.size();++i){
      std::cout << arms[i]->toString() << std::endl;
    }  
    for(uint p=0;p<policies.size();++p){
      std::cout << policies[p]->toString() << std::endl;
    }  
  }
  void run(Log &log, const uint T){
    log.startRun();
    for(uint t=1;t<=T;++t){
      for(uint p=0;p<policies.size();++p){
        execSingleRound(log, p, t);
      }
    }
  }
  void execSingleRound(Log &log, uint p, uint t){
    uint arm = policies[p]->selectNextArm();
    double reward = arms[arm]->pull();
    policies[p]->updateState(arm, reward); 
    double optimalExpectedReward = arms[optimalArm]->getExpectedReward();
    double armExpectedReward     = arms[arm]->getExpectedReward();
    double regret = optimalExpectedReward - armExpectedReward;
    log.record(p, t, arm, reward, regret);
  }
};


} //namespace
