#pragma once
#ifdef _WIN32
#include <opencv2\opencv.hpp>
#else
#include <opencv2/opencv.hpp>
#endif
#include "CameraProperties.h"
class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	const CameraProperties& _Properties() const
	{
		return mProperties;
	}
	void SetProperties(const CameraProperties& properties);
	void Calibrate();
	bool Capture();

	const cv::Mat& Snapshot();

private:
	cv::VideoCapture mCapture;

	cv::Mat mFrame;
	CameraProperties mProperties;
};

