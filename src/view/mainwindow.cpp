// Copyright telvina 2022

#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton0, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButton3, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButton4, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButton5, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButton6, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButton7, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButton8, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButton9, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonDot, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonX, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonPlus, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonMinus, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonMult, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonDiv, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonPow, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonMod, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonOpen, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonClose, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonSin, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonCos, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonTan, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonAsin, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonAcos, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonAtan, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonLn, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonLg, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonPi, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  connect(ui->pushButtonE, SIGNAL(clicked()), this, SLOT(_InputSymbols()));
  wCredit = new CreditWindow(nullptr, &_creditController);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::_InputSymbols() {
  QPushButton *button = reinterpret_cast<QPushButton *>(sender());
  ui->inputFunction->setText(ui->inputFunction->text() + button->text());
}

void MainWindow::on_pushButtonAC_clicked() { ui->inputFunction->setText(""); }

void MainWindow::on_pushButtonSqrt_clicked() {
  ui->inputFunction->setText(ui->inputFunction->text() + "sqrt");
}

void MainWindow::on_pushButtonBack_clicked() {
  if (ui->inputFunction->text().size() > 0) {
    ui->inputFunction->setText(ui->inputFunction->text().chopped(1));
  }
}

void MainWindow::on_pushButtonEqual_clicked() {
  if (ui->inputFunction->text().contains("π") ||
      ui->inputFunction->text().contains("e")) {
    QString tempString = ui->inputFunction->text();
    tempString.replace("π", "3.14");
    tempString.replace("e", "2.72");
    _inputStr = tempString.toStdString();
  } else {
    _inputStr = ui->inputFunction->text().toStdString();
  }
  if (_controller.Validator(_inputStr)) {
    if (_controller.StringContainsX(_inputStr)) {
      wChoose = new ChooseWindow(nullptr, _inputStr, &_controller);
      wChoose->show();
    } else {
      _inputStr = _controller.PolishNotation(_inputStr);
      _outputStr = _controller.ResultOfNotation(_inputStr, 0.);
    }
  } else {
    _outputStr = "Syntax error";
  }
  ui->labelResult->setText(QString::fromStdString(_outputStr));
}

void MainWindow::on_actionStandart_Mode_triggered() {
  wCredit->hide();
  this->show();
}

void MainWindow::on_actionCredit_Mode_triggered() {
  this->hide();
  wCredit->show();
}
