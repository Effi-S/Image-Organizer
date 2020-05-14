#include "opencv2/face.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MyUtils.h"
#include <locale>
#pragma once

const std::string FACES_DIR = "FaceDetection/faces";
const std::string YML = "FaceDetection/trained_model.yml";
const std::string CSV = "FaceDetection/training_data.csv";
const std::string USER_LABELS = "FaceDetection/user_labels.csv";
const wchar_t separator = ';';  ///< seperator in csv file


class FaceDetector
{	 
public:
	static FaceDetector loadFromYAML(const std::string& yml = YML) {
		return std::move(FaceDetector(yml));  // retrain model from scratch
	}
	static FaceDetector creatNew(const std::string& csv = CSV, const std::string &faces=FACES_DIR ) {
		return std::move(FaceDetector(csv, faces)); ///< Load from csv and faces dir and save to saveTo (yml file).
	}
		
	void addTrainingSet(std::vector<cv::Mat> images, std::wstring label, std::string=FACES_DIR);
	
	std::vector<std::wstring> searchFor(std::wstring label, bool draw=false);

	void save(const std::string yml = YML);

	~FaceDetector() = default;

private:


	FaceDetector(const std::string& yml);   ///< load model from yml
	FaceDetector(const std::string& csv, const std::string& imgs_dir);  ///< create new from csv and directory with images


	void read_csv(std::vector<cv::Mat>& images, std::vector<int>& labels);
	
	
	std::unordered_map<std::wstring, int> _getUserLabelMap(); ///< because LBPH is implemented with integer labels and string labels are simpler.

	std::unordered_map<std::wstring, int> m_userLabels = _getUserLabelMap();

	void addUserLabel(const std::wstring&);

	cv::Ptr<cv::face::LBPHFaceRecognizer> m_model = cv::face::LBPHFaceRecognizer::create();
	
	const std::string m_training_labels_csv;

};

