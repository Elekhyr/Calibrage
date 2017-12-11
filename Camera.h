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
	void SetProperties(const CameraProperties& properties);
    void Calibrate(const std::vector<cv::Mat> calibrationImages, Chessboard chessboard, cv::Size boardSize, float edgeLength, cv::Mat& distanceCoefficient);
	bool Capture();
	const cv::Mat& Snapshot();

private:
	cv::VideoCapture mCapture;
	cv::Mat mFrame;
	CameraProperties mProperties;
    cv::Mat cameraMatrix;
};

