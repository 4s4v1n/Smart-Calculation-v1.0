// Copytight telvina 2022
#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QWidget>

#include "../controller/credit_controller.h"

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QWidget {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent, s21::CreditController *controller);
  ~CreditWindow();

 private slots:
  void on_yearsButton_clicked();

  void on_monthsButton_clicked();

  void on_annuityButton_clicked();

  void on_differentButton_clicked();

  void on_CalculateButton_clicked();

 private:
  Ui::CreditWindow *ui;
  s21::CreditController *_controller = nullptr;
};

#endif  // CREDITWINDOW_H
