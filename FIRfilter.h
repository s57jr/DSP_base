/*
 * FIRfilter.h
 *
 *  Created on: Oct 10, 2018
 *      Author: jreberc
 */

#ifndef FIRFILTER_H_
#define FIRFILTER_H_


#include <iostream>
#include <string>
#include <math.h>
#include <map>
#include "mainwindow.h"

#include "DSP.h"
#include "FFT.h"

using namespace std;


class FIRfilter : public DSP {
public:
    FIRfilter(int length, string type, float samplerate, float fcutoff_low, float fcutoff_high);
	virtual ~FIRfilter();

	void window_coefficients(string type);
    void convolution(QVector<float> &sig, int sig_length, QVector<float> &filtered);
    void set_len(int length);
    int get_len();
    void display_resp(int abs_scale);

    void calculate_coefficients(string type, float samplerate, float fcutoff_low, float fcutoff_high );
    void display_coef(MainWindow *MainWindow);
    void display_resp(MainWindow *MainWindow);

    void print_coef();

protected:
    int len;
//  float *save_chunk;
//  float *coefficients;
    QVector<float> coefficients;
    QVector<float> save_chunk;

    //float *lol;
    QVector<float> lol;

    FFT *response;

    enum StringValue { triangular,
					  hanning,
					  hamming,
					  blackman,
					  lowpass,
					  highpass,
					  bandpass,
					  bandstop,
    				  error};

    StringValue parse_strings(string input);


};

#endif /* FIRFILTER_H_ */
