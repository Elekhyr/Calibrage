#include "Chessboard.h"



Chessboard::Chessboard()
{
}


Chessboard::~Chessboard()
{
}

void Chessboard::SetProperties(const ChessboardProperties & properties)
{
}

std::vector<cv::Point2d> Chessboard::GetCorners(const cv::Mat & image)
{
	std::vector<cv::Point2d> corners;

	cv::findChessboardCorners(image, cv::Size(mProperties.nbRows, mProperties.nbCols), corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);

	return corners;
}

void Chessboard::DrawCorners(const std::vector<cv::Point2d>& corners, cv::Mat & image)
{
	cv::drawChessboardCorners(image, cv::Size(mProperties.nbCols, mProperties.nbRows), corners, !corners.empty());
}

void Chessboard::CreateKnownCorners()
{
	mCorners.reserve(mProperties.nbCols * mProperties.nbRows);
	for (unsigned i = 0; i < mProperties.nbRows; ++i)
	{
		for (unsigned j = 0; j < mProperties.nbCols; ++j)
		{
			mCorners.push_back(cv::Point3d(j * mProperties.squareLength, i * mProperties.squareLength, 0));
		}
	}
}

