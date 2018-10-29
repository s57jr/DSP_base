
#include "mainwindow.h"
#include "uimw.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::Plot(QString label,QVector<double> x, QVector<double> y)
{
  ui->addPlot(this, label);
  int plotnum = ui->getPlotInx();

  // The following plot[0] setup is mostly taken from the plot[0] demos:
  ui->plot[plotnum]->addGraph();
  ui->plot[plotnum]->graph()->setPen(QPen(Qt::green));
  ui->plot[plotnum]->graph()->setBrush(QBrush(QColor(0, 255, 0, 50)));
  ui->plot[plotnum]->graph()->setData(x, y);
  ui->plot[plotnum]->axisRect()->setupFullAxesBox(true);
  ui->plot[plotnum]->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

  double min = *std::min_element(y.constBegin(), y.constEnd());
  double max = *std::max_element(y.constBegin(), y.constEnd());

  ui->plot[plotnum]->xAxis->setRange(0 , static_cast<int>(x.length()));

  if(min>max){
    ui->plot[plotnum]->yAxis->setRange(-qAbs(min), qAbs(max));
  }else{
    ui->plot[plotnum]->yAxis->setRange(-qAbs(max), qAbs(max));
  }

}


void MainWindow::Plot(QString label,QVector<float> x, QVector<float> y)
{
    QVector<double> x1(x.size()),y1(y.size());

    for(int i=0;i<x.size();i++){
        x1[i]=static_cast<double>(x[i]);
    }
    for(int i=0;i<y.size();i++){
        y1[i]=static_cast<double>(y[i]);
    }
    Plot(label, x1, y1);
}
