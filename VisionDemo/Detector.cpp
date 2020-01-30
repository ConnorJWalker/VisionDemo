#include "Detector.h"

DetectedCard Detector::addCardData(cv::Rect card) {
	return {
		cv::Point2i(
			card.tl().x + (card.width / 2),
			card.br().y - (card.height / 2)
		),
		card
	};
}

std::vector<DetectedCard> Detector::findPlayingCards(cv::Mat image) {
	cv::Mat greyscaleImage;
	cv::cvtColor(image, greyscaleImage, cv::COLOR_BGR2GRAY);

	cv::Mat cannyOutput;
	int threshold = 130;
	cv::Canny(greyscaleImage, cannyOutput, threshold, threshold * 2);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(cannyOutput, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	std::vector<DetectedCard> detectedCards;
	for (auto contour : contours) {
		std::vector<cv::Point> contoursPoly;
		cv::approxPolyDP(contour, contoursPoly, 3, true);

		cv::Rect card = cv::boundingRect(contoursPoly);
		detectedCards.push_back(addCardData(card));
	}

	return detectedCards;
}
