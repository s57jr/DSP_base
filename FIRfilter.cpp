///*
// * FIRfilter.cpp
// *
// *  Created on: Oct 10, 2018
// *      Author: jreberc
// */

//#include "FIRfilter.h"

//template <class T>
//FIRfilter<T>::FIRfilter(int length, string type, T samplerate, T fcutoff_low, T fcutoff_high): FFT<T>(length) {

//    set_filter_len(length);
//    calculate_coefficients(type, samplerate,fcutoff_low, fcutoff_high);
//}

//template <class T>
//FIRfilter<T>::~FIRfilter() {

//}

//template <class T>
//void FIRfilter<T>::set_filter_len(int length){
//    this->filter_len = length+(length%2-1);
//    if(length%2 != 1){
//        std::cout << "Filter length should be odd! " << std::endl;
//    }

//    std::cout << "Setting filter length to: " << filter_len << std::endl;

//    coefficients.resize(filter_len);
//    save_chunk.resize(filter_len-1);
//    save_chunk.fill(0);

//}

//template <class T>
//int FIRfilter<T>::get_filter_len(){
//    return filter_len;
//}

//template <class T>
//typename FIRfilter<T>::StringValue FIRfilter<T>::parse_strings(string input){

//	std::cout << "Creating " << input << " filter" << std::endl;

//	if(input == "triangular")    {return triangular;}
//	else if(input == "hanning")  {return hanning;}
//	else if(input == "hamming")  {return hamming;}
//	else if(input == "blackman") {return blackman;}
//	else if(input == "lowpass")  {return lowpass;}
//	else if(input == "highpass") {return highpass;}
//	else if(input == "bandpass") {return bandpass;}
//	else if(input == "bandstop") {return bandstop;}
//	else return error;
//}

//template <class T>
//void FIRfilter<T>::display_coef(MainWindow *MainWindow){

//    dispcoef.resize(filter_len);
//    dispcoef = coefficients;

//    DSP::display_wf(dispcoef, filter_len, "Filter coefficients" ,MainWindow);

////    QVector<double> x(filter_len), y(filter_len);

////    for(int i=0;i<filter_len;i++){
////        x[i]=i;
////        y[i]=static_cast<double>(dispcoef[i]);
////    }

////    MainWindow->Plot("Filter coefficients", x, y);
//}

//template <class T>
//void FIRfilter<T>::print_coef(){
//    for (int i = 0; i < filter_len; ++i) {
//        std::cout << coefficients.at(i) << std::endl;
//	}
//}

//template <class T>
//void FIRfilter<T>::display_resp(MainWindow *MainWindow){

//    dispcoef.resize(FFT<T>::get_fft_len());


//    for (int i = 0; i < FFT<T>::get_fft_len(); ++i) {

//        if(i >=filter_len-1){
//            dispcoef[i] = 0;
//        }else{
//            dispcoef[i] = coefficients[i];
//        }
//    }

//    FFT<T>::fft_PSD(dispcoef);

//    DSP::display_wf(dispcoef,FFT<T>::get_fft_len(), "Filter response" ,MainWindow);

////    QVector<double> x(get_fft_len()), y(get_fft_len());

////    for(int i=0;i<get_fft_len();i++){
////        x[i]=i;
////        y[i]=static_cast<double>(dispcoef[i]);
////    }

////    MainWindow->Plot("Filter response", x, y);
//}

//template <class T>
//void FIRfilter<T>::calculate_coefficients(string type, T samplerate, T fcutoff_low, T fcutoff_high ){
//    int n = (filter_len/2);
//    int i;
//    T two = 2.0;
//    T scalling=0;
//    switch(parse_strings(type)){
//        case lowpass :
//            coefficients[n]=two*(fcutoff_low/samplerate);
//            scalling+= coefficients[n];
//            for(i=1;i<=n;i++){
//                coefficients[n+i] = coefficients[n-i] = std::sin(two*pi()*static_cast<T>(i)*(fcutoff_low/samplerate))/(static_cast<T>(i)*pi());
//                scalling+= coefficients[n+i];
//                scalling+= coefficients[n-i];
//            }
//        break;
//        case highpass :
//            coefficients[n]=static_cast<float>(1.0)-(static_cast<float>(2.0)*fcutoff_high/samplerate);
//            scalling+= coefficients[n];
//            for(i=1;i<=n;i++){
//                coefficients[n+i] = coefficients[n-i] = -std::sin(two*pi()*static_cast<T>(i)*(fcutoff_high/samplerate))/(static_cast<T>(i)*pi());
//                scalling+= coefficients[n+i];
//                scalling+= coefficients[n-i];
//            }
//        break;
//        case bandpass :
//            coefficients[n]=(2.0f/samplerate)*(fcutoff_high - fcutoff_low);
//            scalling+= coefficients[n];
//            for(i=1;i<=n;i++){
//                coefficients[n+i] = coefficients[n-i] = (std::sin(two*pi()*static_cast<T>(i)*(fcutoff_high/samplerate))/(static_cast<T>(i)*pi()))
//                                                        -(std::sin(two*pi()*static_cast<T>(i)*(fcutoff_low/samplerate))/(static_cast<T>(i)*pi()));
//                scalling+= coefficients[n+i];
//                scalling+= coefficients[n-i];
//            }
//        break;
//        case bandstop :
//            coefficients[n]=1.0f-((two/samplerate)*(fcutoff_high + fcutoff_low));
//            scalling+= coefficients[n];
//            for(i=1;i<=n;i++){
//                coefficients[n+i] = coefficients[n-i] = (-std::sin(two*pi()*static_cast<T>(i)*(fcutoff_high/samplerate))/(static_cast<T>(i)*pi()))
//                                                        +(std::sin(two*pi()*static_cast<T>(i)*(fcutoff_low/samplerate))/(static_cast<T>(i)*pi()));
//                scalling+= coefficients[n+i];
//                scalling+= coefficients[n-i];
//            }
//        break;
//        default:
//            std::cout << "Bad filter type! " << std::endl;
//    }

//    scalling = (1.0f/scalling);
//    coefficients[n]*=scalling;
//    for(i=1;i<=n;i++){
//        coefficients[n+i]=coefficients[n-i]= coefficients[n+i]*scalling;
//    }
//}

//template <class T>
//void FIRfilter<T>::window_coefficients(string type){
//    int i=1;
//    T two = 2.0;
//    T one = 2.0;
//    T pfive = 0.5;
//    T pfivefour = 0.5;
//    T pfoursix = 0.46;
//    T pfourtwo = 0.42;
//    T pzeroeight = 0.08;

//    int n = filter_len/2;
//    switch(parse_strings(type)){
//        case triangular :
//            for(i=1;i<=n;i++){
//                coefficients[n-i]=coefficients[n+i]=coefficients[n+i]*(one-(static_cast<T>(i)/static_cast<T>(n)));
//            }
//        break;
//        case hanning :
//            for(i=1;i<=n;i++){
//                coefficients[n-i]=coefficients[n+i]=coefficients[n+i]*(pfive+pfive*std::cos(static_cast<T>(i)*pi()/static_cast<T>(n)));
//            }
//        break;
//        case hamming :
//            for(i=1;i<=n;i++){
//                coefficients[n-i]=coefficients[n+i]=coefficients[n+i]*(pfivefour+pfoursix*std::cos(static_cast<T>(i)*pi()/static_cast<T>(n)));
//            }
//        break;
//        case blackman :
//            for(i=1;i<=n;i++){
//                coefficients[n-i]=coefficients[n+i]=coefficients[n+i]*(pfourtwo+pfive*std::cos(static_cast<T>(i)*pi()/static_cast<T>(n))
//                                               +pzeroeight*std::cos(two*pi()*static_cast<T>(i)/static_cast<T>(n)));
//            }
//        break;
//        default:
//        	std::cout << "Bad window type! " << std::endl;
//    }
//}

//template <class T>
//void FIRfilter<T>::convolution(QVector<T> &sig, int sig_length, QVector<T> &outp){ //make something that ensures filtered has correct length
//	for (int i = 0; i < sig_length; i++ )
//	{
//	    outp[i] = 0;    // set to zero before sum

//        if(i >= sig_length-(filter_len-1)){
//            save_chunk[i-(sig_length-(filter_len-1))] = sig[i];
//		}

//        for (int j = 0; j < filter_len; j++ )
//	    {
//	    	if(i-j < 0){
//                outp[i] += (save_chunk[filter_len+(i-j)-1] * coefficients[j]);    // convolve: multiply and accumulate

//	    	}else{
//                outp[i] += (sig[i - j] * coefficients[j]);                 // convolve: multiply and accumulate
//	    	}
//	    }
//	}
//}

//template class FIRfilter<float>;
//template class FIRfilter<double>;

//template class FFT<float>;
//template class FFT<double>;
