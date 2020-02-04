# Card Detector Test

This project is split into 3 branches, simple, master and dev

#### Simple

This branch contains just the basic implementation to show off the basic idea of how it works. This branch is likely to stay the same until a new, better, approach is found

**_This project is nowhere near completed and will be updated as we find better soloutions. This is just to give an idea of progress and how the system will work / what data we can collect_**

#### Master

This is the main branch and will have extra features to test better ways of detecting cards, making the code more complicated. Use this branch as a starting point if you want to test different implementations to see if they work better. This version will also show the Canny result of the image with a slider to allow you to test different canny thresholds

Feel free to make a pull request if a better method or a fix to any problems is found

#### Dev

This is the branch that I will be using to test new methods of detecting cards. This was built from the master starting point

## Getting Started

- [Download](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/) and [install](https://docs.opencv.org/master/d3/d52/tutorial_windows_install.html) OpenCV
- [Link OpenCv to Visual Studio](https://docs.opencv.org/master/dd/d6e/tutorial_windows_visual_studio_opencv.html)
- Fork the wanted repository
- Build and run the project (make sure the debugger is set to Debug X64)
- Enter demo.JPG when prompted for a file, or a full file path to another picture

## Example Output

Inputting Demo File

![Demo Input Screenshot](https://i.imgur.com/vY8gymb.png "Test demo Input")

Demo Photo Output

![Demo Output](https://imgur.com/4eM4U60.png "Test demo output")

Demo Canny View Output

![Demo Canny Output](https://i.imgur.com/MSdy7dx.png "Demo canny output")

Demo of Standard View vs Outline View

![Standard vs Outline](https://i.imgur.com/kJSsWM4.png "Standard view vs outline view")

Demo of Outline View with Colour Detection

![Outline View with Colour Detection](https://i.imgur.com/6cck0DJ.png "Outline view with colour detection")