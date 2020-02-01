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
	std::string outlineWindow = "Outline of Card Detection";

	const float scaleX = 0.5f;
	const float scaleY = 0.5f;

public:
	std::string cannyWindow = "Canny Card Detection Result";

// Methods
public:
	void render(std::vector<DetectedCard> cards, cv::Mat image);
	void renderCanny(std::vector<DetectedCard> cards, cv::Mat cannyImage);
	void renderOutline(std::vector<DetectedCard> cards, int width, int height);
};

