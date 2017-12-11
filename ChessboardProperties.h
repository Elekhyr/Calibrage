#pragma once
#include <string>
#ifdef _WIN32
#include <opencv2\opencv.hpp>
#else
#include <opencv2/opencv.hpp>
#endif
struct ChessboardProperties
{
	ChessboardProperties();
	~ChessboardProperties();
	ChessboardProperties(const ChessboardProperties& rhs);
	const ChessboardProperties& operator=(const ChessboardProperties& rhs);

	void ReadFromFile(const std::string& path);
	void WriteToFile(const std::string& path);

	cv::Size dimension; /// dimension of the chessboard
	double squareLength; /// Length of the edge of a square

	double nbCols; /// Number of aruco in columns
	double nbRows; /// Number of aruco in rows
};

