#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>


/** Global variables */
const cv::String face_cascade_name = "lbpcascade_frontalface_improved.xml";
const cv::String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
const std::string window_name = "Searching for your face...";
const cv::RNG rng(12345);


const double WAIT_TIME = 19000;

using FacesVec = std::vector<cv::Mat>;
class FacesCropped
{
	
public:
	FacesVec readfromWebCam(int num_of_images = 15);
	FacesVec fromFaceVec(FacesVec input);
	int numberOfFaces(cv::Mat input);

private:
	
	cv::CascadeClassifier m_face_cascade;
	cv::CascadeClassifier m_eyes_cascade;
	cv::Mat _cropOutFace(cv::Mat, bool draw=false);
	int initCascade();
	int initVideoCapture();
	void addCroppedFaceToVec(cv::Mat frame, std::vector<cv::Mat>& imgs, double elapsed = WAIT_TIME);
	cv::VideoCapture m_cap;

};

