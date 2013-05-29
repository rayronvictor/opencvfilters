#include <iostream>
#include <string.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void median(Mat& src, Mat& dst, int kSize);

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
        cerr << "Imagem não encontrada!" << endl;
        return -1;
    }
    
    cvtColor(src, dst, CV_BGR2GRAY);
    
    // median filter
    median(dst, dst, 5);
    
    imwrite(dstDir+image, dst);
    
    namedWindow( windowOriginalImage, CV_WINDOW_AUTOSIZE);
    namedWindow( windowResultImage, CV_WINDOW_AUTOSIZE);
    imshow( windowOriginalImage, src);
    imshow( windowResultImage, dst);
    waitKey();
}

void median(Mat& src, Mat& dst, int kSize){
    
    Mat _src;
    // creates a border around the source image to not have to verify conditions near the edge of the original image
    copyMakeBorder(src, _src, (kSize/2), (kSize/2), (kSize/2), (kSize/2), BORDER_REPLICATE);
    
    for(int i = (kSize/2); i < _src.rows-(kSize/2); i++){
        for(int j = (kSize/2); j < _src.cols-(kSize/2); j++){
            
            vector<uchar> pixels;
            
            for(int k = i-(kSize/2); k <= i+(kSize/2); k++){
                for(int w = j-(kSize/2); w <= j+(kSize/2); w++){
                    pixels.push_back(_src.at<uchar>(k,w));
                }
            }
            
            // sort the pixels of the window filter
            sort(pixels.begin(), pixels.end());
            
            // takes the middle
            dst.at<uchar>(i-(kSize/2),j-(kSize/2)) = pixels.at((kSize*kSize)/2);
        }
    }
    
    
}