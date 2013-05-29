#include <iostream>
#include <string.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void equalizeHistogram(Mat& src, Mat& dst);

int main( int argc, char** argv )
{
    Mat src, dst;
    string windowOriginalImage = "Original";
    string windowResultImage = "Result";
    
    // setup dir and image file
    string image = "Google JAX low contrast.jpg";
    string sourceDir = "/Users/rayron/Desktop/img/";
    string dstDir = "/Users/rayron/Desktop/processed/";
    
    // load image
    src = imread(sourceDir + image, 5 );
    
    // verify if the image is loaded
    if (src.data == 0) {
        cerr << "Image not found!" << endl;
        return -1;
    }
    
    // equalize the image
    equalizeHistogram(src, dst);
    
    imwrite(dstDir+image, dst);
    
    namedWindow( windowOriginalImage, CV_WINDOW_AUTOSIZE);
    namedWindow( windowResultImage, CV_WINDOW_AUTOSIZE);
    imshow( windowOriginalImage, src);
    imshow( windowResultImage, dst);
    waitKey();
}

void equalizeHistogram(Mat& src, Mat& dst)
{
    // verify if has 3 channels
    if(src.channels() == 3 && src.type() == CV_8UC3){
        cvtColor(src, dst, CV_BGR2HLS);
    }else{
        cvtColor(src, dst, CV_BGR2GRAY);
    }
    
    dst = src.clone();
    
    const int hist_sz = 256;
    int hist[hist_sz];
    memset(hist, 0, sizeof(hist));
    
    int channel = src.channels()-1;
    
    // create an array of the number of pixels per intensity
    for( int y = 0; y < src.rows; y++ )
    {
        for( int x = 0; x < src.cols; x++ ){
            hist[src.at<Vec3b>(y,x)[channel]]++;
        }
    }
    
    // divide the range of intensity per number of pixels
    float scale = 255.f/(src.rows*src.cols);
    int sum = 0;
    uchar lut[hist_sz+1];
    
    for( int i = 0; i < hist_sz; i++ )
    {
        sum += hist[i];
        int val = cvRound(sum*scale);
        lut[i] = (uchar)(val);
    }
    
    lut[0] = 0;
    for( int y = 0; y < src.rows; y++ )
    {
        for( int x = 0; x < src.cols; x++ ){
            dst.at<Vec3b>(y,x)[0] = lut[src.at<Vec3b>(y,x)[0]];
            dst.at<Vec3b>(y,x)[1] = lut[src.at<Vec3b>(y,x)[1]];
            dst.at<Vec3b>(y,x)[2] = lut[src.at<Vec3b>(y,x)[2]];
        }
    }
    
}