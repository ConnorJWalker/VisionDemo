#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "Renderer.h"
#include "Detector.h"

class Application
{
// Properties
private:
	// Filename / path for program image program should load
	std::string imageLocation;

	// Image containing image user loaded in
	cv::Mat image;

	Detector detector;
	Renderer renderer;

	int thresholdSlider;
	const int thresholdSliderMaxValue = 300;
	double threshold = 60;

// Methods
private:

	/*
	 * Asks the user to enter the file they want to use for this demo and
	 * loads it into image property
	 *
	 * @Returns true if file is loaded successfully, false if not
	 */
	bool loadUserFile();

	/*
	 * Askes the user if they want to run the application again and gets their 
	 * response
	 * 
	 * @ Returns true if they want to run again, false if not
	 */
	bool shouldRunAgain();

	/*
	 * Callback function for trackbar changes. Sets the new threshold value and
	 * reruns the application to regenerate data with new threshold value
	 *
	 * @Params void* - a pointer to the current class instance to use to access
	 * the Application classes methods and properties
	 */
	static void onThresholdSliderChange(int, void*);

	// Runs the main application by calling the detection and render methods
	void run();

public:

	/*
	 * Entry point for the application, begins startup code and calls the main
	 * run function
	 *
	 * Public so it can be access from the main function
	 */
	void start();
};

