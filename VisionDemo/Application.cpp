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

void Application::onThresholdSliderChange(int, void* object) {
	Application* app = (Application*)object;

	app->threshold = (double)app->thresholdSlider;

	std::vector<DetectedCard> cards = app->detector.findPlayingCards(app->image.clone(), app->threshold);
	app->renderer.render(cards, app->image.clone());
	app->renderer.renderCanny(cards, app->detector.cannyOutput);
}

void Application::start() {
	while (true) {
		if (!loadUserFile()) {
			continue;
		}

		////////////////// CORE APPLICATION HERE ////////////////// 
		std::vector<DetectedCard> cards = detector.findPlayingCards(image.clone());
		renderer.render(cards, image.clone());
		renderer.renderCanny(cards, detector.cannyOutput);
		///////////////////////////////////////////////////////////

		cv::createTrackbar("Threshold", renderer.cannyWindow, &thresholdSlider, thresholdSliderMaxValue, onThresholdSliderChange, this);

		while (true) {
			if (cv::waitKey(30) >= 0) break;
		}

		cv::destroyAllWindows();

		if (!shouldRunAgain()) {
			break;
		}
	}	
}
