#pragma once
#include <opencv2\opencv.hpp>
#include "CameraProperties.h"
class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void SetProperties(const CameraProperties& properties);
	void Calibrate();
	bool Capture();

	const cv::Mat& Snapshot();

private:
	cv::VideoCapture mCapture;

	cv::Mat mFrame;
	CameraProperties mProperties;
};
