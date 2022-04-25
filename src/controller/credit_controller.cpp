// Copyright telvina 2022
#include "credit_controller.h"

#include <string>
#include <utility>
#include <vector>

namespace s21 {
long double CreditController::FullPay() { return this->_output._fullPay; }
long double CreditController::OverPay() { return this->_output._overPay; }
long double CreditController::MountPay() { return this->_output._monthPay; }
long double CreditController::LastPay() { return this->_output._lastPay; }

bool CreditController::Validator(const std::string& creditType,
                                 const std::string& timeType,
                                 const long double& time,
                                 const long double& percent,
                                 const long double& creditSum) {
  return this->_IsValidInfo(creditType, timeType, time, percent, creditSum);
}

void CreditController::SetData(const std::string& creditType,
                               const std::string& timeType,
                               const long double& time,
                               const long double& percent,
                               const long double& creditSum) {
  return this->_SetInfo(creditType, timeType, time, percent, creditSum);
}

void CreditController::Calculate() { this->_Calculate(); }
}  // namespace s21
