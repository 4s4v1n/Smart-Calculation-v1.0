// Copyright 2022 telvina
#include "calculator_controller.h"

#include <string>
#include <utility>
#include <vector>

namespace s21 {
bool CalculatorController::Validator(std::string str) {
  return this->_IsValidString(str);
}

std::string CalculatorController::PolishNotation(const std::string& str) {
  return this->_MakePolishNotation(str);
}

std::string CalculatorController::ResultOfNotation(const std::string& str,
                                                   long double x) {
  return this->_Result(str, x);
}

bool CalculatorController::StringContainsX(std::string& str) {
  return this->_ContainsX(str);
}

bool CalculatorController::IsNumber(const std::string& str) {
  return this->_IsNumber(str);
}

std::pair<std::vector<long double>, std::vector<long double>>
CalculatorController::VectorPair(std::string str, long double& xStart,
                                 long double& xEnd) {
  return this->_TwoVectors(str, xStart, xEnd);
}

}  // namespace s21
