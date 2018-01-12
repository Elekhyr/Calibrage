#pragma once
#ifdef _WIN32
#include <opencv2\opencv.hpp>
#else
#include <opencv2/opencv.hpp>
#endif
#include "CameraProperties.h"
#include "Chessboard.h"
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
    void Calibrate(const std::vector<cv::Mat>& calibrationImages, Chessboard chessboard);
	bool Capture();
	void corrige(const cv::Mat& imageTordue, cv::Mat& imageCorrige);
	const cv::Mat& Snapshot();

private:
	cv::VideoCapture mCapture;
	cv::Mat mFrame;
	CameraProperties mProperties;
    cv::Mat cameraMatrix;
	cv::Mat distCoefficients;
};

