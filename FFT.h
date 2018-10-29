/*
 * fft.h
 *
 *  Created on: Oct 9, 2018
 *      Author: jreberc
 */

#ifndef FFT_H_
#define FFT_H_

#include <math.h>
#include <iostream>
#include "DSP.h"
#include <QVector>

class FFT : public DSP{
public:
	FFT(int len);
	virtual ~FFT();
	void set_len(int len);
	int get_len();

//    void fft(float *srt);
//    void ifft(float *srt);

//	void fft(float *srt, float *sit);
//	void ifft(float *srt, float *sit);

    void fft(QVector<float> &srt);
    void ifft(QVector<float> &srt);

    void fft(QVector<float> &srt, QVector<float> &sit);
    void ifft(QVector<float> &srt, QVector<float> &sit);

//	void display_fft(float *srt, int abs_scale);
//	void display_ifft(float *srt, int abs_scale);

//	void display_fft(float *srt, float *sit, int abs_scale);
//	void display_ifft(float *srt, float *sit, int abs_scale);

//	void print_fft(float *srt);
//	void print_ifft(float *srt);

//	void print_fft(float *srt, float *sit);
//	void print_ifft(float *srt, float *sit);

//	void get_PSD(float *srt, float *PSD);
//	void get_PSD(float *srt, float * sit, float *PSD);

    void get_PSD(QVector<float> &srt, QVector<float> &PSD);
    void get_PSD(QVector<float> &srt, QVector<float> &sit, QVector<float> &PSD);
	int zero_pad;


protected:

	int fft_length;
//	int *br;
    QVector<int> br;
	void bitrev();

};

#endif /* FFT_H_ */
