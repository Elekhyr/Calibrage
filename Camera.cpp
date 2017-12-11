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

void Camera::Calibrate()
{
}

bool Camera::Capture()
{
	return mCapture.read(mFrame);
}

const cv::Mat & Camera::Snapshot()
{
	return mFrame;
}
