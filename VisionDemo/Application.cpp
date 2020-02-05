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
	app->run();
}

void Application::run() {
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<DetectedCard> cards = detector.findPlayingCards(image.clone(), threshold);
	renderer.render(cards, image.clone());
	renderer.renderCanny(cards, detector.cannyOutput);
	renderer.renderOutline(cards, image.rows, image.cols);

	auto finish = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

	std::cout << "Execution finished in " << duration << " milliseconds" << std::endl;
}

void Application::start() {
	while (true) {
		if (!loadUserFile()) {
			continue;
		}

		run();
		cv::createTrackbar("Threshold", renderer.outlineWindow, &thresholdSlider, thresholdSliderMaxValue, onThresholdSliderChange, this);

		while (true) {
			if (cv::waitKey(30) >= 0) break;
		}

		cv::destroyAllWindows();

		if (!shouldRunAgain()) {
			break;
		}
	}	
}
