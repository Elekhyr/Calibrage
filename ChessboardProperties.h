#pragma once
#include <string>
#include <opencv2\opencv.hpp>
struct ChessboardProperties
{
	ChessboardProperties();
	~ChessboardProperties();
	void ReadFromFile(const std::string& path);
	void WriteToFile(const std::string& path);

	cv::Size dimension; /// dimension of the chessboard
	double squareLength; /// Length of the edge of a square

	double nbCols; /// Number of aruco in columns
	double nbRows; /// Number of aruco in rows
};

