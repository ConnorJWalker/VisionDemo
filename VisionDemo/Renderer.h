#pragma once
#include <string>
#include <vector>
#include <opencv2/highgui.hpp>
#include "Detector.h"

class Renderer
{
// Properties
private:
	std::string windowName = "Simple Card Detection";

// Methods
private:

public:
	~Renderer();
	void render(std::vector<DetectedCard> cards, cv::Mat image);
};

