#ifndef GPP_H_
#define GPP_H_

#include "headers.h"



class GaborPhasePatterns{

public:

      // constructors/destructors
    	GaborPhasePatterns(int _scale=5,int _orient=8):scale(_scale),orient(_orient)
            {
	          vector <cv::Mat> LGPP_r, LGPP_i;
                  vector <cv::Mat> GGPP_r, GGPP_i;
		  vector <cv::Mat> Resp;
            }
	~GaborPhasePatterns()
            {
	      for (int p=0;p<LGPP_r.size();p++)
                  {
		      LGPP_r.pop_back();
		      LGPP_i.pop_back();
                  }
                  for (int p=0;p<GGPP_r.size();p++)
                  {
		      GGPP_r.pop_back();
		      GGPP_i.pop_back();
                  }

		  for(int p=0;p<Resp.size();p++)
		    {
		      Resp.pop_back();
		    }
	    }

      //Accesors/Interface methods
	void SetParameter(int _scale,int _orient)
            {
                  scale=_scale;
                  orient=_orient;
                  PrintParameters();
            }

      	void PrintParameters()const
            {
                   cout<< "\n\t For the Gabor Phase Patterns...."<<endl;
                   cout<< " \t\t The # of scales is set to %d"<<scale<<" and orientations to %d"<<orient<<endl;
            }

      	void setFilteredInput(vector <cv::Mat>Inp)
           {
		     Resp=Inp;
	   }

      	vector<cv::Mat> GetGPP(bool isReal,bool isGGPP);

      	//Computational methods
      	void ComputeLGPP(bool isReal);
      	void ComputeGGPP(bool isReal);


protected:

      	vector<cv::Mat> LGPP_r,LGPP_i;
      	vector<cv::Mat> GGPP_r,GGPP_i;
      	vector<cv::Mat> Resp; // the gabor filter response used as input to the ComputeLGPP/ComputeGGPP methods
      	int scale,orient;

};


class HGPP : public GaborPhasePatterns
{

  public:
      //constructors
	HGPP(int _reg_size_y=8,int _reg_size_x=8,int _overlap_y=4,int _overlap_x=4, int _NBINS=16,int _scale=5, int _orient=8): NBINS(_NBINS),GaborPhasePatterns(_scale,_orient)

      	{
                 reg_size[0]=_reg_size_y;
	         reg_size[1]=_reg_size_x;
                 overlap[0]=_overlap_y;
	         overlap[1]=_overlap_x;
		 NoLGPP=0;NoGGPP=0;
		 NoBl[0][0]=0;NoBl[0][1]=0;NoBl[1][1]=0;NoBl[1][0]=0;
                 Mat HistGPP[4];
      	}
	~HGPP()
      	{
        	for (int n=0;n<4;n++)
            	{
                	HistGPP[n].release();
	    	}
      	}


      	//Accesors
	void SetParameter(int _NBINS, int _reg_size[2],int _overlap[2])
        {
		NBINS=_NBINS;
                reg_size[0]=_reg_size[0];reg_size[1]=_reg_size[1];
               	overlap[0]=_overlap[0];overlap[1]=_overlap[1];
		NoLGPP=2*scale*orient;
		NoGGPP=2*scale;
		PrintParameters();
        }

	void PrintParameters() const
        {
                cout << "\n \t Parameters for the Histogram of Gabor Phase Patterns...."<<endl;
                cout << " \t\t The region size of image patch is set to {"<<reg_size[0]<<","<<reg_size[1]<<"} pixels"<< endl;
                cout << " \t\t The overlap between image patches is set to {"<<overlap[0]<<","<<overlap[1]<<"} pixels"<< endl;
                cout << " \t\t The # of bins per image patch for histogram computation is set to "<<NBINS<<endl;
        }


	void PrintHistogramStats()
        {
	        bool fl=true;
                cout << "\n\t The stats of the histogram feature are..."<<endl;
                cout << " \t\t There are %d"<<NoLGPP<<" frames of LGPP and %d"<<NoGGPP<<" frames of GGPP"<<endl;
                cout << " \t\t There are %d"<<ComputeNoBlocks(fl,!fl)<<" patches per LGPP frame and %d"<< ComputeNoBlocks(fl,fl)<<" patches per GGPP frame"<<endl;     
                cout << " \t\t Total Feature length is %d"<< 2*NBINS*(NoBl[0][0]*NoLGPP+NoBl[1][0]*NoGGPP)<<endl;
         }


         Mat GetOutputHistogram(bool isReal,bool isGGPP) const
         {
	 	return HistGPP[2*isGGPP+isReal];
         }

	 //Main Computation Method
	void ComputeHistogram(bool isReal,bool isGGPP);


  protected:
	Mat HistGPP[4];
      	int NBINS,reg_size[2],overlap[2];
      	int NoLGPP,NoGGPP;
      	int NoBl[2][2];
      	int ComputeNoBlocks(bool isReal,bool isGGPP);

};

#endif
