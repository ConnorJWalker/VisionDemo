#include "Renderer.h"

// This function is used to draw all of the rectanghles onto the image and then
// display it in a named window. In the final project this would not be needed,
// this is just so we can see what is going on
void Renderer::render(std::vector<DetectedCard> cards, cv::Mat image) {
	cv::Scalar colour(0, 0, 255);

	for (DetectedCard card : cards) {
		cv::rectangle(image, card.cardRectangle, colour);
	}

	cv::resize(image, image, cv::Size(), scaleX, scaleY);
	cv::imshow(windowName, image);
}

void Renderer::renderCanny(std::vector<DetectedCard> cards, cv::Mat cannyImage) {
	cv::resize(cannyImage, cannyImage, cv::Size(), scaleX, scaleY);
	cv::imshow(cannyWindow, cannyImage);
}

void Renderer::renderOutline(std::vector<DetectedCard> cards, int width, int height) {
	cv::Mat background(width, height, CV_8UC3, cv::Scalar(0, 0, 0));

	cv::Scalar white(255, 255, 255);
	cv::Scalar blue(255, 100, 100);

	std::string colours[2] = { "Red", "Black" };

	for (size_t i = 0; i < cards.size(); i++) {
		cv::rectangle(background, cards[i].cardRectangle, white);

		std::vector<std::string> renderData = {
			"X: " + std::to_string(cards[i].center.x) + " Y: " + std::to_string(cards[i].center.y),
			"Colour: " + colours[(int)cards[i].colour],
			"Colour Percentage: " + std::to_string(cards[i].colourPercentage)
		};

		for (size_t j = 0; j < renderData.size(); j++) {
			cv::Size size = cv::getTextSize(renderData[j], cv::FONT_HERSHEY_SIMPLEX, 1, 1, 0);
			int buffer = 15;

			cv::putText(
				background,
				renderData[j],
				cv::Point(
					cards[i].center.x - (size.width / 2),
					cards[i].center.y - ((size.height * renderData.size() / 2) - (j * (size.height + buffer)))
				),
				cv::FONT_HERSHEY_SIMPLEX,
				1, 
				blue
			);
		}

		cv::Point textOrigin(cards[i].cardRectangle.tl().x, cards[i].cardRectangle.tl().y - 10);
		cv::putText(background, std::to_string(i), textOrigin, cv::FONT_HERSHEY_SIMPLEX, 1.5, white);
	}

	cv::resize(background, background, cv::Size(), scaleX, scaleY);
	cv::imshow(outlineWindow, background);
}
