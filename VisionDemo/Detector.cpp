#include "Detector.h"

/*
 *  Used to convert a rectangle object into a DetectedCard object
 *  This is just used to add extra data to the card that could be useful
 *  elsewere in the program
 */
DetectedCard Detector::addCardData(cv::Rect card) {
	return {
		cv::Point2i(
			card.tl().x + (card.width / 2),
			card.br().y - (card.height / 2)
		),
		card
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

/*
 *	Uses the canny edge detection to find playing cards in provided image
 *  @Param image - the image loaded in from the file at Application::loadUserFile
 *  @Returns vector of DetectedCard structs (found in Detector.h) each element contains
 *  a rectangle object around the cards location as well as its center X, Y value 
 */
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
			detectedCards.push_back(addCardData(card));
		}
	}

	return detectedCards;
}
