// Copyright telvina 2022

#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QWidget>

#include "../qcustomplot.h"

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QWidget {
  Q_OBJECT

 public:
  explicit PlotWindow(QWidget* parent,
                      std::pair<std::vector<long double>,
                                std::vector<long double>>& coordinatePair,
                      long double& xEnd, long double& yEnd);
  ~PlotWindow();

 private:
  void _CopyVectors(QVector<double>& x, QVector<double>& y,
                    std::vector<long double>& xStd,
                    std::vector<long double>& yStd);
  Ui::PlotWindow* ui;
  double _xStart = 0.;
  double _xEnd = 0.;
  double _yStart = 0.;
  double _yEnd = 0.;
};

#endif  // PLOTWINDOW_H
