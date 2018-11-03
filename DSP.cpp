/*
 * DSP.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: jreberc
 */

#include "DSP.h"

DSP::DSP() {
	// TODO Auto-generated constructor stub

}

DSP::~DSP() {
	// TODO Auto-generated destructor stub
}


void DSP::print_wf(QVector<float> wf, int wflen){
    for (int i = 0; i < wflen; ++i) {
		std::cout << wf[i] << ", ";
	}
	std::cout << std::endl;
}


void DSP::display_wf(QVector<float> wf, int wflen, QString label, MainWindow *MainWindow){

    QVector<double> x(wflen), y(wflen);

    for(int i=0;i<wflen;i++){
        x[i]=i;
        y[i]=static_cast<double>(wf[i]);
    }

    MainWindow->Plot(label, x, y);
}

void DSP::display_wf(QVector<float> wfx, QVector<float> wfy, int wflen, QString label, MainWindow *MainWindow){

    QVector<double> x(wflen), y(wflen);

    for(int i=0;i<wflen;i++){
        x[i]=static_cast<double>(wfx[i]);
        y[i]=static_cast<double>(wfy[i]);
    }

    MainWindow->Plot(label, x, y);
}

void DSP::print_wf(QVector<double> wf, int wflen){
    for (int i = 0; i < wflen; ++i) {
        std::cout << wf[i] << ", ";
    }
    std::cout << std::endl;
}


void DSP::display_wf(QVector<double> wf, int wflen, QString label, MainWindow *MainWindow){

    QVector<double> x(wflen), y(wflen);

    for(int i=0;i<wflen;i++){
        x[i]=i;
        y[i]=static_cast<double>(wf[i]);
    }

    MainWindow->Plot(label, x, y);
}

void DSP::display_wf(QVector<double> wfx, QVector<double> wfy, int wflen, QString label, MainWindow *MainWindow){

    QVector<double> x(wflen), y(wflen);

    for(int i=0;i<wflen;i++){
        x[i]=static_cast<double>(wfx[i]);
        y[i]=static_cast<double>(wfy[i]);
    }

    MainWindow->Plot(label, x, y);
}




//void DSP::display_wf(float *wf, int len, int abs_scale){

//	float max_abs=0;

//	abs_scale = (abs_scale%2) ? abs_scale : abs_scale+1;

//	char graph[len][abs_scale];

//	for (int i = 0; i < len; ++i) {
//		for (int j = 0; j < abs_scale; ++j) {
//			graph[i][j] = '-';
//		}
//	}

//	for(int i=0; i< len; i++){
//		if(abs(wf[i])>max_abs)max_abs=wf[i];
//	}
//	for(int i=0;i<len;i++){
//		int j = (((abs_scale/2)-1)*(wf[i]/max_abs));
//		for(int k=0;k<abs(j);k++){
//			if(j<0){
//				graph[i][-j+(int)(abs_scale/2)-k] = '#';
//			}else if(j>0){
//				graph[i][-j+(int)(abs_scale/2)+k] = '#';
//			}
//		}
//		if(j==0)graph[i][(int)(abs_scale/2)]='#';
//	}

//	for (int i = 0; i < abs_scale; ++i) {
//		for (int j = 0; j < len; ++j) {
//			std::cout << graph[j][i];
//		}
//		std::cout << '\n';
//	}

//}
