#include "headers.h"
#include "GaborPhasePatterns.h"

// Compute histogram of gabor phase patterns 
void HGPP::ComputeHistogram(bool isReal,bool isGGPP)
{
        vector<cv::Mat> GPP=GetGPP(isReal,isGGPP);
        Rect rect,rect_h;
        int _nframes=.5*(isGGPP*NoGGPP + (1-isGGPP)*NoLGPP);


        Mat temp,s_tmp,hist;

        Mat Hist=cv::Mat(NBINS*ComputeNoBlocks(isReal,isGGPP),_nframes,CV_32FC1);
	int chn[]={0};
	float minMax[2]={0.0,256.0};
	const float *ranges[]={minMax};

        for (int n=0;n<_nframes;n++)
        {
		NoBl[isGGPP][isReal]=0;
            	GPP[n].copyTo(temp);
            	for (int r=0;r<GPP[n].size().height && r+reg_size[0]-1<GPP[n].size().height;r=r+reg_size[0]-overlap[0])
            	{
                	for (int c=0;c<GPP[n].size().width && c+reg_size[1]-1<GPP[n].size().width;c=c+reg_size[1]-overlap[1])
                    	{
		      		rect=cv::Rect(c,r,reg_size[1],reg_size[0]);
		      		temp(rect).copyTo(s_tmp);
		      		rect_h=cv::Rect(n,NoBl[isGGPP][isReal],1,NBINS);
		      		cv::calcHist(&s_tmp,1,chn,Mat(),hist,1,&NBINS,ranges,true,false);
		      		hist.copyTo(Hist(rect_h));
		      		NoBl[isGGPP][isReal]=NoBl[isGGPP][isReal]+NBINS;
                    	}
                }
	}

	Hist.copyTo(HistGPP[2*isGGPP+isReal]);//translates to code 0 LGPP Real, 1 LGPP Im, 2 GGPP Real, 3 GGPP Im

        //release data structures from memeory
	Hist.release();
	temp.release();
	hist.release();
	s_tmp.release();
	for(int n=0;n<_nframes;n++)
	{
		GPP[n].release();
	}
}


// Compute number of image patches in a Gabor Phase Patterns
int HGPP::ComputeNoBlocks(bool isReal,bool isGGPP)
{

        vector<cv::Mat> GPP=GetGPP(isReal,isGGPP);
        int blk=0;

	for (int r=0;r<GPP[0].size().height && r+reg_size[0]-1<GPP[0].size().height;r=r+reg_size[0]-overlap[0])
	{
		for (int c=0;c<GPP[0].size().height && c+reg_size[0]-1<GPP[0].size().height;c=c+reg_size[0]-overlap[0])
		{
                	blk++;
                }
	}

        return blk;
}




