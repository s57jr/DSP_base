#ifndef UIMW_H
#define UIMW_H


#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "../qcustomplot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class UIMW
{

private:

    static const int plots = 5; //num of plots -1

    int window_W = 469;
    int window_H = 357;
    int plot_num=0;

public:
    QAction *actionInsert_Plot;
    QAction *actionSave_Document;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QCustomPlot *plot[plots];
    QLabel     *graphlabel[plots];
    QStatusBar *statusBar;



    void setupUi(QMainWindow *MainWindow);
    void addPlot(QMainWindow *MainWindow, QString label);
    int getPlotInx();  //get plot index
    void retranslateUi(QMainWindow *MainWindow);


};

namespace Ui {
    class MainWindow: public UIMW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UIMW_H
