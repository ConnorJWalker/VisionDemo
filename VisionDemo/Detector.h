#pragma once
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

enum class Colour {
	RED, BLACK
};

struct DetectedCard {
	cv::Point2i center;
	cv::Rect cardRectangle;
	Colour colour;
	int colourPercentage;
};

class Detector
{
// Properties
public:
	// Image containing the output of the canny edge detection
	// Public so render class can access it
	cv::Mat cannyOutput;

// Methods
private:
	/*
	 * Adds additional data to the card that has been detected
	 * 
	 * @Param card - a cv::Rect object in the location where the detector found a card
	 * @Retuns a DetectedCard struct containing passed in rect and additional data
	 */
	DetectedCard addCardData(cv::Rect card, cv::Mat image);

	/* 
	 * Tests to see if detected card could actually be a card or a bit of noise / background
	 *
	 * @Returns true if card could be card, false if not
	 * @Param card - a cv::Rect object in the location where the detector believes a card might be
	 * @Param detectedCards - a vector of previously detected cards to compare pixel distance of current
	 * card from
	 */
	bool isCardValid(cv::Rect card, std::vector<DetectedCard> detectedCards);

	Colour detectCardColour(cv::Rect card, cv::Mat image, int& percentage);

public:
	/*
	 *	Uses the canny edge detection to find playing cards in provided image
	 *
	 *  @Param image - the image loaded in from the file at Application::loadUserFile
	 *  @Returns vector of DetectedCard structs (found in Detector.h) each element contains
	 *  a rectangle object around the cards location as well as its center X, Y value
	 */
	std::vector<DetectedCard> findPlayingCards(cv::Mat image, double threshold = 60);
};

