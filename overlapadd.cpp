//#include "overlapadd.h"


//template <class T>
//OverlapAdd<T>::OverlapAdd(int filter_length, int signal_length, string filter_type, string window_type, T samplerate, T fcutoff_low, T fcutoff_high) :
//    FIRfilter<T>(filter_length, filter_type, samplerate, fcutoff_low, fcutoff_high)
//{

//    set_sig_length(signal_length);
//    window_coefficients(window_type);

//    std::cout << "Initializing FFT class for Overlap-Add filtering " << std::endl;

//    ovaddfft=new FFT<T>(sig_length+FIRfilter<T>::filter_len-1);
//    ovadd_coef_resp_r.resize(ovaddfft->get_fft_len());
//    ovadd_coef_resp_i.resize(ovaddfft->get_fft_len());

//    for(int i=0;i<ovaddfft->get_fft_len();i++){
//        if(i>=FIRfilter<T>::filter_len){
//            ovadd_coef_resp_r[i] = 0;
//        }else{
//            ovadd_coef_resp_r[i] = FIRfilter<T>::coefficients[i];
//        }
//    }


//    ovaddsig_r.resize(ovaddfft->get_fft_len());
//    ovaddsig_i.resize(ovaddfft->get_fft_len());
//    ovaddsig1_r.resize(ovaddfft->get_fft_len());
//    ovaddsig1_i.resize(ovaddfft->get_fft_len());
//    save_add_r.resize(FIRfilter<T>::filter_len-1);
//    save_add_i.resize(FIRfilter<T>::filter_len-1);
//    padding_zeros.resize(FIRfilter<T>::filter_len-1);
//    padding_zeros.fill(0);
//    ovaddfft->fft(ovadd_coef_resp_r,ovadd_coef_resp_i);

//}

//template <class T>
//OverlapAdd<T>::~OverlapAdd() {
//    ovaddfft->~FFT();
//}

//template <class T>
//int OverlapAdd<T>::get_filter_len(){
//    return FIRfilter<T>::get_filter_len();
//}

//template <class T>
//void OverlapAdd<T>::window_coefficients(string type){
//    FIRfilter<T>::window_coefficients(type);
//}

//template <class T>
//void OverlapAdd<T>::display_coef(MainWindow *MainWindow){
//    FIRfilter<T>::display_coef(MainWindow);
//}

//template <class T>
//void OverlapAdd<T>::display_resp(MainWindow *MainWindow){
// //   FIRfilter::display_resp(MainWindow);
//    FIRfilter<T>::dispcoef.resize(FIRfilter<T>::get_fft_len());

//    for (int i = 0; i < FIRfilter<T>::get_fft_len(); ++i) {

//        if(i >=FIRfilter<T>::filter_len-1){
//            FIRfilter<T>::dispcoef[i] = 0;
//        }else{
//            FIRfilter<T>::dispcoef[i] = FIRfilter<T>::coefficients[i];
//        }
//    }

//    FIRfilter<T>::fft_PSD(FIRfilter<T>::dispcoef);

//    DSP::display_wf(FIRfilter<T>::dispcoef,FIRfilter<T>::get_fft_len(), "Filter response" ,MainWindow);

////    QVector<double> x(FIRfilter<T>::get_fft_len()), y(FIRfilter<T>::get_fft_len());

////    for(int i=0;i<FIRfilter<T>::get_fft_len();i++){
////        x[i]=i;
////        y[i]=static_cast<double>(FIRfilter<T>::dispcoef[i]);
////    }

////    MainWindow->Plot("Filter response", x, y);
//}

//template <class T>
//int OverlapAdd<T>::get_sig_length(){
//    return sig_length;
//}

//template <class T>
//void OverlapAdd<T>::set_sig_length(int length){

//    int addlen=0;

//    float power = static_cast<float>(log2(length+FIRfilter<T>::filter_len-1));

//    if(power - static_cast<int>(power) != 0.0f){
//        addlen = static_cast<int>(pow(2.0,static_cast<int>(power)+1.0))-(length+FIRfilter<T>::filter_len-1);
//        std::cout << "Chosen length can not be applied! Make sure (filter_length+signal_length-1) is a power of 2! " << std::endl;
//    }

//    std::cout << "Setting signal length to: " << length+addlen << std::endl;

//    sig_length = length+addlen;
//}

//template <class T>
//void OverlapAdd<T>::filter(QVector<T> &sig, QVector<T> &filtered){

//    if(sig.size() != sig_length){
//        return;
//    }

//    ovaddsig_r=sig+padding_zeros;
//    ovaddsig_i.fill(0);

//    ovaddfft->fft(ovaddsig_r,ovaddsig_i);

//    for(int i=0;i<ovaddfft->get_fft_len();i++){
//        ovaddsig1_r[i] = ovaddsig_r[i]*ovadd_coef_resp_r[i]-ovaddsig_i[i]*ovadd_coef_resp_i[i];
//        ovaddsig1_i[i] = ovaddsig_i[i]*ovadd_coef_resp_r[i]+ovaddsig_r[i]*ovadd_coef_resp_i[i];

//    }

//    ovaddfft->ifft(ovaddsig1_r, ovaddsig1_i);

//    //copy and save
//    for(int i=0;i<ovaddfft->get_fft_len();i++){
//        if(i<FIRfilter<T>::filter_len-1){
//            filtered[i]=save_add_r[i]+ovaddsig1_r[i];

//        }else if(i >= sig_length){
//            save_add_r[i-sig_length] = ovaddsig1_r[i];
//            save_add_i[i-sig_length] = ovaddsig1_i[i];
//        }else{
//            filtered[i] = ovaddsig1_r[i];
//        }
//    }
//}


//template class  OverlapAdd<double>;
//template class  OverlapAdd<float>;

//template class FIRfilter<float>;
//template class FIRfilter<double>;

//template class FFT<float>;
//template class FFT<double>;
