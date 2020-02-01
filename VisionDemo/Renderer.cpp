#include "Renderer.h"

Renderer::~Renderer() {
	cv::destroyAllWindows();
}

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

	for (size_t i = 0; i < cards.size(); i++) {
		cv::rectangle(background, cards[i].cardRectangle, white);

		std::string coords = "X: " + std::to_string(cards[i].center.x) + " Y: " + std::to_string(cards[i].center.y);
		cv::putText(
			background,
			coords,
			cv::Point(
				cards[i].center.x - (cv::getTextSize(coords, cv::FONT_HERSHEY_SIMPLEX, 1, 1, 0).width / 2),
				cards[i].center.y
			),
			cv::FONT_HERSHEY_SIMPLEX,
			1, 
			blue
		);

		cv::Point textOrigin(cards[i].cardRectangle.tl().x, cards[i].cardRectangle.tl().y - 10);
		cv::putText(background, std::to_string(i), textOrigin, cv::FONT_HERSHEY_SIMPLEX, 1.5, white);
	}

	cv::resize(background, background, cv::Size(), scaleX, scaleY);
	cv::imshow(outlineWindow, background);
}
