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

template <class T>
class SigGen : public DSP{
public:
	SigGen(int sr, int freq);
	virtual ~SigGen();

    static constexpr T pi() { return T(3.14159265359); }

    void sine(QVector<T> &wf, int len);
    void cosine(QVector<T> &wf, int len);
    void delta_func(QVector<T> &wf, int len, int delay);

protected:

    int sr;
    T freq;






};

/*
 * SigGen.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: jreberc
 */

#include "SigGen.h"

template <class T>
SigGen<T>::SigGen(int sr, int freq):
sr(sr),
freq(freq){

}

template <class T>
SigGen<T>::~SigGen() {

}

template <class T>
void SigGen<T>::delta_func(QVector<T> &wf, int len,int delay){
    for (int i = 0; i < len; ++i) {
        if(i==delay){
            wf[i]=static_cast<T>(1.0);
        }else{
            wf[i]=static_cast<T>(0);
        }
    }
}

template <class T>
void SigGen<T>::sine(QVector<T> &wf, int len){
    T two = 2.0;
    for (int i = 0; i < len; ++i) {
        wf[i]=std::sin(two*pi()*freq*static_cast<float>(i)/sr);
    }
}

template <class T>
void SigGen<T>::cosine(QVector<T> &wf, int len){
    T two = 2.0;
    for (int i = 0; i < len; ++i) {
        wf[i]=std::cos(two*pi()*freq*static_cast<float>(i)/sr);
    }
}


//template class  SigGen<double>;
//template class  SigGen<float>;


#endif /* SIGGEN_H_ */
