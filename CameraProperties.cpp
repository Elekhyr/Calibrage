#include "CameraProperties.h"
#include "json.hpp"


using json = nlohmann::json;
CameraProperties::CameraProperties()
{
}


CameraProperties::~CameraProperties()
{
}

CameraProperties::CameraProperties(const CameraProperties & rhs)
{
	if (this != &rhs)
	{
		center = rhs.center;
		focalDist = rhs.focalDist;
		ratio_x = rhs.ratio_x;
		ratio_y = rhs.ratio_y;
		rx = rhs.rx;
		ry = rhs.ry;
		rz = rhs.rz;
		translation = rhs.translation;
	}
}

const CameraProperties & CameraProperties::operator=(const CameraProperties & rhs)
{
	if (this != &rhs)
	{
		center = rhs.center;
		focalDist = rhs.focalDist;
		ratio_x = rhs.ratio_x;
		ratio_y = rhs.ratio_y;
		rx = rhs.rx;
		ry = rhs.ry;
		rz = rhs.rz;
		translation = rhs.translation;
	}
	return *this;
}

void CameraProperties::ReadFromFile(const std::string & path)
{
	std::ifstream stream;
	stream.exceptions(std::fstream::badbit | std::fstream::failbit);
	json js;

	try {
		stream.open(path);
		stream >> js;
	}
	catch (std::exception& e) {
		std::cerr << "Exception" << e.what() << std::endl;
		return;
	}

	double x = js["x"];
	double y = js["y"];

	center = cv::Vec2d(x, y);
	ratio_x = js["ratio_x"];
	ratio_y = js["ratio_y"];
	
	double tx = js["tx"];
	double ty = js["ty"];
	double tz = js["tz"];
	translation = cv::Vec3d(tx, ty, tz);
	rx = js["rx"];
	ry = js["ry"];
	rz = js["rz"];

	focalDist = js["focalDist"];
}

void CameraProperties::SaveToFile(const std::string & path) const
{
	std::ofstream stream;
	stream.exceptions(std::fstream::badbit | std::fstream::failbit);
	json js;
	
	js["x"] = center[0];
	js["y"] = center[1];

	js["ratio_x"] = ratio_x;
	js["ratio_y"] = ratio_y;

	js["tx"] = translation[0];
	js["ty"] = translation[1];
	js["tz"] = translation[2];

	js["rx"] = rx;
	js["ry"] = ry;
	js["rz"] = rz;

	js["focalDist"] = focalDist;

	try {
		stream.open(path);
		stream << std::setw(4) << js << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception" << e.what() << std::endl;
		return;
	}
}
