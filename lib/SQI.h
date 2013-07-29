#ifndef SQI_H
#define SQI_H


#include <iostream>
#include "stdio.h"
#include <string>

#include <opencv/cv.hpp>

#include <opencv/cxcore.hpp>
#include "opencv/cvaux.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


//#include "headers.h"
//#include "HGPP.h"

class SQI 
{

  public:
	//constructors
        SQI(int _IMSIZ=64,int _size=9,float _sigma=3.0):IMSIZ(_IMSIZ),size(_size),sigma(_sigma)
        {
	}
	~SQI()
	  {
	  }


	//Accesors
	void setInpImage(cv::Mat img);
	void setParameters(int imsiz_,int size_,float sigma_);
	cv::Mat getOutImage()const
	{
		return out_sqi;
	}


	//Display SQI Image
	void DisplayImage() const
	{
    		
    		cv::namedWindow("Self Quotient Image");
    		cv::imshow("Image", out_sqi);
    		cv::waitKey(0);
		cv::destroyWindow("Self Quotient Image");
	}

	//Main method to get sqi image (includes some normalization as pre-processing)
	void get_self_quo_image();

  private:
	cv::Mat in_img;
	int IMSIZ,size;
	float sigma;
	cv::Mat out_sqi;


};

#endif
