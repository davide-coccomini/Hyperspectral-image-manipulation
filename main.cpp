/* BANDE
https://docs.opencv.org/2.4/doc/user_guide/ug_mat.html 
*/


#include "pch.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream> 
#include <math.h>
#include <string>
#include <stdlib.h>  
#include <string> 
#include <thread> 




using namespace cv;
using namespace std;


void saveImages(string path, vector<cv::Mat> images) {
	for (int i = 0; i < images.size(); i++) {
		bool check = imwrite(path+"/"+ to_string(i)+".tif", images[i]);
	}
}
void decimazione() {
	/*Decimazione*/

	vector<cv::Mat> fifteenImages, sevenImages;
	for (int i = 1; i <= 31; i++) {
		if (i % 2 == 0) {
			Mat image = imread("images/" + to_string(i - 1) + ".tif", CV_LOAD_IMAGE_GRAYSCALE);
			fifteenImages.push_back(image);
		}
		if (i % 4 == 0) {
			Mat image = imread("images/" + to_string(i - 1) + ".tif", CV_LOAD_IMAGE_GRAYSCALE);
			sevenImages.push_back(image);
		}
	}
	saveImages("C:/images/decimazione/fifteen", fifteenImages);
	saveImages("C:/images/decimazione/seven", sevenImages);
}

static void media(int jump) {
	/* Media */
	vector<cv::Mat> images, fifteenImages, sevenImages;
	for (int i = 1; i <= 31; i++) {
		Mat image = imread("images/" + to_string(i - 1) + ".tif", CV_LOAD_IMAGE_GRAYSCALE);
		images.push_back(image);
	}
	cout << images.size() << endl;
	int rows = images[0].rows;
	int cols = images[0].cols;

	for (int i = 1; i < 30; i++) {
		if (i % 2 == 0 || i == 1) {
			for (int j = 0; j < rows; j++) {
				for (int k = 0; k < cols; k++) {
					Scalar intensityLeft = images[i - 1].at<uchar>(j, k);
					Scalar intensityRight = images[i + 1].at<uchar>(j, k);
					Scalar intensityCenter = images[i].at<uchar>(j, k);
					Scalar intensity = ((intensityLeft / 2) + intensityCenter + (intensityRight / 2)) / 2;
					images[i].at<uchar>(j, k) = intensity.val[0];
				}
			}
		 fifteenImages.push_back(images[i]);
		}
		cout << i << "/" << 31 <<  endl;
	}
	saveImages("C:/images/media/fifteen", fifteenImages);



	for (int i = 3; i < 29; i+=4) {
			for (int j = 0; j < rows; j++) {
				for (int k = 0; k < cols; k++) {
					Scalar intensityLeft = images[i - 1].at<uchar>(j, k) + images[i - 2].at<uchar>(j, k)/2;
					Scalar intensityRight = images[i + 1].at<uchar>(j, k) + images[i + 2].at<uchar>(j, k)/2;
					Scalar intensityCenter = images[i].at<uchar>(j, k);
					Scalar intensity = (intensityLeft + intensityCenter + intensityRight) / 4;
					images[i].at<uchar>(j, k) = intensity.val[0];
				}
			}
			sevenImages.push_back(images[i]);
			cout << i << "/" << 31 << endl;
	}
	saveImages("C:/images/media/seven", sevenImages);
}

int main(int argc, char* argv[])
{
	decimazione();

	media(1);

	//media();

	cout << endl;
	system("pause");
	return 0;
}