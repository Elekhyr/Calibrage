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
	
	std::vector<cv::Mat> ims(1);
	ims[0] = cv::imread("/Users/lois/Documents/M2/TIV3D/fish8.jpg");//Choisir image de calibration ici
	cv::Mat imIn = cv::imread("/Users/lois/Documents/M2/TIV3D/fish8.jpg");//Choisir image à corriger ici
	
	cv::Mat out;
	camera.Calibrate(ims, chessboard);
	camera.corrige(imIn, out);
	
	int framesPerSecond = 20;

	cv::namedWindow("Webcam", CV_WINDOW_AUTOSIZE);

	while (1)//camera.Capture())
	{
		cv::Mat mat; 
		//auto vec = chessboard.GetCorners(camera.Snapshot());

		//camera.Snapshot().copyTo(mat);

		//chessboard.DrawCorners(vec, mat);
		cv::imshow("Webcam", out);
		if (cv::waitKey(1) == 27)
			break;
	}
	return 0;
}
