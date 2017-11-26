#pragma once
#include "ChessboardProperties.h"
#include <vector>
#include <opencv2\opencv.hpp>
class Chessboard
{
public:
	Chessboard();
	~Chessboard();

	void SetProperties(const ChessboardProperties& properties);
	std::vector<cv::Point2d> GetCorners(const cv::Mat& image);
	void DrawCorners(const std::vector<cv::Point2d>& corners, cv::Mat& image);
private:
	ChessboardProperties mProperties;
	std::vector<cv::Point3d> mCorners;

	void CreateKnownCorners();
};

