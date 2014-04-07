#include "headers.h"
#include "SQI.h"
#include "FeatureExtractor.h"
#include "GaborFilter.h"
#include "GaborPhasePatterns.h"
#include <opencv2/opencv.hpp>



void FeatureExtractor::AddNewImage(Mat img) {

	Mat tmp = cv::Mat(img.size().height,img.size().width, CV_32FC1);
	Mat tmp2 = cv::Mat(img.size().height,img.size().width, CV_32FC1);

	Scalar mean,stdev;

	 //reset input image depending on paramters first
	ResetStructures();
        


        // convert to a gray scale image  and resize
      	//**check if grayscale or not first
        img.convertTo(tmp2,CV_32FC1);
	cvtColor( tmp2, tmp,CV_RGB2GRAY); 

	cv::resize(tmp,inp_img,inp_img.size(),0,0,0);	

	cv::meanStdDev(inp_img,mean,stdev);	


	mean.val[0] *= -1;
			
        cv::scaleAdd(cv::Mat::ones(inp_img.size(),inp_img.type()),mean.val[0],inp_img,inp_img);
	
	//ERROR: if standard deviation is zero do differently
 
	
	if(stdev.val[0]!=0)
	  {stdev.val[1]=1.0/stdev.val[0];}
        else 
	  {stdev.val[1]=1;}	

        inp_img=inp_img*stdev.val[1];
      

                                   
	//release data
	tmp.release();
	tmp2.release();

}


void FeatureExtractor::SetParameter(string name, string value) {

	CV_FUNCNAME( "HGPP::SetParameter");

	// check parameters

	if(name.compare("scale")==0){
		scale=atoi(value.c_str());
	}
	else if(name.compare("orient")==0){
		orient=atoi(value.c_str());
	}
	else if(name.compare("NBINS")==0){
		NBINS=atoi(value.c_str());
	}
	else if(name.compare("size")==0){
		size=atoi(value.c_str());
	}
	else if(name.compare("sigma")==0){
		sigma=atof(value.c_str());
	}
	else if(name.compare("IMSIZE")==0){
		IMSIZ=atoi(value.c_str());
	}
	else if(name.compare("FILTSIZE")==0){
		_FILTSIZ=atoi(value.c_str());
	}
	else if(name.compare("fmax")==0){
	        _fmax=atof(value.c_str());
	}
	else if(name.compare("sigma_g")==0){
	        _sigma_g=atof(value.c_str());
	}	
	else if(name.compare("region_size_x")==0){
	        _reg_size[1]=atoi(value.c_str());
	}	
        else if(name.compare("region_size_y")==0){
	        _reg_size[0]=atoi(value.c_str());
	}
	else if(name.compare("overlap_x")==0){
	        _overlap[0]=atoi(value.c_str());
	}
        else if(name.compare("overlap_y")==0){
	        _overlap[1]=atoi(value.c_str());
	}
	else if(name.compare("sigma_g")==0){
	        _sigma_g=atof(value.c_str());
	}	
	else {
		printf("Parameter '%s' invalid\n", name.c_str());
		exit(2);
	}
       

}


void FeatureExtractor::ResetStructures() {

	if((inp_img.size().height!=IMSIZ) || (inp_img.size().width!=IMSIZ)){
		inp_img = cv::Mat(IMSIZ,IMSIZ, CV_8UC1);
	}

}


void FeatureExtractor::DisplayImage(Mat img) const{
    	namedWindow("Image");
    	imshow("Image", img);
    	waitKey(0);
	destroyWindow("Image");

}


void FeatureExtractor::ExtractHGPPFeature()
{
        //Initialize Gabor Filter
	  cout<<"\t Passing Input Paramters...."<<endl;
	  filt.SetParameter("IMSIZ",int2string(IMSIZ));
	  filt.SetParameter("scale",int2string(scale));
	  filt.SetParameter("orient",int2string(orient));
	  filt.SetParameter("FILTSIZ",int2string(_FILTSIZ));
	  filt.SetParameter("fmax",std::to_string(_fmax));
	  filt.SetParameter("sigma_g",std::to_string(_sigma_g));

          cout<<"\t Compute Gabor Filters...."<<endl;
          filt.ComputeFilter();
	  
	   
	  cout<<"\t Compute Self Quotient Image"<<endl;
	  // set input and paramters for SQI feature Extractor
	  sqi.setInpImage(inp_img);
	  sqi.setParameters(IMSIZ,size,sigma);
	  sqi.get_self_quo_image();//Compute Self Quotient Image
		

	  //Compute Filter Response
	  filt.ComputeFilterResponse(sqi.getOutImage());	
       	
	  // retrieve output feature	
	  cout<<"\t Computing Gabor Phase Patterns"<<endl;	
	  hgpp.SetParameter(NBINS,_reg_size,_overlap);


	  //Compute Real Parts of LGPP and GGPP
	  bool isReal=true;
	  hgpp.setFilteredInput(filt.GetFilterOutput(isReal));//inherited from GPP base class
	
	  hgpp.ComputeLGPP(isReal);//inherited from the GaborPhasePatterns base class 
	  cout<<"\t Computing GGPP"<<endl;
	  hgpp.ComputeGGPP(isReal);//

	  cout<<"\t Computing the Histogram of GPP"<<endl;

	  // Compute Imaginary Parts of LGPP and GGPP
	  hgpp.setFilteredInput(filt.GetFilterOutput(!isReal));
	  hgpp.ComputeLGPP(!isReal);//inherited from the GaborPhasePatterns base class 
	  hgpp.ComputeGGPP(!isReal);


	
	  cout<<"\t Computing Histogram of Gabor Phase Patterns"<<endl;
	  bool isGGPP=true;
	  hgpp.ComputeHistogram(!isReal,!isGGPP);//LGPP Imag
	  hgpp.ComputeHistogram(isReal,!isGGPP);//LGPP Real
	  hgpp.ComputeHistogram(!isReal,isGGPP);//GGPP Imag
	  hgpp.ComputeHistogram(isReal,isGGPP);//GGPP Real
		

}



Mat FeatureExtractor::RetrieveOutputFeature(bool isSQI,bool isReal,bool isGGPP)
{
	if(isSQI){
	          return sqi.getOutImage();
	}
	else{
	  return hgpp.GetOutputHistogram(isReal,!isGGPP);
	}

}	



//misc function
string int2string(int num)
{
     stringstream ss;
     ss<<num;
     return ss.str();
}



