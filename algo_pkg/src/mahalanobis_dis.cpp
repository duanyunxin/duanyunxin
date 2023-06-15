#include <iostream>
#include <Eigen/Dense>

double mahalanobisDistance(
    const Eigen::VectorXd& x, 
    const Eigen::VectorXd& mean,
    const Eigen::MatrixXd& cov) 
{
    Eigen::VectorXd diff = x - mean;
    Eigen::MatrixXd inv_cov = cov.inverse(); // 协方差矩阵的逆
    double mahalanobis_distance = std::sqrt((diff.transpose() * inv_cov * diff)(0, 0));
    return mahalanobis_distance;
}

int main()
{
    Eigen::VectorXd x(2);
    Eigen::VectorXd mean(2);
    Eigen::MatrixXd cov(2,2);

    x << 10, 200;
    mean << 0, 0;
    cov << 11, 0.5, 50, 100;

    double distance = mahalanobisDistance(x, mean, cov);
    std::cout << "The Mahalanobis distance is: " << distance << std::endl;
    return 0;
}