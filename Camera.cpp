#include <exception>
#include "Camera.h"

Camera::Camera()
	: mCapture(0)
{
}


Camera::~Camera()
{
}

void Camera::Init()
{
	if (!mCapture.isOpened())
	{
//		throw std::exception("Can't open video capture");
        exit(-5);
	}
}

void Camera::SetProperties(const CameraProperties & properties)
{
	mProperties = properties;
}

void Camera::Calibrate(const std::vector<cv::Mat>& calibrationImages, Chessboard chessboard)
{
	
    std::vector<std::vector<cv::Vec2f>> imageSpaceCorners;
    std::vector<std::vector<cv::Vec3f>> worldSpaceCorners(1);
    for (cv::Mat image : calibrationImages) {
        imageSpaceCorners.push_back(chessboard.GetCorners(image));
    }
    chessboard.CreateKnownCorners();
	
	for (int i = 0; i < calibrationImages.size(); ++i){
		for (auto& p : chessboard.mCorners){
			worldSpaceCorners[i].emplace_back(p[0], p[1], 0.f);
		}
	}
	
    std::vector<cv::Mat> rVectors, tVectors;
	cameraMatrix = cv::Mat::zeros(3, 3, CV_64F);
	
	//D'après documentation distCoefficients vaut (k_1, k_2, p_1, p_2[, k_3[, k_4, k_5, k_6 [, s_1, s_2, s_3, s_4[, \tau_x, \tau_y]]]])
	cv::calibrateCamera(worldSpaceCorners, imageSpaceCorners, calibrationImages.front().size(), cameraMatrix, distCoefficients, rVectors, tVectors);//, CV_CALIB_RATIONAL_MODEL); à rajouter pour 14 valeurs sinon 5.

}

void Camera::corrige(const cv::Mat& imageTordue, cv::Mat& imageCorrige){
	
	cv::Mat tmp = cv::Mat::zeros(4, 1, CV_64F);
	tmp.at<double>(0,0) = distCoefficients.at<double>(0,0);
	tmp.at<double>(1,0) = distCoefficients.at<double>(1,0);
	tmp.at<double>(2,0) = distCoefficients.at<double>(4,0);
	tmp.at<double>(3,0) = distCoefficients.at<double>(5,0);
	
	//undistortImage veut que tmp vale (k_1, k_2, k_3, k_4)
	cv::fisheye::undistortImage(imageTordue, imageCorrige, cameraMatrix, tmp);
	
}

bool Camera::Capture()
{
	return mCapture.read(mFrame);
}

const cv::Mat & Camera::Snapshot()
{
	return mFrame;
}
