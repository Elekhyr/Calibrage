#include <iostream>
#include <fstream>

#include "ChessboardProperties.h"
#include "json.hpp"

using json = nlohmann::json;
ChessboardProperties::ChessboardProperties()
{
}


ChessboardProperties::~ChessboardProperties()
{
}

ChessboardProperties::ChessboardProperties(const ChessboardProperties & rhs)
{
	if (this != &rhs)
	{
		dimension = rhs.dimension;
		nbCols = rhs.nbCols;
		nbRows = rhs.nbRows;
		squareLength = rhs.squareLength;
	}
}

const ChessboardProperties & ChessboardProperties::operator=(const ChessboardProperties & rhs)
{
	if (this != &rhs)
	{
		dimension = rhs.dimension;
		nbCols = rhs.nbCols;
		nbRows = rhs.nbRows;
		squareLength = rhs.squareLength;
	}
	return *this;
}

void ChessboardProperties::ReadFromFile(const std::string & path)
{
	std::ifstream stream;
	stream.exceptions(std::fstream::badbit | std::fstream::failbit);
	json js;

	try {
		stream.open(path);
		stream >> js;
	}
	catch (std::exception& e){
		std::cerr << "Exception" << e.what() << std::endl;
		return;
	}

	dimension = cv::Size(js["height"], js["width"]);
	squareLength = js["squareLength"];
	nbCols = js["nbCols"];
	nbRows = js["nbRows"];

}

void ChessboardProperties::WriteToFile(const std::string & path)
{
	std::ofstream stream;
	stream.exceptions(std::fstream::badbit | std::fstream::failbit);
	json js;

	js["height"] = dimension.height;
	js["width"] = dimension.width;
	js["squareLength"] = squareLength;
	js["nbCols"] = nbCols;
	js["nbRows"] = nbRows;

	try {
		stream.open(path);
		stream << std::setw(4) << js << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception" << e.what() << std::endl;
	}
}
