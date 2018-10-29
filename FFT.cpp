/*
 * Fft.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: jreberc
 */

#include "FFT.h"

FFT::FFT(int len) {
	std::cout << "Initializing FFT... " << std::endl;

    int newlen=len;

    float power = static_cast<float>(log2(len));

    if(power - static_cast<int>(power) != 0.0f){
        zero_pad = static_cast<int>(pow(2.0,static_cast<int>(power)+1.0))-len;
        newlen=static_cast<int>(pow(2,static_cast<int>(power)+1));
        std::cout << "Length not a power of 2, setting length to: " << newlen << std::endl;
	}else{
		zero_pad = 0;
	}

    fft_length = newlen;
//	br = new int[len];
    br.resize(fft_length);
	bitrev(); 
}

FFT::~FFT() {
    //delete [] br;
	std::cout << "Closing FFT... " << std::endl;
}

//void FFT::print_fft(float *srt){

//	float sig[fft_length];

//	for (int i = 0; i < fft_length; ++i) {
//		sig[i] = srt[i];
//	}

//	fft(sig);
//	DSP::print_wf(sig,fft_length);
//}

//void FFT::print_ifft(float *srt){

//	float sig[fft_length];

//	for (int i = 0; i < fft_length; ++i) {
//		sig[i] = srt[i];
//	}

//	ifft(sig);
//	DSP::print_wf(sig,fft_length);
//}

//void FFT::print_fft(float *srt, float *sit){
//	float PSD[fft_length] = {};
//	float sig[fft_length];
//	float sigi[fft_length];

//	for (int i = 0; i < fft_length; ++i) {
//		sig[i]  = srt[i];
//		sigi[i] = sit[i];
//	}
//	fft(sig,sigi);
//	get_PSD(sig,sigi,PSD);
//	DSP::print_wf(PSD,fft_length);
//}

//void FFT::print_ifft(float *srt, float *sit){
//	float PSD[fft_length] = {};
//	float sig[fft_length];
//	float sigi[fft_length];

//	for (int i = 0; i < fft_length; ++i) {
//		sig[i]  = srt[i];
//		sigi[i] = sit[i];
//	}
//	ifft(sig,sigi);
//	get_PSD(sig,sigi,PSD);
//	DSP::print_wf(PSD,fft_length);
//}

//void FFT::display_fft(float *srt, int abs_scale){

//	float sig[fft_length];

//	for (int i = 0; i < fft_length; ++i) {
//		sig[i] = srt[i];
//	}

//	fft(sig);

//	DSP::display_wf(sig,fft_length,abs_scale);
//}

//void FFT::display_ifft(float *srt, int abs_scale){

//	float sig[fft_length];

//	for (int i = 0; i < fft_length; ++i) {
//		sig[i] = srt[i];
//	}

//	ifft(sig);

//	DSP::display_wf(sig,fft_length,abs_scale);
//}

//void FFT::display_fft(float *srt, float *sit, int abs_scale){
//	float PSD[fft_length] = {};
//	float sig[fft_length];
//	float sigi[fft_length];

//	for (int i = 0; i < fft_length; ++i) {
//		sig[i]  = srt[i];
//		sigi[i] = sit[i];
//	}
//	fft(sig,sigi);
//	get_PSD(sig,sigi,PSD);

//	DSP::display_wf(PSD,fft_length,abs_scale);
//}

//void FFT::display_ifft(float *srt, float *sit, int abs_scale){
//	float PSD[fft_length] = {};
//	float sig[fft_length];
//	float sigi[fft_length];

//	for (int i = 0; i < fft_length; ++i) {
//		sig[i]  = srt[i];
//		sigi[i] = sit[i];
//	}
//	ifft(sig,sigi);
//	get_PSD(sig,sigi,PSD);

//	DSP::display_wf(PSD,fft_length,abs_scale);
//}

void FFT::get_PSD(QVector<float> &srt, QVector<float> &sit, QVector<float> &PSD){
	for (int i = 0; i < fft_length; ++i) {
        PSD[i]=sqrtf(powf(srt[i],2)+powf(sit[i],2));
	}
}


void FFT::set_len(int len){

    int newlen=len;
    float power = static_cast<float>(log2(len));

    if(power - static_cast<int>(power) != 0.0f){
        zero_pad = static_cast<int>(pow(2.0,static_cast<int>(power)+1.0))-len;
        newlen=static_cast<int>(pow(2,static_cast<int>(power)+1));
        std::cout << "Length not a power of 2, setting length to: " << newlen << std::endl;
	}

    fft_length = newlen;
//	delete [] br;
//	br = new int[len];
    br.resize(fft_length);
    bitrev();
}

int FFT::get_len(){
	return fft_length;
}

void FFT::bitrev(){
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


void FFT::fft(QVector<float> &srt){

    QVector<float> sit(fft_length);
    QVector<float> PSD(fft_length);

    sit.fill(0);
    PSD.fill(0);

    fft(srt,sit);

    get_PSD(srt,sit,PSD);

    srt = PSD;
}

void FFT::ifft(QVector<float> &srt){

    QVector<float> sit(fft_length);
    QVector<float> PSD(fft_length);

    sit.fill(0);
    PSD.fill(0);

    ifft(srt,sit);

    get_PSD(srt,sit,PSD);

    srt = PSD;

}

void FFT::fft(QVector<float> &srt, QVector<float> &sit){

    int i,a,c,k,d,l,j;
    float rm,im,ss,cc;

    QVector<float> ssi(fft_length);
    QVector<float> ssr(fft_length);

    for(i=0;i<fft_length;i++){
        ssi[i]=sit[br[i]];
        ssr[i]=srt[br[i]];

    }

    j=static_cast<int>(log2(fft_length));

    d=1;
    for(i=1;i<j+1;i++){
        a=static_cast<int>(pow(2.0,i));
        c=0;
        for(k=0;k<fft_length/a;k++){d=a/2;
            for(l=0;l<(a/2);l++){
                ss=-sinf(2.0f*PI*static_cast<float>(l)/static_cast<float>(a));
                cc=cosf(2.0f*PI*static_cast<float>(l)/static_cast<float>(a));
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
        srt[i] = ssr[i];
        sit[i] = ssi[i];
    }

}

void FFT::ifft(QVector<float> &srt, QVector<float> &sit){

    int i,a,c,k,d,l,j;
    float rm,im,ss,cc;

    QVector<float> ssi(fft_length);
    QVector<float> ssr(fft_length);

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
                ss=-sinf(2.0f*PI*static_cast<float>(l)/static_cast<float>(a));
                cc=cosf(2.0f*PI*static_cast<float>(l)/static_cast<float>(a));
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


//void FFT::fft(float *srt){

//    float sit[fft_length] = {};
//    float PSD[fft_length] = {};

//	fft(srt,sit);

//	get_PSD(srt,sit,PSD);

//	for (int i = 0; i < fft_length; ++i) {
//		srt[i] = PSD[i];
//	}
//}

//void FFT::ifft(float *srt){

//	float sit[fft_length] = {};
//	float PSD[fft_length] = {};

//	ifft(srt,sit);

//	get_PSD(srt,sit,PSD);

//	for (int i = 0; i < fft_length; ++i) {
//		srt[i] = PSD[i];
//	}
//}

//void FFT::fft(float *srt, float *sit){

//	int i,a,c,k,d,l,j;
//	float rm,im,ss,cc;
//	float ssi[fft_length],ssr[fft_length];

//    for(i=0;i<fft_length;i++){
//        ssi[i]=sit[br[i]];
//        ssr[i]=srt[br[i]];

//    }

//    j=log2(fft_length);

//    d=1;
//    for(i=1;i<j+1;i++){
//        a=pow(2.0,i);
//        c=0;
//        for(k=0;k<fft_length/a;k++){d=a/2;
//            for(l=0;l<(a/2);l++){
//                ss=-sin(2.0*M_PI*(double)l/(double)a);
//                cc=cos(2.0*M_PI*(double)l/(double)a);
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

//    for(i=0;i<fft_length;i++){
//    	srt[i] = ssr[i];
//    	sit[i] = ssi[i];
//    }

//}

//void FFT::ifft(float *srt, float *sit){

//	int i,a,c,k,d,l,j;
//	float rm,im,ss,cc;
//	float ssi[fft_length],ssr[fft_length];

//    for(i=0;i<fft_length;i++){
//        ssi[i]=srt[br[i]];
//        ssr[i]=sit[br[i]];

//    }

//    j=log2(fft_length);

//    d=1;
//    for(i=1;i<j+1;i++){
//        a=pow(2.0,i);
//        c=0;
//        for(k=0;k<fft_length/a;k++){d=a/2;
//            for(l=0;l<(a/2);l++){
//                ss=-sin(2.0*M_PI*(double)l/(double)a);
//                cc=cos(2.0*M_PI*(double)l/(double)a);
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

//    for(i=0;i<fft_length;i++){
//    	srt[i] = ssi[i]/fft_length;
//    	sit[i] = ssr[i]/fft_length;
//    }

//}
