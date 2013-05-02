#ifndef CV_DOT_TEMPLATE
#define CV_DOT_TEMPLATE
#include <iostream>

#include <iostream>
#include <iostream>

#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <sstream>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/imgproc/imgproc.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <sstream>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/imgproc/imgproc.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write
using namespace std;
using namespace cv;

class DOT{

    Size regionDim;     //size of the region
    Size Samples;       //size of samples in horizontal and veritcal directions

public:
    DOT()
    {

        regionDim.width=7;
        regionDim.height=7;
    }

    void derivativeImage(Mat input,Mat &output)
    {

    Mat dx,dy;
    cv::GaussianBlur (input,input,Size(3,3),1);
        cv::Sobel (input,dx,CV_32F,1,0,3);
        cv::Sobel (input,dy,CV_32F,0,1,3);

        //caculating magnitude and orientation of each channel seperately
        Mat mag,ang;
        cv::cartToPolar (dx,dy,mag,ang,false);

        //
        //cv::imshow("mag",mag);
        //allocating matrices for derivative image

        Mat mag1,ang1;
        ang1=Mat(ang.rows,ang.cols,CV_32FC(1));
        mag1=Mat(mag.rows,mag.cols,CV_32FC(1));

        vector<Mat> ch1;




        for(int i=0;i<mag.rows;i++)
        {
            float *ptr=mag.ptr <float>(i);
            float *ptr1=ang.ptr <float>(i);
            for(int j=0;j<mag.cols;j++)
            {
                float max=ptr[j*3];
                float max1=ptr1[j*3];

                if(ptr[j*3+1]>max)
                {
                    max=ptr[j*3+1];
                    max1=ptr1[j*3+1];
                }
                if(ptr[j*3+2]>max)
                {
                    max=ptr[j*3+2];
                    max1=ptr1[j*3+2];

                }

                ptr1[j*3]=max1;
                ptr[j*3]=max;

            }
        }

        cv::split(mag,ch1);
        ch1[0].copyTo(output);


    }

    void createTemplate(Mat input)
    {

        Samples.width=input.cols/regionDim.width;
        Samples.height=input.rows/regionDim.height;

        // discretize
         const int SAMPLING_SIZE = regionDim.width;
         int offsetX = 1+SAMPLING_SIZE/2;
         int offsetY = 1+SAMPLING_SIZE/2;
//cerr << rowBinIndex <<":" << colBinIndex <<endl;
         //determine DOT for regions in the image
        for (int rowBinIndex = 0; rowBinIndex < Samples.height; ++rowBinIndex)
        {
          for (int colBinIndex = 0; colBinIndex < Samples.width; ++colBinIndex)
          {

              for (int rowPixelIndex = -SAMPLING_SIZE/2; rowPixelIndex <= SAMPLING_SIZE/2; rowPixelIndex += SAMPLING_SIZE/2)
                   {
                     const int yPosition = offsetY + rowPixelIndex;

                     for (int colPixelIndex = -SAMPLING_SIZE/2; colPixelIndex <= SAMPLING_SIZE/2; colPixelIndex += SAMPLING_SIZE/2)
                     {
                       const int xPosition = offsetX + colPixelIndex;
                       int counter = 0;



                       cerr << xPosition <<":" << yPosition <<":" << SAMPLING_SIZE <<endl;
                        }
                     cerr <<"********************** 1" <<endl;
              }
              cerr <<"********************** 2" <<endl;
             break;

              offsetX += SAMPLING_SIZE;

          }
          offsetY += SAMPLING_SIZE;
          offsetX = SAMPLING_SIZE/2+1;
          break;
    }


    }

    void process(Mat image)
    {
        //computing the number of regions along the horizontal and vertical directions

        Mat output;
        derivativeImage(image,output);
        createTemplate(output);

        //imshow("image",image);
        cv::normalize(output,output,0,1,CV_MINMAX);

        imshow("der",output);


    }


};






#endif