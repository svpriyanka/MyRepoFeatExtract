#include "headers.h"
#include "GaborFilter.h"


// Method to compute the coffecients of the Gabor Filter given the number of scales, orientation, frequency and 
//\sigma: the spatial aspect ratio

void GaborFilter::ComputeFilter(){

int idx[]={0,0,0};
float kv,temp,sig,mag,phi,temp2,temp3;
int i,j,u,v;

	ResetStructures();

	int size_y=int(.5*float(FILTSIZ-1));
	int size_x=int(.5*float(FILTSIZ-1));

	for ( v=0;v<scale;v++)
    	{
        	kv=fmax/pow(2,(float(v)*.5));
        	temp=kv*kv/(sigma_g*sigma_g);

	        for ( u=0;u<orient;u++)
        	{
            		phi=float(u)*pi/8;
	    		for (i = -1*size_y; i <=size_y ; i++)
	      		{
				for ( j = -1*size_x; j <=size_x ; j++)
		  		{
		    			mag=pow(float(i),2) + pow(float(j),2);
		    			temp2=temp*exp(-1*.5*mag*temp);
		    			temp3=(kv*cos(phi)*j) + (kv*sin(phi)*i);
		    			idx[0]=i+size_y; idx[1]=j+size_x;idx[2]=orient*(v)+u;
		    			GaborFilt_i[idx[2]].at<float>(idx[0],idx[1])=temp2*(sin(temp3));
	    	    			GaborFilt_r[idx[2]].at<float>(idx[0],idx[1])=temp2*(cos(temp3)-exp(-1*.5*sigma_g*sigma_g));
				}
	      		}
		}
    	}



}

// Method to compute the response to the input image of the Gabor Filters computed using the method GaborFilter::ComputeFilters
void GaborFilter::ComputeFilterResponse(cv::Mat _inp_image)
{


	_inp_image.copyTo(inp_img);

    	Point N=cv::Point(IMSIZ+2*FILTSIZ-2,IMSIZ+2*FILTSIZ-2);
	Rect rect=cv::Rect(FILTSIZ-1,FILTSIZ-1,IMSIZ,IMSIZ);
    	Mat inp_large=cv::Mat(IMSIZ+2*FILTSIZ-2,IMSIZ+2*FILTSIZ-2,CV_32FC1);
	//	copyMakeBorder(inp_img,inp_large,FILTSIZ-1,FILTSIZ-1,FILTSIZ-1,FILTSIZ-1,BORDER_CONSTANT,cvScalar(0));
    	cv::Mat out_large=cv::Mat(N.y,N.x,CV_32FC1);
    	cv::Point anch=cv::Point(-1,-1);

	Mat tmp=cv::Mat(100,100,CV_32FC1);
	resize(inp_img,tmp,tmp.size(),0,0,INTER_LINEAR);

	for (int p=0;p<scale*orient;p++)
	{

	        cv::filter2D(inp_large,out_large,-1,GaborFilt_r[p],anch);
        	(out_large(rect)).copyTo(FiltResp_r[p]);

        	cv::filter2D(inp_large,out_large,-1,GaborFilt_i[p],anch);
        	(out_large(rect)).copyTo(FiltResp_i[p]);
  	}

    	out_large.release();
    	inp_large.release();
 }


// Interface Method to retrieve the filtered output
vector<cv::Mat> GaborFilter::GetFilterOutput(bool isReal) const
{

   	if(isReal==true)
	{
        	return FiltResp_r;
     	}
     	else
	{
        	return FiltResp_i;
      	}
}


// Method to set paramters to the GaborFilter class
void GaborFilter::SetParameter(string name, string value) {

         CV_FUNCNAME( "HGPP::SetParameter");

	// check parameters

	 if(name.compare("scale")==0)
	{
		scale=atoi(value.c_str());
	}
	else if(name.compare("orient")==0)
	{
		orient=atoi(value.c_str());
	}
	else if(name.compare("IMSIZ")==0)
	{
		IMSIZ=atoi(value.c_str());
	}
	else if(name.compare("FILTSIZ")==0)
	{
		FILTSIZ=atoi(value.c_str());
	}
	else if(name.compare("sigma_g")==0)
	{
		sigma_g=atof(value.c_str());
	}
	else if(name.compare("fmax")==0)
	{
	       fmax=atof(value.c_str());
	}
	else {
		printf("Parameter '%s' invalid\n", name.c_str());
		exit(2);
	}

}

// Method to reset the input and output structures  upon change of parameters
//Note: This does not recompute the filters/the filter-responses

void  GaborFilter::ResetStructures()
{
  int po=GaborFilt_r.size();

	if(po<scale*orient)
	{
      		for(int p=po;p<scale*orient;p++)
		{
	  		GaborFilt_r.push_back(cv::Mat(FILTSIZ,FILTSIZ,CV_32FC1));
	  		GaborFilt_i.push_back(cv::Mat(FILTSIZ,FILTSIZ,CV_32FC1));
	  		FiltResp_r.push_back(cv::Mat(IMSIZ,IMSIZ,CV_32FC1));
	  		FiltResp_i.push_back(cv::Mat(IMSIZ,IMSIZ,CV_32FC1));
		}
    	}
  	else
    	{
      		for (int p=scale*orient;p<po;p++)
      		{
	  		GaborFilt_r.pop_back();
	  		GaborFilt_i.pop_back();
	  		FiltResp_r.pop_back();
	  		FiltResp_i.pop_back();
		}
    	}
}
