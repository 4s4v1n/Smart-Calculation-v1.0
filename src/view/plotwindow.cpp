// Copyright telvina 2022

#include "plotwindow.h"

#include <QVector>
#include <utility>
#include <vector>

#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget* parent,
                       std::pair<std::vector<long double>,
                                 std::vector<long double>>& coordinatePair,
                       long double& yStart, long double& yEnd)
    : QWidget(parent), ui(new Ui::PlotWindow) {
  ui->setupUi(this);
  ui->plot->setInteraction(QCP::iRangeDrag, true);
  ui->plot->setInteraction(QCP::iRangeZoom, true);
  ui->plot->addGraph();
  ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
  ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
  QColor coral(255, 127, 80);
  ui->plot->graph(0)->setPen(QPen(coral));
  QVector<double> x;
  QVector<double> y;
  _CopyVectors(x, y, coordinatePair.first, coordinatePair.second);
  ui->plot->graph(0)->setData(x, y);
  ui->plot->xAxis->setRange(*coordinatePair.first.begin(),
                            *(coordinatePair.first.end() - 1));
  ui->plot->yAxis->setRange(yStart, yEnd);
  ui->plot->replot();
}

PlotWindow::~PlotWindow() { delete ui; }

void PlotWindow::_CopyVectors(QVector<double>& x, QVector<double>& y,
                              std::vector<long double>& xStd,
                              std::vector<long double>& yStd) {
  for (size_t i = 0; i < xStd.size(); ++i) {
    x.push_back(xStd[i]);
    y.push_back(yStd[i]);
  }
}
