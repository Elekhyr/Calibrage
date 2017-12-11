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

std::vector<cv::Vec2f> Chessboard::GetCorners(const cv::Mat & image)
{
	std::vector<cv::Vec2f> corners;

	mFound = cv::findChessboardCorners(image, cv::Size(4, 7), corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);

	return corners;
}

void Chessboard::DrawCorners(const std::vector<cv::Vec2f>& corners, cv::Mat & image)
{
	try
	{
		if (mFound)
			cv::drawChessboardCorners(image, cv::Size(4, 7), corners, mFound);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << "exception found" << std::endl;
	}
}

void Chessboard::CreateKnownCorners()
{
    mCorners.clear();
	mCorners.reserve(mProperties.nbCols * mProperties.nbRows);
	for (unsigned i = 0; i < mProperties.nbRows; ++i)
	{
		for (unsigned j = 0; j < mProperties.nbCols; ++j)
		{
			mCorners.push_back(cv::Vec2f(j * mProperties.squareLength, i * mProperties.squareLength));
		}
	}
}

