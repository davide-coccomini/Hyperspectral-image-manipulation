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



using namespace cv;
using namespace std;


struct wavelength {
	Mat image;
	int value;
};

void saveImages(string path, vector<wavelength> images) {
	for (int i = 0; i < images.size(); i++) {
		bool check = imwrite(path+"/"+ to_string(images[i].value) +".tif", images[i].image);
	}
}
void decimation() {
	/*Decimation*/

	vector<wavelength> fifteenImages, sevenImages;
	int baseWavelengthFifteen = 410;
	int baseWavelengthSeven = 430;
	for (int i = 1; i <= 31; i++) {
		if (i % 2 == 0) {
			Mat image = imread("images/" + to_string(i - 1) + ".tif", CV_LOAD_IMAGE_GRAYSCALE);
			wavelength w = {
				image,
				baseWavelengthFifteen
			};
			fifteenImages.push_back(w);
			baseWavelengthFifteen += 20;
		}
		if (i % 4 == 0) {
			Mat image = imread("images/" + to_string(i - 1) + ".tif", CV_LOAD_IMAGE_GRAYSCALE);
			wavelength w = {
				image,
				baseWavelengthSeven
			};
			sevenImages.push_back(w);
			baseWavelengthSeven += 40;
		}
	}
	saveImages("C:/images/decimazione/fifteen", fifteenImages);
	saveImages("C:/images/decimazione/seven", sevenImages);
}

static void average() {
	/* Average */
	vector<cv::Mat> images;
	vector<wavelength> fifteenImages, sevenImages;

	int baseWavelengthFifteen = 410;
	int baseWavelengthSeven = 430;

	for (int i = 1; i <= 31; i++) {
		Mat image = imread("images/" + to_string(i - 1) + ".tif", CV_LOAD_IMAGE_GRAYSCALE);
		images.push_back(image);
	}

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
		 wavelength w = {
			images[i],
			baseWavelengthFifteen
		 };
		 fifteenImages.push_back(w);
		 baseWavelengthFifteen += 20;
		}
	 cout << i << "/" << 29 <<  endl;
	}
	saveImages("C:/images/media/fifteen", fifteenImages);

	for (int i = 1; i <= 31; i++) {
		Mat image = imread("images/" + to_string(i - 1) + ".tif", CV_LOAD_IMAGE_GRAYSCALE);
		images.push_back(image);
	}


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
		wavelength w = {
			images[i],
			baseWavelengthSeven
		};
		sevenImages.push_back(w);
		baseWavelengthSeven += 40;
		cout << i << "/" << 27 << endl;
	}
	saveImages("C:/images/media/seven", sevenImages);
}

int main(int argc, char* argv[])
{
	decimation();
	average();
	system("pause");
	return 0;
}