#include "FacesCropped.h"




cv::Mat FacesCropped::_cropOutFace(cv::Mat frame, bool draw)
{
    const int DESIRED_SIZE = 400; // size of face image 
    std::vector<cv::Rect> faces;
    std::vector<cv::Rect> eyes;
    cv::Mat frame_gray; // gray image

    //-- 1. convert to gray and equalize 
    cvtColor(frame, frame_gray, cv::COLOR_BGRA2GRAY);
    equalizeHist(frame_gray, frame_gray);


    //-- 2. Detect face
    m_face_cascade.detectMultiScale(frame_gray, faces, 1.1, 4, 0 | cv::CASCADE_SCALE_IMAGE);

    if (faces.size() != 1) {
        cv::imshow(window_name, frame);
        return cv::Mat(); // only 1 face at a time
    }
    auto& face = faces[0];

    if (draw) {
        //-- 2.1 show bounding rectangle of face found 
            auto fr2 = frame.clone();
            cv::rectangle(fr2, face, cv::CAP_ANY);
            cv::imshow(window_name, fr2);
    }
    
    //-- 3. Detect eyes in face 
    cv::Mat faceROI = frame_gray(face);

    m_eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE);

    if (eyes.size() != 2)
        return cv::Mat();  // false positive or missed an eye.

    cv::Rect& eye_l_rect = eyes[0];

    cv::Rect& eye_r_rect = eyes[1];

    if (eye_l_rect.x > eye_r_rect.x)  // determine left and right eye.
        std::swap(eye_l_rect, eye_r_rect);

    //-- 4. get center point of eyes
    cv::Point2f eye_l_center(face.x + eye_l_rect.x + eye_l_rect.width * 0.5f, face.y + eye_l_rect.y + eye_l_rect.height * 0.5f);
    cv::Point2f eye_r_center(face.x + eye_r_rect.x + eye_r_rect.width * 0.5f, face.y + eye_r_rect.y + eye_r_rect.height * 0.5f);
    cv::Point2f eyes_center = cv::Point2f((eye_l_center.x + eye_r_center.x) * 0.5f, (eye_l_center.y + eye_r_center.y) * 0.5f);
    cv::line(frame, eyes_center, eye_r_center, cv::Scalar());
    ///--5 align by the eyes
    //-- 5.1 Get the angle between the 2 eyes.
    double dy = (eye_r_center.y - eye_l_center.y);
    double dx = (eye_r_center.x - eye_l_center.x);
    double len = sqrt(dx * dx + dy * dy);
    double angle = atan2(dy, dx) * 180.0 / CV_PI; // Convert from radians to degrees.

    //-- 5.2  create rotation matrix using the angle from 5.1
    cv::Mat rot = cv::getRotationMatrix2D(eyes_center, angle, 1.0);

    //-- 6. Cropping out face 
    int width = face.width * 2;
    int height = face.height * 2;

    cv::Mat dst_image = cv::Mat(width, height, CV_8U, cv::Scalar(128)); // create a gray image the size we want.

    //-- 7. Shift the center of to be the desired center between the eyes.
    rot.at<double>(0, 2) += width * 0.5f - eyes_center.x;
    rot.at<double>(1, 2) += height * 0.4f - eyes_center.y;

    cv::warpAffine(frame, dst_image, rot, dst_image.size());  // warping frame into dst_image.
    return dst_image;
}
void FacesCropped::addCroppedFaceToVec(cv::Mat frame, std::vector<cv::Mat>& cropped_faces, double elapsed) 
{
   
    if (elapsed < WAIT_TIME)return;
    auto dst_img = _cropOutFace(frame);
    if(!dst_img.empty())
        cropped_faces.push_back(dst_img);

}

FacesVec FacesCropped::readfromWebCam(int num_of_images)
{
    
	// 1. initialize cascades and video capture.
	FacesVec cropped_faces;

	if (initCascade() < 0)
        return cropped_faces; 
    if(initVideoCapture() < 0)
        return cropped_faces;
		
		//-- 2. add cropped faces from the video stream
		cv::Mat frame;
        std::clock_t start(std::clock());
		while (cropped_faces.size() < num_of_images)
		{
			m_cap.read(frame);
			if (frame.empty())continue;
			
			//-- 3. add cropped and aligned image to vector
			addCroppedFaceToVec(frame, cropped_faces, double(std::clock()) - start);

			if (cv::waitKey(5) >= 0)
				break;
		}

        //-- creating local files TODO: remove this!!
		int num = 1;
		for (auto& it : cropped_faces)
			cv::imwrite(std::to_string(num++) + ".png", it.clone());
        //-----


        cv::imshow("The Face Found:", cropped_faces.begin()->clone());
        cv::waitKey(10);


	return cropped_faces;
}

FacesVec FacesCropped::fromFaceVec(FacesVec input)
{
    FacesVec retVec;
    for (auto& img : input)
        retVec.push_back(_cropOutFace(img));
    return retVec;
}

int FacesCropped::numberOfFaces(cv::Mat input)
{
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray; // gray image
    
    //-- 1. initialize cascades.

    if (initCascade() < 0)
    return 0;

    //-- 2. convert to gray and equalize 
    cvtColor(input, frame_gray, cv::COLOR_BGRA2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //-- 3. Detect faces and return how many found.
    m_face_cascade.detectMultiScale(frame_gray, faces, 1.1, 4, 0 | cv::CASCADE_SCALE_IMAGE);

    return int(faces.size()); 
}

int FacesCropped::initCascade()
{
	if (!m_face_cascade.load(face_cascade_name)) { std::cerr << "--(!)Error loading faces\n";return -1; };
	if (!m_eyes_cascade.load(eyes_cascade_name)) { std::cerr << "--(!)Error loading eyes\n"; return -1;};
    
	return 1;
}

int FacesCropped::initVideoCapture()
{
	//--- INITIALIZE VIDEOCAPTURE

	int deviceID = 0;             // 0 = open default camera
	int apiID = cv::CAP_ANY;      // 0 = autodetect default API

								  // open selected camera using selected API
	m_cap.open(deviceID, apiID);
	// check if we succeeded
	if (!m_cap.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return -1;
	}
	return 1;
}
