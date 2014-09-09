#pragma once

#include <vector>
#include <string>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <ctime>

namespace bandit{

typedef unsigned int uint;

extern const double pi;
extern const double e;

//RNG engine
extern std::mt19937 randomEngine;

template<class T>
int vectorMaxIndex(const std::vector<T> &elems){
  int m=0;
  T mv=elems[0];
  for(uint i=0;i<elems.size();++i){
    if(elems[i]>mv){
      mv=elems[i];
      m=i;
    }
  }
  return m;
}

template<class T>
T vectorMax(std::vector<T> &elems){
  T mv=elems[0];
  for(uint i=0;i<elems.size();++i){
    if(elems[i]>mv){
      mv=elems[i];
    }
  }
  return mv;
}

template<class T>
T vectorSum(const std::vector<T> &elems){
  T s=0;
  for(uint i=0;i<elems.size();++i){
    s+=elems[i];
  }
  return s;
}

std::string itos(int number);
std::string dtos(double number);

} //namespace
