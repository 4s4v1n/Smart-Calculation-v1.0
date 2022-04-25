// Copyright telvina 2022

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

#include "choosewindow.h"
#include "creditwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  s21::CalculatorController _controller;
  s21::CreditController _creditController;
  std::string _inputStr;
  std::string _outputStr;
  ChooseWindow *wChoose = nullptr;
  CreditWindow *wCredit = nullptr;

 private slots:
  void _InputSymbols();
  void on_pushButtonAC_clicked();
  void on_pushButtonSqrt_clicked();
  void on_pushButtonBack_clicked();
  void on_pushButtonEqual_clicked();
  void on_actionStandart_Mode_triggered();
  void on_actionCredit_Mode_triggered();
};
#endif  // MAINWINDOW_H
