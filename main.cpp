#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include "FFT.h"
#include "SigGen.h"
#include "FIRfilter.h"
#include "overlapadd.h"
#include "overlapsave.h"

/*
 * TODO SHOULD DO:
 * 1. try to move definitions of templated classes into .cpp files..
 * 2.//HANDLE this: user should not be able to set fft length from this class, however the method in the base class is public. Setting base class as private causes error in overlapadd.h ...
 * 3. Implement functions to use QComplexNumber Class
 * 4. ovadd and ovsave can have the same base class...
 *
 * TODO IDEAS:
 * The overlap�save algorithm may be extended to include other common operations of a system:
    1.additional channels cn be processed more cheaply than the first by reusing the forward FFT
    2.sampling rates can be changed by using different sized forward and inverse FFTs
    3.frequency translation (mixing) can be accomplished by rearranging frequency bins
 * */


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    const int lenmult = 4;

    const int sr = 1000;
    int filt_len = 18;

    int tstlen = 64-filt_len+1;

//    float delta[tstlen*lenmult];
//    float sit[tstlen] = {};
//    float filtered[filt_len+tstlen-1] = {};

//    FIRfilter <double> filt (filt_len,"lowpass",sr,200,200);
//    filt_len = filt.get_filter_len();
//    filt.window_coefficients("hanning");
//    filt.display_coef(&w);
//    filt.display_resp(&w);

    OverlapSave<double> oadd(filt_len,tstlen,"lowpass", "blackman",sr,20,200);

    //correct sizes if necessary
    filt_len = oadd.get_filter_len();
    tstlen = 64-filt_len+1;

    oadd.window_coefficients("hanning");
    oadd.display_coef(&w);
    oadd.display_resp(&w);



    QVector<double> delta(tstlen*lenmult);
    QVector<double> srt(tstlen);
    QVector<double> sit(tstlen);
    QVector<double> filtered(filt_len+tstlen-1);

    SigGen<double> testgen(sr,20);

    testgen.delta_func(delta,tstlen*lenmult,0);
    testgen.cosine(delta, tstlen*lenmult);

    QVector<double> y(filtered.size()*lenmult);
    QVector<double> x(filtered.size()*lenmult);

    for(int k=0;k<filtered.size()*lenmult;k++){
        x[k]=k;
    }

    /***********************************************************************/

//    lol.fft(srt,sit);

//    lol.fft(filtr,filti);

//    for(int i=0;i<4;i++){
//        outr[i] = srt[i]*filtr[i]-sit[i]*filti[i];
//        outi[i] = sit[i]*filtr[i]+srt[i]*filti[i];
//        std::cout << "out: " << outr[i] <<" + "<<outi[i] << "j "<< std::endl;
//    }
//    lol.ifft(outr,outi);

//    for(int i=0;i<4;i++){
//        std::cout << "out: " << outr[i] <<" + "<<outi[i] << "j "<< std::endl;
//    }

//    FFT lol(64);
//    QVector<float> xxx(64);
//    srt.resize(64);
//    sit.resize(64);
//    sit.fill(0);

//    for(int k=0;k<64;k++){
//        xxx[k]=k;
//    }

//    for (int j = 0; j < 64; ++j) {
//        srt[j]=delta[j];
//    }

//    w.Plot("graf",xxx,srt);
//    lol.fft(srt,sit);
//    w.Plot("graf",xxx,srt);
//    w.Plot("graf",xxx,sit);
//    lol.ifft(srt);
//    w.Plot("graf",xxx,srt);
//    lol.fft(srt);
//    w.Plot("graf",xxx,srt);

    /***********************************************************************/

    for (int i = 0; i < lenmult; ++i) {

        for (int j = 0; j < tstlen; ++j) {
            srt[j]=delta[j+(i*tstlen)];
        }

       // filt.convolution(srt,tstlen,filtered);
        oadd.filter(srt,filtered);

        for(int k=0;k<tstlen;k++){
            y[(i*tstlen)+k]=filtered.at(k);
        }

        w.Plot("graf",x,y);

    }

    return a.exec();
}
