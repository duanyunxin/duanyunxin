#include <opencv4/opencv2/opencv.hpp>
#include <vector>

const double simplification_factor = 0.005;

std::vector<std::vector<cv::Point>> detectBoundary(const cv::Mat& binary_image)
{
    if (binary_image.empty())
    {
        std::cout << "Input image is empty" << std::endl;
        return {};
    }

    if (binary_image.type() != CV_8UC1) {
        std::cout << "Input image is not a binary image" << std::endl;
        return {};
    }

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // 查找轮廓（计算时间）
    // cv::findContours(binary_image, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    cv::findContours(binary_image, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    std::vector<std::vector<cv::Point>> non_edge_contours;
    // 处理图片边界轮廓
    for (const auto& contour : contours) 
    {
        std::vector<cv::Point> filtered_contour;
        // bool is_edge = false;
        // 检查每个点是否在边缘
        for (const auto& point : contour) 
        {
            if (point.x == 0 || point.y == 0 || point.x == binary_image.cols - 1 || point.y == binary_image.rows - 1) 
            {
                // contours.
                // is_edge = true;
                // break;
                continue;
            }
            else
            {
                filtered_contour.push_back(point);
            }
        }

        non_edge_contours.push_back(filtered_contour);
        // 如果轮廓不在边缘，添加到列表
        // if (!is_edge) 
        // {
        //     non_edge_contours.push_back(contour);
        // }
    }

    // 简化轮廓
    // for (size_t i = 0; i < non_edge_contours.size(); ++i)
    // {
    //     double epsilon = simplification_factor * cv::arcLength(non_edge_contours[i], true);
    //     cv::approxPolyDP(non_edge_contours[i], non_edge_contours[i], epsilon, true);
    // }

    return non_edge_contours;
    // return contours;
}

cv::Mat drawSolidCircle(int image_size)
{
    cv::Mat image = cv::Mat::ones(image_size, image_size, CV_8UC1) * 255;
    cv::Point center(image.cols * 0.5, image.rows * 0.5);
    int radius = std::min(image.cols, image.rows) * 0.25;
    cv::circle(image, center, radius, cv::Scalar(0), -1);
    return image;
}

void createBinaryImage(cv::Mat& image)
{
    double thresholdValue = 128.0;  // 阈值，可以根据需要调整
    double maxValue = 255.0;  // 设置为阈值以上的像素的值
    cv::threshold(image, image, thresholdValue, maxValue, cv::THRESH_BINARY);
}

int main()
{
    // int size = 500;
    // cv::Mat image = drawSolidCircle(size);
    // cv::namedWindow("Circle", cv::WINDOW_NORMAL);
    // cv::imshow("Circle", image);
    // cv::waitKey(0);

    cv::Mat image = cv::imread("/home/hsb/Pictures/20230425-120121.jpg", cv::IMREAD_GRAYSCALE);
    createBinaryImage(image);
    std::vector<std::vector<cv::Point>> boundaries = detectBoundary(image);

    for (const auto& boundary : boundaries)
    {
        for (const auto& point : boundary)
        {
            std::cout << point << std::endl;
            cv::circle(image, point, 2, cv::Scalar(150, 150, 150), -1);
        }
        std::cout << std::endl;
    }

    cv::namedWindow("Circle", cv::WINDOW_NORMAL);
    cv::imshow("Circle", image);
    cv::waitKey(0);

    return 0;
}