#include "Camera.h"
#include "Chessboard.h"
#include "ChessboardProperties.h"

int main()
{
	Camera camera;
	
	Chessboard chessboard;
	ChessboardProperties cp;
	cp.ReadFromFile("chessboard.json");
	chessboard.SetProperties(cp);

	camera._Properties().SaveToFile("camera.json");

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
		cv::Mat mat; 
		auto vec = chessboard.GetCorners(camera.Snapshot());

		camera.Snapshot().copyTo(mat);

		chessboard.DrawCorners(vec, mat);
		cv::imshow("Webcam", mat);
		if (cv::waitKey(1) == 27)
			break;
	}
	return 0;
}