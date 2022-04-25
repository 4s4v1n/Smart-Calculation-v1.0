#ifndef CALCULATOR_MODEL_H
#define CALCULATOR_MODEL_H

#define STEPS_NUMBER 5000

#include <cmath>
#include <regex>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
class CalculatorModel {
 private:
  std::string _inputLine;
  std::string _outputLine;
  long double _result = 0.;

  typedef std::pair<std::string, size_t> operation_t;

  std::stack<operation_t> operationStack;
  std::stack<long double> numberStack;

  enum lexems_t {
    WRONG = 0,
    NUMBER = 1,
    OPEN_BRACKET = 2,
    CLOSE_BRACKET = 3,
    BINARY = 4,
    BINARY_UNARY = 5,
    UNARY = 6
  };

  std::regex _numberEx;
  std::regex _unaryEx;
  std::regex _binaryUnaryEx;
  std::regex _binaryEx;
  std::regex _digitEx;

  operation_t _WhichOperation(std::string::iterator& iter);
  void _MakePriority(CalculatorModel::operation_t& operation);
  void _CalculateWithStack(std::string::iterator& iter);
  lexems_t _WhichIsAction(std::string::iterator& iter);
  bool _BracketBalance(std::string str);

 protected:
  std::string _MakePolishNotation(const std::string& str);
  void _SetFunction(const std::string& str);
  bool _IsValidString(std::string str);
  bool _ContainsX(const std::string& str);
  std::string _Result(const std::string& str, long double xValue);
  bool _IsNumber(const std::string& str);
  std::pair<std::vector<long double>, std::vector<long double>> _TwoVectors(
      const std::string& str, long double& xStart, long double& xEnd);

 public:
  CalculatorModel();
  ~CalculatorModel();
};

}  // namespace s21

#endif  // CALCULATOR_MODE_H
