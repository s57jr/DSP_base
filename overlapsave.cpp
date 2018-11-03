//#include "overlapsave.h"

//template <class T>
//OverlapSave<T>::OverlapSave(int filter_length, int signal_length, string filter_type, string window_type, T samplerate, T fcutoff_low, T fcutoff_high) :
//    FIRfilter<T>(filter_length, filter_type, samplerate, fcutoff_low, fcutoff_high)
//{
//    set_sig_length(signal_length);
//    window_coefficients(window_type);

//    std::cout << "Initializing FFT class for Overlap-Add filtering " << std::endl;

//    ovsavefft=new FFT<T>(sig_length+FIRfilter<T>::filter_len-1);
//    ovsave_coef_resp_r.resize(ovsavefft->get_fft_len());
//    ovsave_coef_resp_i.resize(ovsavefft->get_fft_len());

//    for(int i=0;i<ovsavefft->get_fft_len();i++){
//        if(i>=FIRfilter<T>::filter_len){
//            ovsave_coef_resp_r[i] = 0;
//        }else{
//            ovsave_coef_resp_r[i] = FIRfilter<T>::coefficients[i];
//        }
//    }


//    ovsavesig_r.resize(ovsavefft->get_fft_len());
//    ovsavesig_i.resize(ovsavefft->get_fft_len());
//    ovsavesig1_r.resize(ovsavefft->get_fft_len());
//    ovsavesig1_i.resize(ovsavefft->get_fft_len());
//    save_add.resize(FIRfilter<T>::filter_len-1);
//    save_add.fill(0);

//    ovsavefft->fft(ovsave_coef_resp_r,ovsave_coef_resp_i);
//}

//template <class T>
//OverlapSave<T>::~OverlapSave() {
//    ovsavefft->~FFT();
//}

//template <class T>
//int OverlapSave<T>::get_filter_len(){
//    return FIRfilter<T>::get_filter_len();
//}

//template <class T>
//void OverlapSave<T>::window_coefficients(string type){
//    FIRfilter<T>::window_coefficients(type);
//}

//template <class T>
//void OverlapSave<T>::display_coef(MainWindow *MainWindow){
//    FIRfilter<T>::display_coef(MainWindow);
//}

//template <class T>
//void OverlapSave<T>::display_resp(MainWindow *MainWindow){

//    FIRfilter<T>::dispcoef.resize(FIRfilter<T>::get_fft_len());


//    for (int i = 0; i < FIRfilter<T>::get_fft_len(); ++i) {

//        if(i >=FIRfilter<T>::filter_len-1){
//            FIRfilter<T>::dispcoef[i] = 0;
//        }else{
//            FIRfilter<T>::dispcoef[i] = FIRfilter<T>::coefficients[i];
//        }
//    }

//    FIRfilter<T>::fft_PSD(FIRfilter<T>::dispcoef);

//    DSP::display_wf(FIRfilter<T>::dispcoef,FIRfilter<T>::get_fft_len(),"Filter response" ,MainWindow );
////    QVector<double> x(FIRfilter<T>::get_fft_len()), y(FIRfilter<T>::get_fft_len());

////    for(int i=0;i<FIRfilter<T>::get_fft_len();i++){
////        x[i]=i;
////        y[i]=static_cast<double>(FIRfilter<T>::dispcoef[i]);
////    }

////    MainWindow->Plot("Filter response", x, y);
//}

//template <class T>
//int OverlapSave<T>::get_sig_length(){
//    return sig_length;
//}

//template <class T>
//void OverlapSave<T>::set_sig_length(int length){

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
//void OverlapSave<T>::filter(QVector<T> &sig, QVector<T> &filtered){

//    if(sig.size() != sig_length){
//        return;
//    }

//    ovsavesig_r=save_add+sig;
//    ovsavesig_i.fill(0);

//    ovsavefft->fft(ovsavesig_r,ovsavesig_i);

//    for(int i=0;i<ovsavefft->get_fft_len();i++){
//        ovsavesig1_r[i] = ovsavesig_r[i]*ovsave_coef_resp_r[i]-ovsavesig_i[i]*ovsave_coef_resp_i[i];
//        ovsavesig1_i[i] = ovsavesig_i[i]*ovsave_coef_resp_r[i]+ovsavesig_r[i]*ovsave_coef_resp_i[i];

//    }

//    ovsavefft->ifft(ovsavesig1_r, ovsavesig1_i);

//    //copy and save
//    for(int i=0;i<ovsavefft->get_fft_len()-(FIRfilter<T>::filter_len-1);i++){

//        if(i<FIRfilter<T>::filter_len-1){
//            save_add[i] = sig[sig_length-(FIRfilter<T>::filter_len-1)+i];
//        }
//        filtered[i]=ovsavesig1_r[i+(FIRfilter<T>::filter_len-1)];
//    }

//}

//template class OverlapSave<float>;
//template class OverlapSave<double>;

//template class FIRfilter<float>;
//template class FIRfilter<double>;

//template class FFT<float>;
//template class FFT<double>;
