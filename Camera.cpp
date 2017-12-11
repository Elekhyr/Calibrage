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

void Camera::Calibrate(const std::vector<cv::Mat> calibrationImages, Chessboard chessboard, cv::Size boardSize, float edgeLength, cv::Mat& distanceCoefficients)
{
    std::vector<std::vector<cv::Vec2f>> imageSpaceCorners;
    std::vector<std::vector<cv::Vec2f>> worldSpaceCorners(1);
    for (cv::Mat image : calibrationImages) {
        imageSpaceCorners.push_back(chessboard.GetCorners(image));
    }
    chessboard.CreateKnownCorners();
    worldSpaceCorners[0] = chessboard.mCorners;
    std::vector<cv::Mat> rVectors, tVectors;
    distanceCoefficients = cv::Mat::zeros(8,1, CV_64F);
    cv::calibrateCamera(worldSpaceCorners, imageSpaceCorners, boardSize, cameraMatrix, distanceCoefficients, rVectors, tVectors);
}

bool Camera::Capture()
{
	return mCapture.read(mFrame);
}

const cv::Mat & Camera::Snapshot()
{
	return mFrame;
}
