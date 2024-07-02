#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // Step 1: Create a VideoCapture object to open the default camera
    cv::VideoCapture cap(0); // 0 for default camera, or use another number for different cameras

    // Step 2: Check if the camera opened successfully
    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open the camera" << std::endl;
        return -1;
    }

    // Step 3: Create a window to display the captured image (optional)
    cv::namedWindow("Captured Image", cv::WINDOW_AUTOSIZE);

    // Step 4: Capture a frame from the camera
    cv::Mat frame;
    cap >> frame; // Capture a single frame

    // Step 5: Display the captured frame (optional)
    cv::imshow("Captured Image", frame);

    // Step 6: Save the captured frame to a file (optional)
    cv::imwrite("captured_image.jpg", frame);

    // Wait for a key press indefinitely
    cv::waitKey(0);

    // Step 7: Release the VideoCapture object and close any open windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
