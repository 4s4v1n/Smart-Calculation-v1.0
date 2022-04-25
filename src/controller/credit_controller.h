#ifndef CREDIT_CONTROLLER_H
#define CREDIT_CONTROLLER_H

#include "../model/credit_model.h"

namespace s21 {
class CreditController : CreditModel {
 public:
  long double MountPay();
  long double LastPay();
  long double OverPay();
  long double FullPay();

  bool Validator(const std::string& creditType, const std::string& timeType,
                 const long double& time, const long double& percent,
                 const long double& creditSum);

  void SetData(const std::string& creditType, const std::string& timeType,
               const long double& time, const long double& percent,
               const long double& creditSum);

  void Calculate();

  CreditController() {}
  ~CreditController() {}
};
}  // namespace s21

#endif  // CREDIT_CONTROLLER_H
