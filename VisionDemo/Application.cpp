#include "Application.h"

bool Application::loadUserFile() {
	std::cout << "Enter the filename or filepath of image you want to search: ";
	std::cin >> imageLocation;

	image = cv::Mat();
	image = cv::imread(imageLocation);
	if (!image.data) {
		std::cout << "\n\nCould not find image " << imageLocation << std::endl;
		return false;
	}

	return true;
}

bool Application::shouldRunAgain() {
	std::cout << "Would you like to try another photo (y/n)? ";
	char* input;
	std::cin >> input;

	return std::strcmp("y", input);
}

void Application::start() {
	while (true) {
		loadUserFile();

		std::vector<DetectedCard> cards = detector.findPlayingCards(image);
		renderer.render(cards, image);

		if (!shouldRunAgain()) {
			break;
		}
	}
}
