#pragma once
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

struct DetectedCard {
	cv::Point2i center;
	cv::Rect cardRectangle;
};

class Detector
{
// Properties
public:
	cv::Mat cannyOutput;

// Methods
private:
	DetectedCard addCardData(cv::Rect card);

public:
	std::vector<DetectedCard> findPlayingCards(cv::Mat image, double threshold = 60);
};

