/*
 * DSP.h
 *
 *  Created on: Oct 11, 2018
 *      Author: jreberc
 */

#ifndef DSP_H_
#define DSP_H_

#include <iostream>
#include <math.h>
#include <QVector>
#include <QString>
#include "mainwindow.h"


class DSP {
public:
	DSP();
	virtual ~DSP();

    void print_wf(QVector<float> wf, int len);
    void display_wf(QVector<float> wf, int wflen, QString label, MainWindow *MainWindow);
    void display_wf(QVector<float> wfx, QVector<float> wfy, int wflen, QString label, MainWindow *MainWindow);

    void print_wf(QVector<double> wf, int len);
    void display_wf(QVector<double> wf, int wflen, QString label, MainWindow *MainWindow);
    void display_wf(QVector<double> wfx, QVector<double> wfy, int wflen, QString label, MainWindow *MainWindow);

};

#endif /* DSP_H_ */
