#include "util.hpp"

namespace bandit{

const double pi = 3.14159265;
const double e  = 2.718281828;

//RNG engine
std::mt19937 randomEngine(std::time(0));

//int -> string
std::string itos(int number)
{
  std::stringstream ss;
  ss << number;
  return ss.str();
}

//double -> string
std::string dtos(double number)
{
  std::stringstream ss;
  ss << number;
  return ss.str();
}

} //namespace
