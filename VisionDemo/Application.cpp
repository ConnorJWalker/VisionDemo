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

void Application::start() {
	while (true) {
		loadUserFile();
	}
}
