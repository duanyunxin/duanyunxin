// 计算一个二阶张量（矩阵）的乘积

#include <iostream>
#include <Eigen/Dense>

int main()
{
    Eigen::Matrix<float, 2, 2> tensor1;
    Eigen::Matrix<float, 2, 2> tensor2;

    tensor1 << 1, 2,
               3, 4;
    tensor2 << 5, 6,
               7, 8;
    Eigen::Matrix<float, 2, 2> product = tensor1 * tensor2;

    std::cout << "Product:\n" << product << std::endl;

    return 0;
}