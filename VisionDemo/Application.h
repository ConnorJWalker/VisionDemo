#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "Renderer.h"
#include "Detector.h"

class Application
{
// Properties
private:
	std::string imageLocation;
	cv::Mat image;

	Detector detector;
	Renderer renderer;

// Methods
private:
	bool loadUserFile();
	bool shouldRunAgain();

public:
	void start();
};

