#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat image = cv::imread("car-967387_640.png");
    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

     // Apply Gaussian blur
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(15, 15), 0);

    // Convert to grayscale
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

     // Display the original and blurred images
    cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Original Image", image);

    cv::namedWindow("Blurred Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Blurred Image", blurredImage);

    cv::namedWindow("Grayscale Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Grayscale Image", grayImage);

    cv::waitKey(0);
    return 0;
}
