#include "headers.h"
#include "FeatureExtractor.h"


int main(int argc, char* argv[]) {

  Mat img;
  FeatureExtractor feat;


        cout<<"Setting Input Parameters...\n";

	// Set input Parameters for the various methods
	feat.SetParameter("scale","5");
	feat.SetParameter("orient","8");
        feat.SetParameter("NBINS","16");
        feat.SetParameter("size","9");
        feat.SetParameter("sigma","3.0");
        feat.SetParameter("IMSIZE","64");
        feat.SetParameter("FILTSIZE","65");
        feat.SetParameter("fmax",std::to_string(.5*pi));
        feat.SetParameter("sigma_g",std::to_string(2*pi));
	feat.SetParameter("region_size_x","8");
	feat.SetParameter("region_size_y","8");
	feat.SetParameter("overlap_x","4");
	feat.SetParameter("overlap_y","4");




	//feature extraction
	img = cv::imread("lena.png");	  // load image

	feat.DisplayImage(img);

 	feat.AddNewImage(img);// add image to extraction

        cout<<"Perform Feature Extraction...\n";

	// Extract Feature from image
	//In the simplest case this involves taking the self quotient image
       	feat.ExtractHGPPFeature();

	// save results
	// Method is definedto save either the Self-quotient image or the histograms of various  Gabor Phase Patterns
	bool isSQI=true,isReal=true,isGGPP=true;

	cout<<"Retrieve output feature"<<endl;
	Mat tmp=feat.RetrieveOutputFeature(!isSQI,isReal,!isGGPP);

	string str="outputFeatures.feat";
	FileStorage fs(str,FileStorage::WRITE);

        fs << "Feature" << tmp;
        fs.release(); // explicit close
        cout << "Output Write Done to " << str << endl;

	return 0;

}
