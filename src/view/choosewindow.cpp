// Copyright telvina 2022

#include "choosewindow.h"

#include <string>
#include <utility>
#include <vector>

#include "../controller/calculator_controller.h"
#include "ui_choosewindow.h"

ChooseWindow::ChooseWindow(QWidget* parent, const std::string& str,
                           s21::CalculatorController* controller)
    : QWidget(parent), ui(new Ui::ChooseWindow) {
  ui->setupUi(this);
  ui->inputFunction->setText(QString::fromStdString(str));
  _polishString = str;
  _controller = controller;
}

ChooseWindow::~ChooseWindow() { delete ui; }

void ChooseWindow::on_buttonX_clicked() {
  _xChoose = true;
  _PlotChoose = false;
}

void ChooseWindow::on_buttonPlot_clicked() {
  _PlotChoose = true;
  _xChoose = false;
}

void ChooseWindow::on_buttonCalculate_clicked() {
  _polishString =
      _controller->PolishNotation(ui->inputFunction->text().toStdString());
  if (_xChoose) {
    if (_controller->IsNumber(ui->inputXValue->text().toStdString())) {
      ui->outputResult->setText(
          QString::fromStdString(_controller->ResultOfNotation(
              _polishString, ui->inputXValue->text().toDouble())));
    } else {
      ui->outputResult->setText("Syntax error");
    }
  } else if (_PlotChoose) {
    if (_controller->IsNumber(ui->xStartArea->text().toStdString()) &&
        _controller->IsNumber(ui->xEndArea->text().toStdString()) &&
        _controller->IsNumber(ui->yStartArea->text().toStdString()) &&
        _controller->IsNumber(ui->yEndArea->text().toStdString())) {
      _xStart = ui->xStartArea->text().toDouble();
      _xEnd = ui->xEndArea->text().toDouble();
      _yStart = ui->yStartArea->text().toDouble();
      _yEnd = ui->yEndArea->text().toDouble();
      if (_xStart >= -1e6 && _xEnd <= 1e6 && _yStart >= -1e6 && _yEnd <= 1e6 &&
          _xStart < _xEnd && _yStart < _yEnd) {
        std::pair<std::vector<long double>, std::vector<long double>>
            vectorPair = _controller->VectorPair(
                ui->inputFunction->text().toStdString(), _xStart, _xEnd);
        wPlot = new PlotWindow(nullptr, vectorPair, _yStart, _yEnd);
        wPlot->show();
      } else {
        ui->outputResult->setText("Syntax error");
      }
    } else {
      ui->outputResult->setText("Syntax error");
    }
  }
}
