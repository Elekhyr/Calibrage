#pragma once
#include "ChessboardProperties.h"
#include <vector>
#ifdef _WIN32
#include <opencv2\opencv.hpp>
#else
#include <opencv2/opencv.hpp>
#endif
class Chessboard
{
public:
	Chessboard();
	~Chessboard();

	void SetProperties(const ChessboardProperties& properties);
	std::vector<cv::Vec2f> GetCorners(const cv::Mat& image);
	void DrawCorners(const std::vector<cv::Vec2f>& corners, cv::Mat& image);
private:
	ChessboardProperties mProperties;
	std::vector<cv::Vec2f> mCorners;
	bool mFound;
	void CreateKnownCorners();
};

