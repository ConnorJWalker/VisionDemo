#include "Application.h"

bool Application::loadUserFile() {
	std::cout << "Enter the filename or filepath of image you want to search: ";
	std::cin >> imageLocation;

	image = cv::imread(imageLocation);
	if (image.empty()) {
		std::cout << "Could not find image " << imageLocation << std::endl;
		return false;
	}

	return true;
}

bool Application::shouldRunAgain() {
	std::cout << "Would you like to try another photo (y/n)? ";
	std::string input;
	std::cin >> input;

	return !(bool)std::strcmp("y", input.c_str());
}

void Application::start() {
	while (true) {
		if (!loadUserFile()) {
			continue;
		}

		std::vector<DetectedCard> cards = detector.findPlayingCards(image.clone());
		renderer.render(cards, image.clone());
		
		while (true) {
			if (cv::waitKey(30) >= 0) break;
		}

		cv::destroyAllWindows();

		if (!shouldRunAgain()) {
			break;
		}
	}	
}
