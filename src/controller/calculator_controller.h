#ifndef CALCULATOR_CONTROLLER_H
#define CALCULATOR_CONTROLLER_H

#include "../model/calculator_model.h"

namespace s21 {
class CalculatorController : CalculatorModel {
 public:
  bool Validator(std::string str);
  std::string PolishNotation(const std::string& str);
  std::string ResultOfNotation(const std::string& str, long double x);
  bool StringContainsX(std::string& str);
  bool IsNumber(const std::string& str);
  std::pair<std::vector<long double>, std::vector<long double>> VectorPair(
      std::string str, long double& xStart, long double& xEnd);
};
}  // namespace s21

#endif  // CALCULATOR_CONTROLLER_H
