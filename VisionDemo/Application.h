#pragma once
#include <string>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

class Application
{
// Properties
private:
	std::string imageLocation;
	cv::Mat image;

// Methods
private:
	bool loadUserFile();

public:
	void start();
};

