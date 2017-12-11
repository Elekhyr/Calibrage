#pragma once
#include <string>
#include <opencv2\opencv.hpp>

struct CameraProperties
{
	CameraProperties();
	~CameraProperties();

	void ReadFromFile(const std::string& path);
	void SaveToFile(const std::string& path) const ;

	// Internal parameters
	cv::Vec2d center; /// Camera origin
	double ratio_x; /// ratio pixels/length on the x axis
	double ratio_y; /// ratio pixels/length on the y axis

	// External parameters
	// Position and orientation of the camera relative to the scene

	cv::Vec3d translation; /// Translation matrix to make the camera origin match with the scene origin
	double rx, ry, rz; /// Rotation coefficients to align scene and camera axis
	
	double focalDist; /// Focal distance of the camera
};

