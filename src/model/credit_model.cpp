// Copyright telvina 2022
#include "credit_model.h"

#include <cmath>

namespace s21 {

bool CreditModel::_IsValidInfo(const std::string& creditType,
                               const std::string& timeType,
                               const long double& time,
                               const long double& percent,
                               const long double& creditSum) {
  bool result = true;
  if (creditType != "annuity" && creditType != "different") {
    result = false;
  }
  if (result && timeType != "months" && timeType != "years") {
    result = false;
  }
  if (result && time <= 0.L) {
    result = false;
  }
  if (result && percent <= 0.L) {
    result = false;
  }
  if (result && creditSum <= 0.L) {
    result = false;
  }
  return result;
}

void CreditModel::_SetInfo(const std::string& creditType,
                           const std::string& timeType, const long double& time,
                           const long double& percent,
                           const long double& creditSum) {
  _creditType = creditType;
  _timeType = timeType;
  _time = time;
  _percent = percent;
  _creditSum = creditSum;
}

void CreditModel::_Calculate() {
  _percent /= 100.L * 12.L;
  if (_timeType == "years") {
    _time *= 12.L;
  }
  if (_creditType == "annuity") {
    _output._monthPay =
        _creditSum *
        (_percent + (_percent / (powl(1.L + _percent, _time) - 1.L)));
    _output._fullPay = _output._monthPay * _time;
    _output._overPay = _output._fullPay - _creditSum;
  } else {
    long double coefficient = _creditSum / _time;
    long double startSum = _creditSum;
    for (size_t i = 0; i < static_cast<size_t>(_time); ++i) {
      _output._lastPay = coefficient + _creditSum * _percent;
      _output._fullPay += _output._lastPay;
      _creditSum -= coefficient;
      if (!i) {
        _output._monthPay = _output._lastPay;
      }
    }
    _output._overPay = _output._fullPay - startSum;
  }
}

}  // namespace s21
