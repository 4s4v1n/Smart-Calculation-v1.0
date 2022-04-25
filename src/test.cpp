#include <gtest/gtest.h>

#include <vector>

#include "controller/calculator_controller.h"
#include "controller/credit_controller.h"

TEST(Test, isNum1) {
  s21::CalculatorController control;
  EXPECT_TRUE(control.IsNumber("23.14"));
}

TEST(Test, isNum2) {
  s21::CalculatorController control;
  EXPECT_FALSE(control.IsNumber("(23.14"));
}

TEST(Test, valid1) {
  s21::CalculatorController control;
  EXPECT_TRUE(control.Validator("23.14+7.3"));
}

TEST(Test, valid2) {
  s21::CalculatorController control;
  EXPECT_FALSE(control.Validator("x23.14+7.3"));
}

TEST(Test, calc1) {
  s21::CalculatorController control;
  std::string str =
      control.PolishNotation("tan(0)+2.3*(-3.1)/12+sin(1)-lg(100.2)+ln(2.72)");
  EXPECT_TRUE("-0.752932" == control.ResultOfNotation(str, 0.));
}

TEST(Test, calc2) {
  s21::CalculatorController control;
  std::string str = "cos(3.14)+3.2%0.2/7^2.3+asin(0)*acos(1)-atan(-1)";
  str = control.PolishNotation(str);
  str = control.ResultOfNotation(str, 0.);
  EXPECT_TRUE("-0.214601" == str);
}

TEST(Test, calc3) {
  s21::CalculatorController control;
  std::string str = "cos(3.14)+x%0.2/7^x+asin(0)*acos(1)-atan(-1)";
  control.StringContainsX(str);
  str = control.PolishNotation(str);
  str = control.ResultOfNotation(str, 1.);
  EXPECT_TRUE("-0.186029" == str);
}

TEST(Test, invalid1) {
  s21::CalculatorController control;
  EXPECT_FALSE(control.Validator("++"));
}

TEST(Test, invalid2) {
  s21::CalculatorController control;
  EXPECT_FALSE(control.Validator(")+"));
}

TEST(Test, invalid3) {
  s21::CalculatorController control;
  EXPECT_FALSE(control.Validator("2^-"));
}

TEST(Test, invalid4) {
  s21::CalculatorController control;
  EXPECT_FALSE(control.Validator("(2^)-"));
}

TEST(Test, vector) {
  s21::CalculatorController control;
  long double start = 0.;
  long double end = 50.;
  std::pair<std::vector<long double>, std::vector<long double>> p =
      control.VectorPair("x", start, end);
  EXPECT_TRUE(p.first[0] == 0.);
  EXPECT_TRUE(p.second[0] == 0.);
}

TEST(Test, credit1) {
  s21::CreditController control;
  control.Validator("annuity", "years", 5., 12.5, 1000000.);
  control.SetData("annuity", "years", 5., 12.5, 1000000.);
  control.Calculate();
  ASSERT_EQ((int)control.MountPay(), 22497);
  ASSERT_EQ((int)control.OverPay(), 349876);
  ASSERT_EQ((int)control.FullPay(), 1349876);
}

TEST(Test, credit2) {
  s21::CreditController control;
  control.Validator("different", "months", 12., 12.5, 1000000.);
  control.SetData("different", "months", 12., 12.5, 1000000.);
  control.Calculate();
  ASSERT_EQ((int)control.MountPay(), 93750);
  ASSERT_EQ((int)control.LastPay(), 84201);
  ASSERT_EQ((int)control.OverPay(), 67708);
  ASSERT_EQ((int)control.FullPay(), 1067708);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}