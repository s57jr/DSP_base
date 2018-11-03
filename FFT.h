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
#include "mainwindow.h"


template <class T>
class FFT : public DSP {
public:
	FFT(int len);
	virtual ~FFT();

    static constexpr T pi() { return T(3.14159265359); }

    void set_fft_len(int len);
    int get_fft_len();

    void fft(QVector<T> &srt);
    void ifft(QVector<T> &srt);
    void fft_PSD(QVector<T> &srt);
    void ifft_PSD(QVector<T> &srt);

    void fft(QVector<T> &srt, QVector<T> &sit);
    void ifft(QVector<T> &srt, QVector<T> &sit);

    void display_fft(QVector<T> &srt, MainWindow *MainWindow);
    void display_ifft(QVector<T> &srt, MainWindow *MainWindow);

    void display_fft(QVector<T> &srt, QVector<T> &sit, MainWindow *MainWindow);
    void display_ifft(QVector<T> &srt, QVector<T> &sit, MainWindow *MainWindow);

    void print_fft(QVector<T> &srt);
    void print_ifft(QVector<T> &srt);
    void print_fft(QVector<T> &srt, QVector<T> &sit);
    void print_ifft(QVector<T> &srt, QVector<T> &sit);


    //result is stored into srt
    void get_PSD(QVector<T> &srt, QVector<T> &sit, QVector<T> &PSD);

protected:

    int zero_pad;

	int fft_length;

    QVector<T> zerovect;  //prepared zero vector to speed up things

    QVector<int> br;
	void bitrev();

};


/*
 * Fft.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: jreberc
 */

#include "FFT.h"

template <class T>
FFT<T>::FFT(int len) {
    std::cout << "Initializing FFT... " << std::endl;

    set_fft_len(len);

    zerovect.resize(fft_length);
    zerovect.fill(0);

}

template <class T>
FFT<T>::~FFT() {
    std::cout << "Closing FFT... " << std::endl;
}

template <class T>
void FFT<T>::print_fft(QVector<T> &srt){

    QVector<T> sig(fft_length);

    for (int i = 0; i < fft_length; ++i) {
        sig[i] = srt[i];
    }

    fft(sig);

    DSP::print_wf(sig,fft_length);
}

template <class T>
void FFT<T>::print_ifft(QVector<T> &srt){

    QVector<T> sig(fft_length);

    for (int i = 0; i < fft_length; ++i) {
        sig[i] = srt[i];
    }

    ifft(sig);
    DSP::print_wf(sig,fft_length);
}

template <class T>
void FFT<T>::print_fft(QVector<T> &srt, QVector<T> &sit){

    QVector<T> PSD(fft_length);
    QVector<T> sig(fft_length);
    QVector<T> sigi(fft_length);

    for (int i = 0; i < fft_length; ++i) {
        sig[i]  = srt[i];
        sigi[i] = sit[i];
    }

    fft(sig,sigi);

    get_PSD(sig,sigi,PSD);

    DSP::print_wf(PSD,fft_length);
}

template <class T>
void FFT<T>::print_ifft(QVector<T> &srt, QVector<T> &sit){

    QVector<T> PSD(fft_length);
    QVector<T> sig(fft_length);
    QVector<T> sigi(fft_length);


    for (int i = 0; i < fft_length; ++i) {
        sig[i]  = srt[i];
        sigi[i] = sit[i];
    }
    ifft(sig,sigi);
    get_PSD(sig,sigi,PSD);
    DSP::print_wf(PSD,fft_length);
}

template <class T>
void FFT<T>::display_fft(QVector<T> &srt, MainWindow *MainWindow){

    QVector<T> sig(fft_length);

    for (int i = 0; i < fft_length; ++i) {
        sig[i] = srt[i];
    }

    fft(sig);

    DSP::display_wf(sig,fft_length, "FFT display",MainWindow);
}

template <class T>
void FFT<T>::display_ifft(QVector<T> &srt, MainWindow *MainWindow){

    QVector<T> sig(fft_length);

    for (int i = 0; i < fft_length; ++i) {
        sig[i] = srt[i];
    }

    ifft(sig);

    DSP::display_wf(sig,fft_length, "IFFT display", MainWindow);
}

template <class T>
void FFT<T>::display_fft(QVector<T> &srt, QVector<T> &sit, MainWindow *MainWindow){

    QVector<T> PSD(fft_length);
    QVector<T> sig(fft_length);
    QVector<T> sigi(fft_length);

    for (int i = 0; i < fft_length; ++i) {
        sig[i]  = srt[i];
        sigi[i] = sit[i];
    }
    fft(sig,sigi);
    get_PSD(sig,sigi,PSD);

    DSP::display_wf(PSD,fft_length, "FFT display", MainWindow);
}

template <class T>
void FFT<T>::display_ifft(QVector<T> &srt, QVector<T> &sit, MainWindow *MainWindow){

    QVector<T> PSD(fft_length);
    QVector<T> sig(fft_length);
    QVector<T> sigi(fft_length);

    for (int i = 0; i < fft_length; ++i) {
        sig[i]  = srt[i];
        sigi[i] = sit[i];
    }
    ifft(sig,sigi);
    get_PSD(sig,sigi,PSD);

    DSP::display_wf(PSD,fft_length, "IFFT display",MainWindow);
}


//result is stored into srt
template <class T>
void FFT<T>::get_PSD(QVector<T> &srt, QVector<T> &sit, QVector<T> &PSD){
    for (int i = 0; i < fft_length; ++i) {
        PSD[i]=static_cast<T>(sqrt(std::pow(srt[i],2)+std::pow(sit[i],2)));
    }
}

template <class T>
void FFT<T>::set_fft_len(int len){

    int newlen=len;
    float power = static_cast<float>(log2(len));

    if(power - static_cast<int>(power) != 0.0f){
        zero_pad = static_cast<int>(pow(2.0,static_cast<int>(power)+1.0))-len;
        newlen=static_cast<int>(pow(2,static_cast<int>(power)+1));
        std::cout << "Length not a power of 2!" << std::endl;
    }else{
        zero_pad = 0;
    }
    std::cout << "Setting FFT length to: " << newlen << std::endl;

    fft_length = newlen;

    br.resize(fft_length);
    bitrev();
}

template <class T>
int FFT<T>::get_fft_len(){
    return fft_length;
}

template <class T>
void FFT<T>::bitrev(){
    int a,d,c,e,g1,j;

    for(a=0;a<fft_length;a++){
        br[a]=a;
    }
    j=static_cast<int>(log2(fft_length));

    for(a=1;a<j;a++){
        c=static_cast<int>(pow(2,a));
        g1=0;
        for(d=0;d<c;d++){
        if(!(d%2)){
              for(e=0;e<fft_length/c;e++){
                    br[e+(d*fft_length/c)]=br[e+(d*fft_length/c)]+g1;
                g1+=(c/2);

            }
        }
        if(d%2){
            g1-=(c/2);
              for(e=0;e<fft_length/c;e++){
                      br[e+(d*fft_length/c)]=br[e+(d*fft_length/c)]-g1;
                  g1-=(c/2);
            }g1+=(c/2);
        }
        }
    }
}

template <class T>
void FFT<T>::fft(QVector<T> &srt){

    fft(srt,zerovect);

}

template <class T>
void FFT<T>::ifft(QVector<T> &srt){

    ifft(srt,zerovect);

}

template <class T>
void FFT<T>::fft_PSD(QVector<T> &srt){

    QVector<T> PSD(fft_length);

    fft(srt,zerovect);
    get_PSD(srt,zerovect,PSD);

    srt = PSD;
}

template <class T>
void FFT<T>::ifft_PSD(QVector<T> &srt){

    QVector<T> PSD(fft_length);

    ifft(srt,zerovect);
    get_PSD(srt,zerovect,PSD);

    srt = PSD;

}

template <class T>
void FFT<T>::fft(QVector<T> &srt, QVector<T> &sit){

    int i,a,c,k,d,l,j;
    T rm,im,ss,cc;
    T two = 2.0;



    QVector<T> ssi(fft_length);
    QVector<T> ssr(fft_length);

    for(i=0;i<fft_length;i++){
        ssi[i]=sit[br[i]];
        ssr[i]=srt[br[i]];

    }

    j=static_cast<int>(log2(fft_length));

    d=1;
    for(i=1;i<j+1;i++){
        a=static_cast<int>(pow(2.0,i));
        c=0;
        for(k=0;k<fft_length/a;k++){
            d=a/2;
            for(l=0;l<(a/2);l++){
                ss=-std::sin(two*pi()*static_cast<T>(l)/static_cast<T>(a));
                cc=std::cos(two*pi()*static_cast<T>(l)/static_cast<T>(a));
                rm=ssr[c+d]*cc-ssi[c+d]*ss;
                im=ssr[c+d]*ss+ssi[c+d]*cc;
                ssr[c+d]=ssr[c+l]-rm;
                ssi[c+d]=ssi[c+l]-im;
                ssr[c+l]=ssr[c+l]+rm;
                ssi[c+l]=ssi[c+l]+im;
                d++;
            }c+=a;
        }
    }

    srt = ssr;
    sit = ssi;


}


//void FFT::fft(QVector<float> &srt, QVector<float> &sit){

//    int i,a,c,k,d,l,j;
//    float rm,im,ss,cc;

//    QVector<float> ssi(fft_length);
//    QVector<float> ssr(fft_length);

//    for(i=0;i<fft_length;i++){
//        ssi[i]=sit[br[i]];
//        ssr[i]=srt[br[i]];

//    }

//    j=static_cast<int>(log2(fft_length));

//    d=1;
//    for(i=1;i<j+1;i++){
//        a=static_cast<int>(pow(2.0,i));
//        c=0;
//        for(k=0;k<fft_length/a;k++){d=a/2;
//            for(l=0;l<(a/2);l++){
//                ss=-sinf(2.0f*PI*static_cast<float>(l)/static_cast<float>(a));
//                cc=cosf(2.0f*PI*static_cast<float>(l)/static_cast<float>(a));
//                rm=ssr[c+d]*cc-ssi[c+d]*ss;
//                im=ssr[c+d]*ss+ssi[c+d]*cc;
//                ssr[c+d]=ssr[c+l]-rm;
//                ssi[c+d]=ssi[c+l]-im;
//                ssr[c+l]=ssr[c+l]+rm;
//                ssi[c+l]=ssi[c+l]+im;
//                d++;
//            }c+=a;
//        }
//    }

//    srt = ssr;
//    sit = ssi;


//}
template <class T>
void FFT<T>::ifft(QVector<T> &srt, QVector<T> &sit){

    int i,a,c,k,d,l,j;
    T rm,im,ss,cc;
    T two = 2.0;

    QVector<T> ssi(fft_length);
    QVector<T> ssr(fft_length);

    for(i=0;i<fft_length;i++){
        ssi[i]=srt[br[i]];
        ssr[i]=sit[br[i]];

    }

    j=static_cast<int>(log2(fft_length));

    d=1;
    for(i=1;i<j+1;i++){
        a=static_cast<int>(pow(2.0,i));
        c=0;
        for(k=0;k<fft_length/a;k++){d=a/2;
            for(l=0;l<(a/2);l++){
                ss=-std::sin(two*pi()*static_cast<T>(l)/static_cast<T>(a));
                cc=std::cos(two*pi()*static_cast<T>(l)/static_cast<T>(a));
                rm=ssr[c+d]*cc-ssi[c+d]*ss;
                im=ssr[c+d]*ss+ssi[c+d]*cc;
                ssr[c+d]=ssr[c+l]-rm;
                ssi[c+d]=ssi[c+l]-im;
                ssr[c+l]=ssr[c+l]+rm;
                ssi[c+l]=ssi[c+l]+im;
                d++;
            }c+=a;
        }
    }

    for(i=0;i<fft_length;i++){
        srt[i] = ssi[i]/fft_length;
        sit[i] = ssr[i]/fft_length;
    }

}




#endif /* FFT_H_ */
