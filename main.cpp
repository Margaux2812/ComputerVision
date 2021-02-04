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

Mat jpgToBinary(Mat img);
void morphology(Mat, Type, int givenPower);
void sobel(Mat);

int main(int argc, const char** argv){
	
	if(argc < 3) {
      std::cout << "You need to supply at least an image path and a parameter." << std::endl;
      return -1;
   	}

    std::string imgPath = argv[1];
    std::string param = argv[2];

    /*Check if the user put a power for the dilation or erosion*/
    int power = 1;
    if(argc == 4){
    	//Check if it is an integer indeed
    	if(std::stoi(argv[3]) > 0)
    		power = std::stoi(argv[3]);
    }

    /* load the image directly in grayscale thanks to the flag*/
    Mat img = imread(imgPath, IMREAD_GRAYSCALE);
	/*Handle error if the file wasn't found*/


    std::vector<std::string> parametersPossible {"sobel", "erosion", "dilation"};

    /*Check if the parameter is valid*/
    if(std::find(parametersPossible.begin(), parametersPossible.end(), param) == parametersPossible.end()){
      std::cout << "The parameter can be \"sobel\", \"erosion\" or \"dilation\"" << std::endl;
      return -1;
   	}

    if(!param.compare("sobel")){
    	
    	sobel(img);

    }else if(!param.compare("erosion")){

    	morphology(jpgToBinary(img), erosion, power);

    }else if(!param.compare("dilation")){

    	morphology(jpgToBinary(img), dilation, power);

    }else{

    	return 0;

    }

    return 0;

}


/*Convert image to binary image*/
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

/* EROSION & DILATION*/

void morphology(Mat binaryImg, Type type, int givenPower){

	Mat morphImg = Mat::zeros(binaryImg.size(), binaryImg.type());
	int power = 0;
	int sum;

	/*We do the action as many time as the user asked (the power parameter)*/
	while(power < givenPower){

		/*We will look at the pixel surrounding our pixel*/

	    for (int y = 0; y<binaryImg.rows-2; y++){
	    	for (int x = 0; x<binaryImg.cols-2; x++){

	    		sum = (int)binaryImg.at<uchar>(y+1,x)+(int)binaryImg.at<uchar>(y,x+1) + (int)binaryImg.at<uchar>(y+1,x+2) + (int)binaryImg.at<uchar>(y+2,x+1);

	    		/*In the case of erosion, we want to check if
	    		the pixels surrounding are all white, and if they
	    		are not, then we turn the actual pixel black, because
	    		it means we are on an edge*/
	    		if(sum == 4*255 && type == dilation){ 
	    			morphImg.at<uchar>(y,x) = 255;
	    		}else if(sum != 0 && type == erosion){
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

	    /*Count the power we are on to*/
	   	power++;

	   	/*Change the image we take as the reference for the futur occurences*/
	    binaryImg = morphImg;
	}

    // display the image
    std::string title = "Morphology Filter - ";
    if(type == dilation)
    	title += "Dilation";
    else
    	title += "Erosion";

    namedWindow(title, WINDOW_AUTOSIZE);
    imshow(title, morphImg);
    imwrite("image/binaryMorphology.jpg", morphImg);
    waitKey(0);
}

/*SOBEL FILTER FUNCTION*/
void sobel(Mat img){

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

			/*As the maximum RGB value possible is 255, we have to
			define it to 255 if the value is greater*/
			if (sum > 255){
				sum = 255;
			}

			sobelImg.at<uchar>(y,x) = sum;
    	}
    }
    
    // display the image
    namedWindow("Sobel Filter", WINDOW_AUTOSIZE);
    imshow("Sobel Filter", sobelImg);
    imwrite("image/sobel.jpg", sobelImg);
    waitKey(0);
}