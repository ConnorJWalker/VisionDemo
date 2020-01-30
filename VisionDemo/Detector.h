#pragma once
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

struct DetectedCard {
	cv::Point2i center;
	cv::Rect object;
};

class Detector
{
// Methods
private:
	DetectedCard addCardData(cv::Rect card);

public:
	std::vector<DetectedCard> findPlayingCards(cv::Mat image);
};

