#include <iostream>
#include <vector>
#include <Eigen/Dense>

typedef std::pair<float, float> Point2f;

Eigen::Vector3f fitCurve(std::vector<Point2f>& transformed_boundary)
{
    int n = transformed_boundary.size();
    Eigen::MatrixXf X(n, 3);
    Eigen::VectorXf Y(n);

    for (int i = 0; i < n; i++)
    {
        X(i, 0) = transformed_boundary[i].first * transformed_boundary[i].first;  // x^2
        X(i, 1) = transformed_boundary[i].first;  // x
        X(i, 2) = 1;  // bias
        Y(i) = transformed_boundary[i].second;
    }

    Eigen::Vector3f coeff = X.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(Y);
    return coeff;
}

int main()
{
    std::vector<Point2f> data;
    for (float x = -10; x <= 10; x += 0.5)
    {
        float y = 2.5*x*x + 3*x + 4.7;
        data.push_back(Point2f(x, y));
    }

    Eigen::Vector3f coeff = fitCurve(data);

    std::cout << "Fitted curve parameters: " << coeff.transpose() << std::endl;
    
    return 0;
}