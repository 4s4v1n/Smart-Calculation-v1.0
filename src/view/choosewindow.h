// Copyright telvina 2022
#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QWidget>

#include "../controller/calculator_controller.h"
#include "plotwindow.h"

namespace Ui {
class ChooseWindow;
}

class ChooseWindow : public QWidget {
  Q_OBJECT

 public:
  explicit ChooseWindow(QWidget *parent, const std::string &str,
                        s21::CalculatorController *controller);
  ~ChooseWindow();

 private slots:
  void on_buttonX_clicked();
  void on_buttonPlot_clicked();
  void on_buttonCalculate_clicked();

 private:
  Ui::ChooseWindow *ui;
  std::string _polishString;
  PlotWindow *wPlot = nullptr;
  s21::CalculatorController *_controller = nullptr;
  bool _xChoose = false;
  bool _PlotChoose = false;
  long double _xStart = 0.;
  long double _xEnd = 0.;
  long double _yStart = 0.;
  long double _yEnd = 0.;
};

#endif  // CHOOSEWINDOW_H
