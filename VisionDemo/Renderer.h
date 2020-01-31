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
	std::string cannyWindow = "Canny Card Detection Result";

	const float scaleX = 0.5f;
	const float scaleY = 0.5f;

// Methods
public:
	~Renderer();
	void render(std::vector<DetectedCard> cards, cv::Mat image);
	void renderCanny(std::vector<DetectedCard> cards, cv::Mat cannyImage);
};

