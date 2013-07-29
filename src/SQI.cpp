#include "SQI.h"

// Source code to compute self-quotient image


void SQI::get_self_quo_image()
    {

    out_sqi=cv::Mat(IMSIZ, IMSIZ, CV_32FC1);


    cv::Size k_size(size,size);
    cv::Mat tmp = cv::Mat(in_img.size().height,in_img.size().width, CV_32FC1);

    if(in_img.size()==cv::Size(IMSIZ,IMSIZ))	
 	{
 		out_sqi=in_img;
	}
  	else
  	{
	  cv::resize(in_img,out_sqi,out_sqi.size(),CV_INTER_AREA);
  	}

    // Smooth
    GaussianBlur(out_sqi,tmp,k_size,sigma);


    // Divide
    cv::divide(out_sqi, tmp, out_sqi);

    tmp.release();

}




void SQI::setInpImage(cv::Mat old_img){
	
	in_img=old_img;
}

void SQI::setParameters(int _IMSIZ,int _size,float _sigma){

	IMSIZ=_IMSIZ;
	size=_size;
	sigma=_sigma;

}




