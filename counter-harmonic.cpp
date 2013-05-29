#include <iostream>
#include <string.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void couterHarmonic(Mat& src, Mat& dst, int kSize, float Q);

int main( int argc, char** argv )
{
    Mat src, dst;
    string windowOriginalImage = "Original";
    string windowResultImage = "Result";
    
    // setup dir and image file
    string image = "lungs s and p 50.jpg";
    string sourceDir = "/Users/rayron/Desktop/img/";
    string dstDir = "/Users/rayron/Desktop/processed/";
    
    // load image
    src = imread(sourceDir + image, 5 );
    
    // verify if the image is loaded
    if (src.data == 0) {
        cerr << "Image not found!" << endl;
        return -1;
    }
    
    cvtColor(src, dst, CV_BGR2GRAY);
    
    couterHarmonic(dst, dst, 3, -1.5f);
    
    imwrite(dstDir+image, dst);
    
    namedWindow( windowOriginalImage, CV_WINDOW_AUTOSIZE);
    namedWindow( windowResultImage, CV_WINDOW_AUTOSIZE);
    imshow( windowOriginalImage, src);
    imshow( windowResultImage, dst);
    waitKey();
}

void couterHarmonic(Mat& src, Mat& dst, int kSize, float Q){
    dst.create(src.size(), src.type());
    Mat _src;
    copyMakeBorder(src, _src, (kSize/2), (kSize/2), (kSize/2), (kSize/2), BORDER_REPLICATE);
    
    float val;
    for(int i = (kSize/2); i < _src.rows-(kSize/2); i++){
        for(int j = (kSize/2); j < _src.cols-(kSize/2); j++){
            
            float a = 0;
            float b = 0;

            for(int k = i-(kSize/2); k <= i+(kSize/2); k++){
                for(int w = j-(kSize/2); w <= j+(kSize/2); w++){
                    val = (float)_src.at<uchar>(k,w);
                    a += pow(val, (1.f + Q));
                    b += pow(val, Q);
                }
            }
            
            dst.at<uchar>(i-(kSize/2),j-(kSize/2)) = (a/b);
        }
    }
}
