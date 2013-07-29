#include "GaborPhasePatterns.h"
#include "headers.h"
#include "GaborFilter.h"
#include "FeatureExtractor.h"

//Method to compute the  local Gabor Phase Pattern(LGPP)
void GaborPhasePatterns::ComputeLGPP(bool isReal){


  Mat Quant;
  int sample[8][2]={{0,0},{0,1},{0,2},{1,2},{2,2},{2,1},{2,0},{1,0}};
  Rect rect0=cv::Rect(1,1,Resp[0].size().width-2,Resp[0].size().height-2);
  Rect rect;
  Mat temp;

	for(int p=0;p<scale*orient;p++)
	{
		Quant=Resp[p]<=0;
		Quant=Quant*(1.0/255);
      		Quant.copyTo(temp);
      		Mat out=Mat::zeros(Quant.size().height-2,Quant.size().width-2,CV_8UC1);

		for (int r=0;r<8;r++)
		{
            		rect=cv::Rect(sample[r][1],sample[r][0],Resp[0].size().width-2,Resp[0].size().height-2);
	    		cv::bitwise_xor(Quant(rect0),Quant(rect),temp);
            		cv::addWeighted(out,1,temp,pow(2,7-r),0,out);

            		if(isReal==true)
			{
	      			LGPP_r.push_back(out);
            		}
            		else
			{
	      			LGPP_i.push_back(out);
            		}
      		}

	      	temp.release();
      		Quant.release();
  	}

}

// Method to compute the Global Gabor Phase Patterns
void GaborPhasePatterns::ComputeGGPP(bool isReal)
{

  Mat Quant;

	for (int sc=0;sc<scale;sc++)
	{
		Quant=Resp[sc*orient]<=0;
      		Quant=Quant*(1.0/255);

      		Mat out=cv::Mat(Resp[0].size(),CV_8UC1);
      		(Quant).copyTo(out);

      		for(int ort=1;ort<orient;ort++)
		{
	   		Quant=Resp[sc*orient+ort]<=0;
	   		Quant=Quant*(1.0/255);

	  		cv::addWeighted(out,1,Quant,pow(2,ort),0,out);         	}

      			if(isReal==true)
			{
	  			GGPP_r.push_back(out);
          		}
      			else
			{
	  			GGPP_i.push_back(out);
  		        }
  		}
        	Quant.release();
}


// Interface method for returning the requested Gabor Phase Patterns
vector<cv::Mat> GaborPhasePatterns::GetGPP(bool isReal,bool isGGPP)
{
  if(isReal && isGGPP)
    {//return the real GGPP
      return GGPP_r;
    }
   else if(isReal && !isGGPP)
     {//return the real LGPP
       return LGPP_r;
     }
   else if(!isReal && isGGPP)
     {//return the imaginary GGPP
       return GGPP_i;
     }
   else
     {//return the imaginary LGPP
       return LGPP_i;
     }
}
