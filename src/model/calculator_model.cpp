// Copyright telvina 2022
#include "calculator_model.h"

#include <utility>

namespace s21 {
CalculatorModel::CalculatorModel()
    : _numberEx("(^\\d+\\.\\d+|^\\d+|^x)"),
      _unaryEx("^(ln|lg|sin|cos|tan|asin|acos|atan|sqrt)\\("),
      _binaryUnaryEx("^(\\+|-)"),
      _binaryEx("^(\\*|/|\\^|%)"),
      _digitEx("^(\\d+\\.\\d+|\\d+|-\\d+|-\\d+\\.\\d+)") {}

CalculatorModel::~CalculatorModel() {}

std::string CalculatorModel::_MakePolishNotation(const std::string& str) {
  _inputLine = str;
  std::string::iterator lineIterator = _inputLine.begin();
  std::cmatch numbers;
  while (lineIterator != _inputLine.end()) {
    if (std::regex_search(lineIterator.base(), numbers, _numberEx)) {
      size_t currentPosition = lineIterator - _inputLine.begin();
      size_t numbersLenght = numbers.str().size();
      _outputLine += _inputLine.substr(currentPosition, numbersLenght);
      _outputLine += " ";
      currentPosition += numbersLenght;
      lineIterator += numbersLenght;
    } else {
      operation_t operation = _WhichOperation(lineIterator);
      if (operation.first != "(" && operation.first != ")") {
        if (operationStack.empty()) {
          operationStack.push(operation);
        } else if (operation.second > operationStack.top().second) {
          operationStack.push(operation);
        } else {
          while (!operationStack.empty() &&
                 operationStack.top().second >= operation.second) {
            _outputLine += operationStack.top().first + " ";
            operationStack.pop();
          }
          operationStack.push(operation);
        }
      } else if (operation.first == "(") {
        operationStack.push(operation);
      } else {
        while (!operationStack.empty() && operationStack.top().first != "(") {
          _outputLine += operationStack.top().first + " ";
          operationStack.pop();
        }
        if (!operationStack.empty() && operationStack.top().first == "(") {
          operationStack.pop();
        }
      }
    }
  }
  while (!operationStack.empty()) {
    _outputLine += operationStack.top().first + " ";
    operationStack.pop();
  }
  return _outputLine;
}

CalculatorModel::operation_t CalculatorModel::_WhichOperation(
    std::string::iterator& iter) {
  operation_t resultOperation = {"", 0};
  std::string str = iter.base();
  if (str.substr(0, 3) == "cos") {
    resultOperation.first = "cos";
    iter += 3;
  } else if (str.substr(0, 3) == "sin") {
    resultOperation.first = "sin";
    iter += 3;
  } else if (str.substr(0, 3) == "tan") {
    resultOperation.first = "tan";
    iter += 3;
  } else if (str.substr(0, 4) == "asin") {
    resultOperation.first = "asin";
    iter += 4;
  } else if (str.substr(0, 4) == "acos") {
    resultOperation.first = "acos";
    iter += 4;
  } else if (str.substr(0, 4) == "atan") {
    resultOperation.first = "atan";
    iter += 4;
  } else if (str.substr(0, 4) == "sqrt") {
    resultOperation.first = "sqrt";
    iter += 4;
  } else if (str.substr(0, 2) == "ln") {
    resultOperation.first = "ln";
    iter += 2;
  } else if (str.substr(0, 2) == "lg") {
    resultOperation.first = "lg";
    iter += 2;
  } else if (*str.data() == '^') {
    resultOperation.first = "^";
    ++iter;
  } else if (*str.data() == '%') {
    resultOperation.first = "%";
    ++iter;
  } else if (*str.data() == '*') {
    resultOperation.first = "*";
    ++iter;
  } else if (*str.data() == '/') {
    resultOperation.first = "/";
    ++iter;
  } else if (*str.data() == '+') {
    --iter;
    if (*iter != '\0') {
      if ((*iter >= 48 && *iter <= 57) || *iter == 'x' || *iter == ')') {
        resultOperation.first = "+";
      } else {
        resultOperation.first = "U+";
      }
    } else {
      resultOperation.first = "U+";
    }
    iter += 2;
  } else if (*str.data() == '-') {
    --iter;
    if (*iter != '\0') {
      if ((*iter >= 48 && *iter <= 57) || *iter == 'x' || *iter == ')') {
        resultOperation.first = "-";
      } else {
        resultOperation.first = "U-";
      }
    } else {
      resultOperation.first = "U-";
    }
    iter += 2;
  } else if (*str.data() == '(') {
    resultOperation.first = "(";
    ++iter;
  } else if (*str.data() == ')') {
    resultOperation.first = ")";
    ++iter;
  }
  _MakePriority(resultOperation);
  return resultOperation;
}

void CalculatorModel::_MakePriority(CalculatorModel::operation_t& operation) {
  if (operation.first == "sin" || operation.first == "cos" ||
      operation.first == "tan" || operation.first == "asin" ||
      operation.first == "acos" || operation.first == "atan" ||
      operation.first == "lg" || operation.first == "ln" ||
      operation.first == "sqrt") {
    operation.second = 5;
  } else if (operation.first == "U+" || operation.first == "U-") {
    operation.second = 4;
  } else if (operation.first == "^") {
    operation.second = 3;
  } else if (operation.first == "%" || operation.first == "*" ||
             operation.first == "/") {
    operation.second = 2;
  } else if (operation.first == "+" || operation.first == "-") {
    operation.second = 1;
  } else if (operation.first == "(" || operation.first == ")") {
    operation.second = 0;
  }
}

std::string CalculatorModel::_Result(const std::string& str,
                                     long double xValue) {
  _outputLine = str;
  std::string::iterator lineIterator = _outputLine.begin();
  char* toldEnd;
  std::cmatch numbersLenght;
  while (lineIterator != _outputLine.end()) {
    if (std::regex_search(lineIterator.base(), numbersLenght, _digitEx)) {
      numberStack.push(strtold(lineIterator.base(), &toldEnd));
      lineIterator += numbersLenght.str().size();
    } else if (*lineIterator == 'x') {
      numberStack.push(xValue);
      ++lineIterator;
    } else {
      _CalculateWithStack(lineIterator);
    }
    if (*lineIterator == ' ') ++lineIterator;
  }
  _result = numberStack.top();
  return std::to_string(_result);
}

void CalculatorModel::_CalculateWithStack(std::string::iterator& iter) {
  long double firstNumber = 0.;
  std::string str = iter.base();
  if (*str.data() == '+' || *str.data() == '-' || *str.data() == '*' ||
      *str.data() == '/' || *str.data() == '%' || *str.data() == '^') {
    firstNumber = numberStack.top();
    numberStack.pop();
    long double secondNumber = numberStack.top();
    numberStack.pop();
    if (*str.data() == '+') {
      numberStack.push(secondNumber + firstNumber);
      iter += 1;
    } else if (*str.data() == '-') {
      numberStack.push(secondNumber - firstNumber);
      iter += 1;
    } else if (*str.data() == '*') {
      numberStack.push(secondNumber * firstNumber);
      iter += 1;
    } else if (*str.data() == '/') {
      numberStack.push(secondNumber / firstNumber);
      iter += 1;
    } else if (*str.data() == '%') {
      numberStack.push(fmodl(secondNumber, firstNumber));
      iter += 1;
    } else if (*str.data() == '^') {
      numberStack.push(powl(secondNumber, firstNumber));
      iter += 1;
    }
  } else {
    firstNumber = numberStack.top();
    numberStack.pop();
    if (str.substr(0, 3) == "cos") {
      numberStack.push(cosl(firstNumber));
      iter += 3;
    } else if (str.substr(0, 3) == "sin") {
      numberStack.push(sinl(firstNumber));
      iter += 3;
    } else if (str.substr(0, 4) == "sqrt") {
      numberStack.push(sqrtl(firstNumber));
      iter += 4;
    } else if (str.substr(0, 3) == "tan") {
      numberStack.push(tanl(firstNumber));
      iter += 3;
    } else if (str.substr(0, 4) == "asin") {
      numberStack.push(asinl(firstNumber));
      iter += 4;
    } else if (str.substr(0, 4) == "acos") {
      numberStack.push(acosl(firstNumber));
      iter += 4;
    } else if (str.substr(0, 4) == "atan") {
      numberStack.push(atanl(firstNumber));
      iter += 4;
    } else if (str.substr(0, 2) == "ln") {
      numberStack.push(logl(firstNumber));
      iter += 2;
    } else if (str.substr(0, 2) == "lg") {
      numberStack.push(log10l(firstNumber));
      iter += 2;
    } else if (str.substr(0, 2) == "U-") {
      numberStack.push(-firstNumber);
      iter += 2;
    } else if (str.substr(0, 2) == "U+") {
      numberStack.push(firstNumber);
      iter += 2;
    }
  }
}

bool CalculatorModel::_BracketBalance(std::string str) {
  std::string::iterator iter = str.begin();
  int bracketCounter = 0;
  while (iter != str.end()) {
    if (*iter == '(') bracketCounter++;
    if (*iter == ')') bracketCounter--;
    ++iter;
  }
  return bracketCounter ? false : true;
}

CalculatorModel::lexems_t CalculatorModel::_WhichIsAction(
    std::string::iterator& iter) {
  std::cmatch findResult;
  lexems_t resultLexem = WRONG;
  if (std::regex_search(iter.base(), findResult, _numberEx)) {
    resultLexem = NUMBER;
    iter += findResult.str().size();
  } else if (std::regex_search(iter.base(), findResult, _binaryUnaryEx)) {
    resultLexem = BINARY_UNARY;
    iter += findResult.str().size();
  } else if (std::regex_search(iter.base(), findResult, _binaryEx)) {
    resultLexem = BINARY;
    iter += findResult.str().size();
  } else if (std::regex_search(iter.base(), findResult, _unaryEx)) {
    resultLexem = UNARY;
    iter += findResult.str().size();
  } else if (*iter == '(') {
    resultLexem = OPEN_BRACKET;
    ++iter;
  } else if (*iter == ')') {
    resultLexem = CLOSE_BRACKET;
    ++iter;
  }
  return resultLexem;
}

bool CalculatorModel::_IsValidString(std::string str) {
  bool valid = true;
  if (str.empty() || !_BracketBalance(str)) {
    valid = false;
  } else {
    std::string::iterator iter = str.begin();
    lexems_t currentLexem = _WhichIsAction(iter);
    if (currentLexem == CLOSE_BRACKET || currentLexem == BINARY) {
      valid = false;
    } else {
      lexems_t previousLexem;
      while (iter != str.end()) {
        previousLexem = currentLexem;
        currentLexem = _WhichIsAction(iter);
        if (currentLexem == OPEN_BRACKET) {
          if (previousLexem == NUMBER || previousLexem == CLOSE_BRACKET) {
            valid = false;
            break;
          }
        } else if (currentLexem == NUMBER) {
          if (previousLexem == NUMBER || previousLexem == CLOSE_BRACKET) {
            valid = false;
            break;
          }
        } else if (currentLexem == BINARY_UNARY) {
          if (previousLexem == BINARY_UNARY) {
            valid = false;
            break;
          }
        } else if (currentLexem == BINARY) {
          if (previousLexem == OPEN_BRACKET || previousLexem == BINARY_UNARY ||
              previousLexem == UNARY || previousLexem == BINARY) {
            valid = false;
            break;
          }
        } else if (currentLexem == UNARY) {
          if (previousLexem == NUMBER || previousLexem == CLOSE_BRACKET) {
            valid = false;
            break;
          }
        } else if (currentLexem == CLOSE_BRACKET) {
          if (previousLexem == OPEN_BRACKET || previousLexem == BINARY_UNARY ||
              previousLexem == UNARY || previousLexem == BINARY) {
            valid = false;
            break;
          }
        } else {
          valid = false;
          break;
        }
      }
      if (currentLexem == OPEN_BRACKET || currentLexem == BINARY ||
          currentLexem == UNARY || currentLexem == BINARY_UNARY) {
        valid = false;
      }
    }
  }
  return valid;
}

void CalculatorModel::_SetFunction(const std::string& str) { _inputLine = str; }

bool CalculatorModel::_ContainsX(const std::string& str) {
  bool result = false;
  _inputLine = str;
  for (auto iter = _inputLine.begin(); iter != _inputLine.end(); ++iter) {
    if (*iter == 'x') {
      result = true;
      break;
    }
  }
  return result;
}

bool CalculatorModel::_IsNumber(const std::string& str) {
  bool result = false;
  if (std::regex_search(str.c_str(), _digitEx)) {
    result = true;
  }
  return result;
}

std::pair<std::vector<long double>, std::vector<long double>>
CalculatorModel::_TwoVectors(const std::string& str, long double& xStart,
                             long double& xEnd) {
  std::pair<std::vector<long double>, std::vector<long double>> result;
  std::string polishString = _MakePolishNotation(str);
  long double step = (xEnd - xStart) / STEPS_NUMBER;
  for (long double i = xStart; i <= xEnd; i += step) {
    result.first.push_back(i);
    result.second.push_back(std::stold(_Result(polishString, i)));
  }
  return result;
}
}  // namespace s21
