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

static void media() {
	/* Media */
	vector<cv::Mat> images, fifteenImages, sevenImages;
	cout << endl;
	for (int i = 1; i <= 31; i++) {
		Mat image = imread("images/" + to_string(i - 1) + ".tif", CV_LOAD_IMAGE_GRAYSCALE);
		images.push_back(image);
	}
	for (int i = 1; i < 31; i++) {
		if (i % 2) {
			for (int j = 0; j < 2129; j++) {
				for (int k = 0; k < 2165; k++) {
					Scalar intensityLeft = images[i - 1].at<uchar>(j, k);
					Scalar intensityRight = images[i + 1].at<uchar>(j, k);
					Scalar intensityCenter = images[i].at<uchar>(j, k);
					Scalar intensity = ((intensityLeft / 2) + intensityCenter + (intensityRight / 2)) / 2;
					images[i].at<uchar>(j, k) = intensity.val[0];
						fifteenImages.push_back(images[i]);
					cout  << i << "/" << 31 << " & " << j << "/" << 2129 << " & " << k << "/" << 2165 << "\r";
				}
			}
		}
	}

	saveImages("images/media/fifteenImages", fifteenImages);

	for (int i = 4; i < 31; i+=5) {
			for (int j = 0; j < 2129; j++) {
				for (int k = 0; k < 2165; k++) {
					Scalar intensityLeft = images[i - 1].at<uchar>(j, k) + images[i - 2].at<uchar>(j, k)/2;
					Scalar intensityRight = images[i + 1].at<uchar>(j, k) + images[i + 2].at<uchar>(j, k)/2;
					Scalar intensityCenter = images[i].at<uchar>(j, k);
					Scalar intensity = (intensityLeft + intensityCenter + intensityRight) / 4;
					images[i].at<uchar>(j, k) = intensity.val[0];
					fifteenImages.push_back(images[i]);
					cout <<  i << "/" << 31 << " & " << j << "/" << 2129 << " & " << k << "/" << 2165 << "\r";
				}
			}
	}
	saveImages("images/media/sevenImages", sevenImages);
}

int main(int argc, char* argv[])
{
	decimazione();

	thread th1(media);
	//media();

	cout << endl;
	system("pause");
	return 0;
}