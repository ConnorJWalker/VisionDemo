#include "Renderer.h"

Renderer::Renderer() {
	cv::namedWindow(windowName);
}

Renderer::~Renderer() {
	cv::destroyWindow(windowName);
}

void Renderer::render(std::vector<DetectedCard> cards, cv::Mat image) {
	cv::Scalar colour(0, 0, 255);

	for (DetectedCard card : cards) {
		cv::rectangle(image, card.cardRectangle, colour);
	}

	cv::imshow(windowName, image);
}
