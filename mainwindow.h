

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "../qcustomplot/qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void Plot(QString label, QVector<double> x, QVector<double> y);
  void Plot(QString label, QVector<float> x, QVector<float> y);

  QTextStream& qStdOut()
  {
      static QTextStream ts( stdout );
      return ts;
  }


private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
