#ifndef FEAT_EXT_H
#define FEAT_EXT_H

#include "headers.h"
#include "SQI.h"
#include "GaborPhasePatterns.h"
#include "GaborFilter.h"


string int2string(int num);

class FeatureExtractor {

  private:
	int scale,orient;
	int NBINS;
	int size;
	float sigma,_fmax,_sigma_g;
	int IMSIZ,_FILTSIZ;
	int _reg_size[2],_overlap[2];
  protected:
	cv::Mat inp_img;
	SQI sqi;
	HGPP hgpp;
	GaborFilter filt;

  public:
	//constructor
 FeatureExtractor(int scale=5,int orient=8,int NBINS=16,int size=9,int sigma=3.0,int IMSIZ=64, int FILTSIZ=65,float fmax=.5*pi,float sigma_g=2*pi,int reg_size_y=8,int reg_size_x=8,int overlap_y=4,int overlap_x=4) : scale(scale),orient(orient),sqi(IMSIZ,size,sigma),filt(scale,orient,IMSIZ,FILTSIZ,fmax,sigma_g),hgpp(reg_size_y,reg_size_x,overlap_y,overlap_x,NBINS,scale,orient)
	{
	}

	//destructor (add later)
	~FeatureExtractor()
	  {
	    inp_img.release();
	  }
        // reset some structures after extraction features from an image
	void ResetStructures();

        //Display Image
	void DisplayImage(cv::Mat img) const;

	// add new image for this extraction method
	//include pre-processing like grayscale conversion resizing
	void AddNewImage(cv::Mat img);


	// set parameters
	void SetParameter(std::string name, std::string value);

        //Extract HGPP Feature (include self quotient image as sub-class) 
	void ExtractHGPPFeature();



	Mat RetrieveOutputFeature(bool isSQI=false,bool isReal=true,bool isGGPP=true);
        //will return SQI image if isSQI=true and so on
        // Will return reall GGPP by default
	
};

#endif
