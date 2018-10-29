/*
 * SigGen.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: jreberc
 */

#include "SigGen.h"

SigGen::SigGen(int sr, int freq):
sr(sr),
freq(freq){

}

SigGen::~SigGen() {

}

void SigGen::delta_func(QVector<float> &wf, int len,int delay){
    for (int i = 0; i < len; ++i) {
        if(i==delay){
            wf[i]=1.0;
        }else{
            wf[i]=0;
        }
    }
}

void SigGen::sine(QVector<float> &wf, int len){
    for (int i = 0; i < len; ++i) {
        wf[i]=sinf(2.0f*PI*freq*static_cast<float>(i)/sr);
    }
}

void SigGen::cosine(QVector<float> &wf, int len){
    for (int i = 0; i < len; ++i) {
        wf[i]=cosf(2.0f*PI*freq*static_cast<float>(i)/sr);
    }
}


//void SigGen::delta_func(float *wf,int len,int delay){
//	for (int i = 0; i < len; ++i) {
//		if(i==delay){
//			*(wf+i)=1.0;
//		}else{
//			*(wf+i)=0;
//		}
//	}
//}

//void SigGen::sine(float wf[], int len){
//	for (int i = 0; i < len; ++i) {
//		wf[i]=sin(2.0*M_PI*freq*(float)i/sr);
//	}
//}

//void SigGen::cosine(float wf[], int len){
//	for (int i = 0; i < len; ++i) {
//		wf[i]=cos(2.0*M_PI*freq*(float)i/sr);
//	}
//}


