/*
 * SigGen.h
 *
 *  Created on: Oct 9, 2018
 *      Author: jreberc
 */

#ifndef SIGGEN_H_
#define SIGGEN_H_

#include <iostream>
#include <string>
#include <math.h>
#include "DSP.h"
#include <QVector>

class SigGen : public DSP{
public:
	SigGen(int sr, int freq);
	virtual ~SigGen();

//	void sine(float *wf, int len);
//	void cosine(float *wf, int len);
//	void delta_func(float *wf,int len,int delay);
    void sine(QVector<float> &wf, int len);
    void cosine(QVector<float> &wf, int len);
    void delta_func(QVector<float> &wf, int len, int delay);

protected:

    int sr;
    float freq;






};

#endif /* SIGGEN_H_ */
