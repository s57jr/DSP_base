/*
 * FIRfilter.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: jreberc
 */

#include "FIRfilter.h"

FIRfilter::FIRfilter(int length, string type, float samplerate, float fcutoff_low, float fcutoff_high) {

    set_len(length);
    response = new FFT(len);
    calculate_coefficients(type, samplerate,fcutoff_low, fcutoff_high);
}

FIRfilter::~FIRfilter() {
    //delete [] coefficients;
    //coefficients = nullptr;
	response->~FFT();
}

void FIRfilter::set_len(int length){
    this->len = length+(length%2-1);
    if(length%2 != 1){
        std::cout << "Filter length should be odd! Setting filter length to: "<< len << std::endl;
    }
    coefficients.resize(len);
    save_chunk.resize(len-1);
    save_chunk.fill(0);

}

int FIRfilter::get_len(){
    return len;
}


FIRfilter::StringValue FIRfilter::parse_strings(string input){

	std::cout << "Creating " << input << " filter" << std::endl;

	if(input == "triangular")    {return triangular;}
	else if(input == "hanning")  {return hanning;}
	else if(input == "hamming")  {return hamming;}
	else if(input == "blackman") {return blackman;}
	else if(input == "lowpass")  {return lowpass;}
	else if(input == "highpass") {return highpass;}
	else if(input == "bandpass") {return bandpass;}
	else if(input == "bandstop") {return bandstop;}
	else return error;
}

void FIRfilter::display_coef(MainWindow *MainWindow){

    lol.resize(len);
    lol = coefficients;

    QVector<double> x(len), y(len);

    for(int i=0;i<len;i++){
        x[i]=i;
        y[i]=static_cast<double>(lol[i]);
    }

    MainWindow->Plot("Filter coefficients", x, y);
  //  delete [] lol;
}

//void FIRfilter::display_coef(MainWindow *MainWindow){
//    lol = new float[len+response->zero_pad];

//    for (int i = 0; i < len; ++i) {
//        lol[i] = coefficients[i];
//    }

//    for (int i = len-1; i < len+response->zero_pad-1; ++i) {
//        lol[i] = 0;
//    }

//    QVector<double> x(len), y(len);

//    for(int i=0;i<len;i++){
//        x[i]=i;
//        y[i]=static_cast<double>(lol[i]);
//    }

//    MainWindow->Plot("Filter response", x, y);
//    delete [] lol;
//}

void FIRfilter::print_coef(){
	for (int i = 0; i < len; ++i) {
//		std::cout << coefficients[i] << std::endl;
        std::cout << coefficients.at(i) << std::endl;
	}
}

void FIRfilter::display_resp(MainWindow *MainWindow){

    if(response->zero_pad){
        std::cout <<"Zero padding coefficients for response display: " << response->zero_pad << std::endl;
    }

    lol.resize(response->get_len());

    for (int i = 0; i < response->get_len(); ++i) {

        if(i >=len-1){
            lol[i] = 0;
        }else{
            lol[i] = coefficients[i];
        }
    }

    response->fft(lol);

    QVector<double> x(response->get_len()), y(response->get_len());

    for(int i=0;i<response->get_len();i++){
        x[i]=i;
        y[i]=static_cast<double>(lol[i]);
    }

    MainWindow->Plot("Filter response", x, y);
}

//void FIRfilter::display_resp(MainWindow *MainWindow){

//    lol = new float[len+response->zero_pad];

//    for (int i = 0; i < len; ++i) {
//        lol[i] = coefficients[i];
//        lol[i] = coefficients.at(i);
//    }

//    for (int i = len-1; i < len+response->zero_pad-1; ++i) {
//        lol[i] = 0;
//    }

//    response->fft(lol);

//    QVector<double> x(len), y(len);

//    for(int i=0;i<len;i++){
//        x[i]=i;
//        y[i]=static_cast<double>(lol[i]);
//    }

//    MainWindow->Plot("Filter response", x, y);
//    delete [] lol;
//}

//void FIRfilter::display_resp(int abs_scale){

//    lol = new float[len+response->zero_pad];

//	for (int i = 0; i < len; ++i) {
//        lol[i] = coefficients[i];
//	}

//	for (int i = len-1; i < len+response->zero_pad-1; ++i) {
//        lol[i] = 0;
//	}
//    response->display_fft(lol,abs_scale);
//    delete [] lol;
//}

void FIRfilter::calculate_coefficients(string type, float samplerate, float fcutoff_low, float fcutoff_high ){
    int n = (len/2);
    int i;
    float scalling=0;
    switch(parse_strings(type)){
        case lowpass :
            coefficients[n]=2.0f*(fcutoff_low/samplerate);
            scalling+= coefficients[n];
            for(i=1;i<=n;i++){
                coefficients[n+i] = coefficients[n-i] = sinf(2.0f*PI*static_cast<float>(i)*(fcutoff_low/samplerate))/(static_cast<float>(i)*PI);
                scalling+= coefficients[n+i];
                scalling+= coefficients[n-i];
            }
        break;
        case highpass :
            coefficients[n]=static_cast<float>(1.0)-(static_cast<float>(2.0)*fcutoff_high/samplerate);
            scalling+= coefficients[n];
            for(i=1;i<=n;i++){
                coefficients[n+i] = coefficients[n-i] = -sinf(2.0f*PI*static_cast<float>(i)*(fcutoff_high/samplerate))/(static_cast<float>(i)*PI);
                scalling+= coefficients[n+i];
                scalling+= coefficients[n-i];
            }
        break;
        case bandpass :
            coefficients[n]=(2.0f/samplerate)*(fcutoff_high - fcutoff_low);
            scalling+= coefficients[n];
            for(i=1;i<=n;i++){
                coefficients[n+i] = coefficients[n-i] = (sinf(2.0f*PI*static_cast<float>(i)*(fcutoff_high/samplerate))/(static_cast<float>(i)*PI))
                                                        -(sinf(2.0f*PI*static_cast<float>(i)*(fcutoff_low/samplerate))/(static_cast<float>(i)*PI));
                scalling+= coefficients[n+i];
                scalling+= coefficients[n-i];
            }
        break;
        case bandstop :
            coefficients[n]=1.0f-((2.0f/samplerate)*(fcutoff_high + fcutoff_low));
            scalling+= coefficients[n];
            for(i=1;i<=n;i++){
                coefficients[n+i] = coefficients[n-i] = (-sinf(2.0f*PI*static_cast<float>(i)*(fcutoff_high/samplerate))/(static_cast<float>(i)*PI))
                                                        +(sinf(2.0f*PI*static_cast<float>(i)*(fcutoff_low/samplerate))/(static_cast<float>(i)*PI));
                scalling+= coefficients[n+i];
                scalling+= coefficients[n-i];
            }
        break;
        default:
            std::cout << "Bad filter type! " << std::endl;
    }

    scalling = (1.0f/scalling);
    coefficients[n]*=scalling;
    for(i=1;i<=n;i++){
        coefficients[n+i]=coefficients[n-i]= coefficients[n+i]*scalling;
    }
}


void FIRfilter::window_coefficients(string type){
    int i=1;
    int n = len/2;
    switch(parse_strings(type)){
        case triangular :
            for(i=1;i<=n;i++){
                coefficients[n-i]=coefficients[n+i]=coefficients[n+i]*(1-(static_cast<float>(i)/static_cast<float>(n)));
            }
        break;
        case hanning :
            for(i=1;i<=n;i++){
                coefficients[n-i]=coefficients[n+i]=coefficients[n+i]*(0.5f+0.5f*cosf(static_cast<float>(i)*PI/static_cast<float>(n)));
            }
        break;
        case hamming :
            for(i=1;i<=n;i++){
                coefficients[n-i]=coefficients[n+i]=coefficients[n+i]*(0.54f+0.46f*cosf(static_cast<float>(i)*PI/static_cast<float>(n)));
            }
        break;
        case blackman :
            for(i=1;i<=n;i++){
                coefficients[n-i]=coefficients[n+i]=coefficients[n+i]*(0.42f+0.5f*cosf(static_cast<float>(i)*PI/static_cast<float>(n))
                                               +0.08f*cosf(2.0f*PI*static_cast<float>(i)/static_cast<float>(n)));
            }
        break;
        default:
        	std::cout << "Bad window type! " << std::endl;
    }
}


//void FIRfilter::convolution(float *sig, int sig_length, float* outp){ //make something that ensures filtered has correct length
//    int i,b;
//
//    float out[sig_length+len];
//
//	for (int i = 0; i < sig_length+len; ++i) {
//		out[i]=0;
//	}
//
//    for(i=0;i<sig_length;i++){
//
//    	//out[i+len]=0;
//
//    	if(i >= sig_length-len){
//    		save_chunk[i-(sig_length-len)] = sig[i];
//    	}
//    	for(b=0;b<len;b++){
//
//    		if(i==0){
//    			out[i+b] = 0;
//    		}
//
//    		if(i<len){
//    			out[i+b]=out[i+b]+(save_chunk[i]*coefficients[b]);
//    		}else{
//    			out[i+b]=out[i+b]+(sig[i-len]*coefficients[b]);
//    			if(i==sig_length-1){
//    				outp[i+b] = out[i+b];
//    			}
//    		}
//		}
//
//		if(i<len){
//			std::cout << ", " << save_chunk[i] << std::endl;
//		}
//
//		outp[i] = out[i];
//
//    }
//}

void FIRfilter::convolution(QVector<float> &sig, int sig_length, QVector<float> &outp){ //make something that ensures filtered has correct length
	for (int i = 0; i < sig_length; i++ )
	{
	    outp[i] = 0;    // set to zero before sum

        if(i >= sig_length-(len-1)){
            save_chunk[i-(sig_length-(len-1))] = sig[i];
		}

	    for (int j = 0; j < len; j++ )
	    {
	    	if(i-j < 0){
                outp[i] += (save_chunk[len+(i-j)-1] * coefficients[j]);    // convolve: multiply and accumulate

	    	}else{
                outp[i] += (sig[i - j] * coefficients[j]);                 // convolve: multiply and accumulate
	    	}
	    }
	}
}
