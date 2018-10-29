#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include "FFT.h"
#include "SigGen.h"
#include "FIRfilter.h"

/*
 * TODO SHOULD DO:
 * 1.create functions/classes so types can be selected (float, double)
 *
 *
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


    const int lenmult = 3;

    const int sr = 1000;
    int filt_len = 16;

    const int tstlen = 64-filt_len+1;
//    float delta[tstlen*lenmult];
//    float sit[tstlen] = {};
//    float filtered[filt_len+tstlen-1] = {};

    QVector<float> delta(tstlen*lenmult);
    QVector<float> sit(tstlen);
    QVector<float> filtered(filt_len+tstlen-1);

    SigGen testgen(sr,20);

    FIRfilter filt(filt_len,"lowpass",sr,200,200);
    filt_len = filt.get_len();
    filt.window_coefficients("hanning");
    filt.display_coef(&w);
    filt.display_resp(&w);

   testgen.delta_func(delta,tstlen*lenmult,0);
    testgen.cosine(delta, tstlen*lenmult);

    QVector<float> y(filtered.size()*lenmult);
    QVector<float> x(filtered.size()*lenmult);

    for(int k=0;k<filtered.size()*lenmult;k++){
        x[k]=k;
    }

    for (int i = 0; i < lenmult; ++i) {

        for (int j = 0; j < tstlen; ++j) {
            sit[j]=delta[j+(i*tstlen)];
        }

        filt.convolution(sit,tstlen,filtered);


        for(int k=0;k<tstlen;k++){
            y[(i*tstlen)+k]=filtered.at(k);
        }

        w.Plot("graf",x,y);

    }

    return a.exec();
}
