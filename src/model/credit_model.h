#ifndef CREDIT_MODEL_H
#define CREDIT_MODEL_H

#include <string>

namespace s21 {
class CreditModel {
 public:
  struct OutInfo {
    long double _overPay = 0.;
    long double _monthPay = 0.;
    long double _fullPay = 0.;
    long double _lastPay = 0.;
  };
  CreditModel() {}
  ~CreditModel() {}

 protected:
  std::string _creditType;
  std::string _timeType;
  long double _time = 0.;
  long double _percent = 0.;
  long double _creditSum = 0.;
  bool _IsValidInfo(const std::string& creditType, const std::string& timeType,
                    const long double& time, const long double& percent,
                    const long double& creditSum);
  void _SetInfo(const std::string& creditType, const std::string& timeType,
                const long double& time, const long double& percent,
                const long double& creditSum);
  void _Calculate();
  OutInfo _output;
};
}  // namespace s21

#endif  // CREDIT_MODEL_H
