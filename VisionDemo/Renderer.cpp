#include "Renderer.h"

Renderer::~Renderer() {
	cv::destroyWindow(windowName);
}

void Renderer::render(std::vector<DetectedCard> cards, cv::Mat image) {
	cv::Scalar colour(0, 0, 255);

	for (DetectedCard card : cards) {
		cv::rectangle(image, card.cardRectangle, colour);
	}

	cv::resize(image, image, cv::Size(), 0.5, 0.5);
	cv::imshow(windowName, image);
}
