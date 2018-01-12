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

void Camera::Calibrate(const std::vector<cv::Mat>& calibrationImages, Chessboard chessboard, cv::Size boardSize, float edgeLength, cv::Mat& distanceCoefficients)
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
    distanceCoefficients = cv::Mat::zeros(8,1, CV_64F);
	cameraMatrix = cv::Mat::zeros(3, 3, CV_64F);
	
    cv::calibrateCamera(worldSpaceCorners, imageSpaceCorners, calibrationImages.front().size(), cameraMatrix, distanceCoefficients, rVectors, tVectors);
}

bool Camera::Capture()
{
	return mCapture.read(mFrame);
}

const cv::Mat & Camera::Snapshot()
{
	return mFrame;
}
