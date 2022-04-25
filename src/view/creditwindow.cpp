// Copyright telvina 2022

#include "creditwindow.h"

#include <string>

#include "ui_creditwindow.h"

CreditWindow::CreditWindow(QWidget* parent, s21::CreditController* controller)
    : QWidget(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);
  _controller = controller;
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_yearsButton_clicked() {
  ui->termTypeLabel->setText("years");
}

void CreditWindow::on_monthsButton_clicked() {
  ui->termTypeLabel->setText("months");
}

void CreditWindow::on_annuityButton_clicked() {
  ui->paymentTypeLabel->setText("annuity");
}

void CreditWindow::on_differentButton_clicked() {
  ui->paymentTypeLabel->setText("different");
}

void CreditWindow::on_CalculateButton_clicked() {
  std::string timeType = ui->termTypeLabel->text().toStdString();
  std::string payType = ui->paymentTypeLabel->text().toStdString();
  long double creditSum = ui->creditSumLine->text().toDouble();
  long double percent = ui->percentLine->text().toDouble();
  long double time = ui->creditTermLine->text().toDouble();
  if (_controller->Validator(payType, timeType, time, percent, creditSum)) {
    _controller->SetData(payType, timeType, time, percent, creditSum);
    _controller->Calculate();
    ui->MounthlyPaymentLabelResult->setText(
        QString::number(_controller->MountPay(), 'f', 2));
    if (payType == "different") {
      ui->MounthlyPaymentLabelResult->setText(
          ui->MounthlyPaymentLabelResult->text() + "...");
      ui->MounthlyPaymentLabelResult->setText(
          ui->MounthlyPaymentLabelResult->text() +
          QString::number(_controller->LastPay(), 'f', 2));
    }
    ui->overPaymentLabelResult->setText(
        QString::number(_controller->OverPay(), 'f', 2));
    ui->FullPaymentLabelResult->setText(
        QString::number(_controller->FullPay(), 'f', 2));
  } else {
    ui->MounthlyPaymentLabelResult->setText("Synatax error");
    ui->overPaymentLabelResult->setText("Synatax error");
    ui->FullPaymentLabelResult->setText("Synatax error");
  }
}
