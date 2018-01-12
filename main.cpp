#include "Camera.h"
#include "Chessboard.h"
#include "ChessboardProperties.h"

int main()
{
	Camera camera;
	Chessboard chessboard;
	ChessboardProperties cp;
	cp.ReadFromFile("/Users/lois/Documents/M2/TIV3D/AnalyseImage-TP2/chessboard.json");
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
	
	std::vector<cv::Mat> ims(1);
	ims[0] = cv::imread("/Users/lois/Documents/M2/TIV3D/fish8.jpg", CV_LOAD_IMAGE_COLOR);
	
	cv::Mat out;
	camera.Calibrate(ims, chessboard);
	camera.corrige(ims[0], out);
	
	int framesPerSecond = 20;

	cv::namedWindow("Webcam", CV_WINDOW_AUTOSIZE);

	while (camera.Capture())
	{
		cv::Mat mat; 
		auto vec = chessboard.GetCorners(camera.Snapshot());

		camera.Snapshot().copyTo(mat);

		chessboard.DrawCorners(vec, mat);
		cv::imshow("Webcam", out);
		if (cv::waitKey(1) == 27)
			break;
	}
	return 0;
}
