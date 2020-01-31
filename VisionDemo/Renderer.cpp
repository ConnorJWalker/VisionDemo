#include "Renderer.h"

Renderer::~Renderer() {
	cv::destroyWindow(windowName);
}

// This function is used to draw all of the rectanghles onto the image and then
// display it in a named window. In the final project this would not be needed,
// this is just so we can see what is going on
void Renderer::render(std::vector<DetectedCard> cards, cv::Mat image) {
	cv::Scalar colour(0, 0, 255);

	for (DetectedCard card : cards) {
		cv::rectangle(image, card.cardRectangle, colour);
	}

	cv::resize(image, image, cv::Size(), 0.5, 0.5);
	cv::imshow(windowName, image);
}
