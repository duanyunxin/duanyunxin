#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x;
    double y;
    double angle;
};

// 计算三次样条插值曲线上所有点
std::vector<Point> computeCubicSplineInterpolation(const std::vector<double>& x, const std::vector<double>& y)
{
    int n = x.size();
    std::vector<double> h(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        h[i] = x[i + 1] - x[i];
    }

    std::vector<double> alpha(n - 1);
    for (int i = 1; i < n - 1; ++i) {
        alpha[i] = (3.0 / h[i]) * (y[i + 1] - y[i]) - (3.0 / h[i - 1]) * (y[i] - y[i - 1]);
    }

    std::vector<double> l(n), u(n), z(n);
    l[0] = 1.0;
    u[0] = 0.0;
    z[0] = 0.0;

    for (int i = 1; i < n - 1; ++i) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1];
        u[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    std::vector<double> c(n), b(n), d(n);
    l[n - 1] = 1.0;
    z[n - 1] = 0.0;
    c[n - 1] = 0.0;

    for (int j = n - 2; j >= 0; --j) {
        c[j] = z[j] - u[j] * c[j + 1];
        b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3.0;
        d[j] = (c[j + 1] - c[j]) / (3.0 * h[j]);
    }

    std::vector<Point> interpolatedPoints;
    for (int i = 0; i < n - 1; ++i) {
        double stepSize = 0.1;  // 步长，控制插值曲线上点的密度
        double t = x[i];
        while (t < x[i + 1]) {
            double delta = t - x[i];
            double yValue = y[i] + b[i] * delta + c[i] * std::pow(delta, 2) + d[i] * std::pow(delta, 3);
            
            // 计算切线的斜率
            double slope = b[i] + 2 * c[i] * delta + 3 * d[i] * std::pow(delta, 2);

            // 计算切线的朝向角度
            double angle = std::atan(slope);

            interpolatedPoints.push_back({t, yValue, angle});
            t += stepSize;
        }
    }

    return interpolatedPoints;
}

int main()
{
    // 输入样本点的 x 和 y 值
    std::vector<double> x = {0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> y = {0.0, 1.0, 0.5, -0.5, 0.0};

    // 计算三次样条插值曲线上的所有点
    std::vector<Point> interpolatedPoints = computeCubicSplineInterpolation(x, y);

    // 输出插值曲线上的所有点的（x, y）坐标及朝向角度
    std::cout << "Interpolated points on the cubic spline curve:" << std::endl;
    for (const Point& point : interpolatedPoints) {
        std::cout << "(" << point.x << ", " << point.y << ") - Angle: " << point.angle << std::endl;
    }
    
    // std::cout << "x: ";
    // for (const Point& point : interpolatedPoints) {
    //     // std::cout << "(" << point.x << ", " << point.y << ") - Angle: " << point.angle << std::endl;
    //     std::cout << point.x << ", ";
    // }
    // std::cout << std::endl;
    // std::cout << "y: ";
    // for (const Point& point : interpolatedPoints) {
    //     std::cout << point.y << ", ";
    // }

    // std::cout << std::endl;
    // std::cout << "angle: ";
    // for (const Point& point : interpolatedPoints) {
    //     std::cout << point.angle << ", ";
    // }
    // std::cout << std::endl;
    
    return 0;
}