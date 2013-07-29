#ifndef GABORFILTER_H_
#define GABORFILTER_H_

#include "headers.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include "stdio.h"
#include <string>

#include <opencv/cv.hpp>

#include <opencv/cxcore.hpp>
#include "opencv/cvaux.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>





class GaborFilter{

  public:
//constructor,destructor
                GaborFilter(int _scale=5,int _orient=8,int _IMSIZ=64,int _FILTSIZ=65,float _fmax=.5*pi,float _sigma_g=2*pi): scale(_scale),orient(_orient),IMSIZ(_IMSIZ),FILTSIZ(_FILTSIZ),fmax(_fmax),sigma_g(_sigma_g)
                {
		
		  std::vector <cv::Mat> GaborFilter_r,GaborFilter_i;
		  std::vector <cv::Mat> FiltResp_r,FiltResp_i;
			ResetStructures();
                }
                
        ~GaborFilter()
                {
		  for (int p=0;p<GaborFilt_r.size();p++)
                        {
                                GaborFilt_r.pop_back();
                                GaborFilt_i.pop_back();
                                FiltResp_r.pop_back();
                                FiltResp_i.pop_back();
                        }
		
		}

        //Computational Methods
        void ComputeFilterResponse(cv::Mat);
        void ComputeFilter();


        //Interface
        void SetParameter(std::string name,std::string value);
	vector<cv::Mat> GetFilterOutput(bool isReal) const;
        void PrintParameters()const
                {
                        cout<<" The parameters for the gabor filter bank are..."<<endl;
                        cout<<" \t There are %d"<<scale*orient<<" filters in the bank"<<endl;
                        cout<<" \t The frequency of the filters is set to %4.2f pi"<<fmax/pi<<endl;
                        cout<<" \t The spatial aspect ratio of the filters is set to %4.2f pi"<<sigma_g/pi<<endl;
                }



        private:
        //Member variables
        Mat inp_img;
        int scale,orient;
        float sigma_g,fmax;
	int IMSIZ,FILTSIZ;// FILTSIZ is the size of the filter and IMSIZ the size of the output image
	std::vector<cv::Mat> GaborFilt_r,GaborFilt_i;
	std::vector<cv::Mat> FiltResp_r,FiltResp_i;

	//Internal method to reset i/o structures upon change of parameters
	void ResetStructures();

};

#endif


