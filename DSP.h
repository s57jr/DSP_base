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


class DSP {
public:
	DSP();
	virtual ~DSP();

    float PI = 3.1415926535897932384626433f;

	void print_wf(float *wf, int len);
	void display_wf(float *wf, int len, int abs_scale);
};

#endif /* DSP_H_ */
