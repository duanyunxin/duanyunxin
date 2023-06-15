#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void testDistanceTransform()
{
    cv::Mat src = cv::Mat::zeros(500, 500, CV_8UC1);
    
    src(cv::Rect(100, 100, 60, 60)) = 255;
    src(cv::Rect(300, 300, 80, 80)) = 255;
    src(cv::Rect(200, 200, 50, 50)) = 255;

    cv::Mat dst;
    cv::distanceTransform(src, dst, cv::DIST_L2, 3);
    cv::normalize(dst, dst, 0, 1., cv::NORM_MINMAX);

    cv::imshow("Source Image", src);
    cv::imshow("Distance Transform Image", dst);

    cv::waitKey(0);
}

int main()
{
    // testDistanceTransform();

    cv::Mat src = cv::Mat::zeros(500, 500, CV_8UC1);
    src(cv::Rect(200, 200, 100, 100)) = 255;
    cv::Mat dst;
    cv::distanceTransform(src, dst, cv::DIST_L2, 3);
    int row = 250;
    int col = 250;
    float distance = dst.at<float>(row, col);
    std::cout << "The distance from the pixel at (" << row << ", " << col << ") to the nearest zero pixel is " << distance << std::endl;
    // cv::imshow("img", src);
    // cv::waitKey(0);

    return 0;
}