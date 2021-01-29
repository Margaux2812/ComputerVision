/*g++ main.cpp -o main -std=c++11 `pkg-config --cflags --libs opencv`

./main image/punto.jpg

*/
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;


enum Type {dilation, erosion};

void morph(Mat, Mat, Type);
Mat jpgToBinary(Mat img);
Mat morphology(Mat, Type);
bool isSurrounded(int x, int y);

int main(int argc, const char** argv){
	
    std::string imglo = argv[1];

    /* load the image directly in grayscale thanks to the flag*/
    Mat img = imread(imglo, IMREAD_GRAYSCALE);
    Mat sobelImg = Mat::zeros(img.size(), img.type());

    /*Asigning values to sobel x direction
		-1	0	1
		-2	0	2
		-1	0	1*/
    
	Mat sobel_x = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);

	/*Asigning values to sobel y direction
		-1	-2	-1
		0	0	0
		1	2	1*/
    
	Mat sobel_y = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);

    for (int y = 0; y<img.rows-2; y++){
    	for (int x = 0; x<img.cols-2; x++){
			int pixelValueX =
			(sobel_x.at<int>(0, 0) * (int)img.at<uchar>(y,x)) + (sobel_x.at<int>(0, 1) * (int)img.at<uchar>(y+1,x)) + (sobel_x.at<int>(0, 2) * (int)img.at<uchar>(y+2,x)) +
			(sobel_x.at<int>(1, 0) * (int)img.at<uchar>(y,x+1)) + (sobel_x.at<int>(1, 1) * (int)img.at<uchar>(y+1,x+1)) + (sobel_x.at<int>(1, 2) * (int)img.at<uchar>(y+2,x+1)) +
			(sobel_x.at<int>(2, 0) * (int)img.at<uchar>(y,x+2)) + (sobel_x.at<int>(2, 1) * (int)img.at<uchar>(y+1,x+2)) + (sobel_x.at<int>(2, 2) * (int)img.at<uchar>(y+2,x+2));         

			int pixelValueY =
			(sobel_y.at<int>(0, 0) * (int)sobelImg.at<uchar>(y,x)) + (sobel_y.at<int>(0, 1) * (int)sobelImg.at<uchar>(y+1,x)) + (sobel_y.at<int>(0, 2) * (int)sobelImg.at<uchar>(y+2,x)) +
			(sobel_y.at<int>(1, 0) * (int)sobelImg.at<uchar>(y,x+1)) + (sobel_y.at<int>(1, 1) * (int)sobelImg.at<uchar>(y+1,x+1)) + (sobel_y.at<int>(1, 2) * (int)sobelImg.at<uchar>(y+2,x+1)) +
			(sobel_y.at<int>(2, 0) * (int)sobelImg.at<uchar>(y,x+2)) + (sobel_y.at<int>(2, 1) * (int)sobelImg.at<uchar>(y+1,x+2)) + (sobel_y.at<int>(2, 2) * (int)sobelImg.at<uchar>(y+2,x+2));
	         
			int sum = abs(pixelValueX) + abs(pixelValueY);

			/*As the maximum RGB value possible is 255, we have to check*/
			if (sum > 255){
				sum = 255;
			}

			sobelImg.at<uchar>(y,x) = sum;
    	}
    }
    
    // display the images
    //namedWindow("Grayscale Image", WINDOW_AUTOSIZE);
    //namedWindow("Sobel Filter", WINDOW_AUTOSIZE);
    //imshow("Grayscale Image", img);
    //imshow("Sobel Filter", sobelImg);

    /*BINARY IMG*/
    Mat binaryImg = jpgToBinary(img);
    imshow("Binary Image", binaryImg);

    /*MORPH IMG*/
    Mat morphImg = morphology(binaryImg, erosion);
    imshow("morphology Image", morphImg);

    waitKey(0);

    return 0;

}

Mat jpgToBinary(Mat img){

	Mat binaryImg = Mat::zeros(img.size(), img.type());

	/*If the pixel  greater or equal to 100, 
	it will become white, 
	else it will be black*/

	for (int y = 0; y<img.rows-1; y++){
    	for (int x = 0; x<img.cols-1; x++){

    		if((int)img.at<uchar>(y,x) >= 100)
				binaryImg.at<uchar>(y,x) = 255;
			else
				binaryImg.at<uchar>(y,x) = 0;
    	}
    }

    return binaryImg;
}

/*bool isSurrounded(int x, int y, int width, int height){

	int top, int bottom, int left, int right;

	if(x==0){
		left = 0;
	}
	switch(x){
		//It doesn't have a left pixel
		case 0: left = 0;
		//It doesn't have a right pixel
		case width-1: right = 0;
		default:
	}
	int top = (int)binaryImg.at<uchar>(y-1,x);
	int bottom = (int)binaryImg.at<uchar>(y+1,x);
	int left = (int)binaryImg.at<uchar>(y,x-1);
	int right = (int)binaryImg.at<uchar>(y,x+1);
}

/* EROSION & DILATION*/

Mat morphology(Mat binaryImg, Type type){

	Mat morphImg = Mat::zeros(binaryImg.size(), binaryImg.type());
	bool needsToChange = false;
	int pixelSurroundingsSum;
	int amount = 0;
	int givenAmount = 1;

	/*We will look at the pixel surrounding our pixel
	and if it is black, we will expand/shrunk it*/

	while(amount < givenAmount){
	    for (int y = 0; y<binaryImg.rows-2; y++){
	    	for (int x = 0; x<binaryImg.cols-2; x++){

	    		int sum = (int)binaryImg.at<uchar>(y+1,x)+(int)binaryImg.at<uchar>(y,x+1) + (int)binaryImg.at<uchar>(y+1,x+2) + (int)binaryImg.at<uchar>(y+2,x+1);

	    		/*In the case of erosion, we want to check if
	    		the pixels surrounding are all white, and if they
	    		are not, then we turn the actual pixel black, because
	    		it means we are on an edge*/
	    		if(sum == 4*255 && type == erosion){ 
	    			morphImg.at<uchar>(y,x) = 255;
	    		}else if(sum != 0 && type == dilation){
	    		/*In the case of dilation, we want to check if
	    		at least one of the pixels surrounding is white, and if
	    		there is, then we turn the actual pixel white, because
	    		it means we are on an edge and are expanding it*/

	    			morphImg.at<uchar>(y,x) = 255;
	    		}else{
	    			morphImg.at<uchar>(y,x) = 0;
	    		}
	    		
	    	}
	    }

	   amount++;

	    binaryImg = morphImg;
	}

    return morphImg;
}

/* grayscale image, binary mask
void morph(Mat inImage, Mat outImage, kernel, Type type) {
 	// half size of the kernel, kernel size is n*n (easier if n is odd)
 	sz = (kernel.n - 1 ) / 2;

	for X in inImage.rows {
	for Y in inImage.cols {

	if ( isOnBoundary(X,Y, inImage, sz) ) {
	// check if pixel (X,Y) for boundary cases and deal with it (copy pixel as is)
	// must consider half size of the kernel
	val = inImage(X,Y);       // quick fix
	}

	else {
	list = [];

	// get the neighborhood of this pixel (X,Y)
	for I in kernel.n {
	for J in kernel.n {
	if ( kernel(I,J) == 1 ) {
	list.add( inImage(X+I-sz, Y+J-sz) );
	}
	}
	}

	if type == dilation {
	// dilation: set to one if any 1 is present, zero otherwise
	val = max(list);
	} else if type == erosion {
	// erosion: set to zero if any 0 is present, one otherwise
	val = min(list);
	}
	}

	// set output image pixel
	outImage(X,Y) = val;
	}
	}
}*/