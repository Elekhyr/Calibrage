#include "Camera.h"
#include "Chessboard.h"

int main()
{
	Camera camera;
	Chessboard chessboard;

	try {
		camera.Init();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	int framesPerSecond = 20;

	cv::namedWindow("Webcam", CV_WINDOW_AUTOSIZE);

	while (camera.Capture())
	{
		cv::imshow("Webcam", camera.Snapshot());
		cv::waitKey(1);
	}
	return 0;
}