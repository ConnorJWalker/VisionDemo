#include "Detector.h"

/*
 *  Used to convert a rectangle object into a DetectedCard object
 *  This is just used to add extra data to the card that could be useful
 *  elsewere in the program
 */
DetectedCard Detector::addCardData(cv::Rect card, cv::Mat image) {
	double percentage = 0;

	return {
		cv::Point2i(
			card.tl().x + (card.width / 2),
			card.br().y - (card.height / 2)
		),
		card,
		detectCardColour(card, image, percentage),
		percentage
	};
}

bool Detector::isCardValid(cv::Rect card, std::vector<DetectedCard> detectedCards) {
	// Make sure the "card" is a reasonable width and height to avoid
	// noise being detected
	if (card.width < 100 && card.height < 200) return false;

	// Make sure that the card is at least 10px away from the last to prevent cards being counted
	// multiple times
	if (detectedCards.size() >= 1) {
		int distanceX = abs(card.tl().x - detectedCards[detectedCards.size() - 1].cardRectangle.tl().x);
		int distanceY = abs(card.tl().y - detectedCards[detectedCards.size() - 1].cardRectangle.tl().y);

		if (distanceX < 50 && distanceY < 50) {
			return false;
		}
	}

	return true;
}

Colour Detector::detectCardColour(cv::Rect card, cv::Mat image, double& percentage) {
	cv::Mat roi(image, card);
	cv::cvtColor(roi, roi, cv::COLOR_BGR2HSV);

	double redPrecentage, blackPercentage;

	auto colourDetection = [](double& percentage, cv::Mat roi, std::vector<int> upperBound, std::vector<int> lowerBound) {
		cv::Mat mask;
		cv::inRange(roi, lowerBound, upperBound, mask);
		
		int imageSize = mask.rows * mask.cols;
		cv::threshold(mask, mask, 120, -1, cv::THRESH_TOZERO);

		percentage = 1 - (imageSize - cv::countNonZero(mask)) / (double )imageSize;
	};

	std::vector<int> lowerRed = { 0, 120, 70 };
	std::vector<int> upperRed = { 10, 255, 255 };
	colourDetection(redPrecentage, roi, upperRed, lowerRed);

	std::vector<int> lowerBlack = { 0, 0, 0 };
	std::vector<int> upperBlack = { 180, 255, 125 };
	colourDetection(blackPercentage, roi, upperBlack, lowerBlack);

	if (redPrecentage > blackPercentage) {
		percentage = redPrecentage;
		return Colour::RED;
	}

	percentage = blackPercentage;
	return Colour::BLACK;
}

std::vector<DetectedCard> Detector::findPlayingCards(cv::Mat image, double threshold) {
	cv::Mat greyscaleImage;
	cv::cvtColor(image, greyscaleImage, cv::COLOR_BGR2GRAY);

	cv::Canny(greyscaleImage, cannyOutput, threshold, threshold * 2);
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(cannyOutput, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	// For each detected contour, create a rectangle object in its location and add it to the
	// detected card vector to be returned to renderer. 
	std::vector<DetectedCard> detectedCards;
	for (auto contour : contours) {
		std::vector<cv::Point> contoursPoly;
		cv::approxPolyDP(contour, contoursPoly, 3, true);

		cv::Rect card = cv::boundingRect(contoursPoly);

		if (isCardValid(card, detectedCards)) {
			detectedCards.push_back(addCardData(card, image));
		}
	}

	return detectedCards;
}
