// 解决非线性最小二乘问题，通过不断线性化残差函数求解线性方程组
// 逐步更新参数向量以最小化残差函数

#include <iostream>
#include <Eigen/Dense>

typedef Eigen::VectorXd Vector;
typedef Eigen::MatrixXd Matrix;

// 定义残差函数，3个方程的非线性最小二乘问题
Vector residualFunction(const Vector& x)
{
    Vector residuals(3);
    residuals(0) = x(0) + 2 * x(1) - 2;
    residuals(1) = x(0) * x(1) + x(1) - 1;
    residuals(2) = x(0) * x(0) + x(1) * x(1) - 2;
    return residuals;
}

// 定义雅可比矩阵
Matrix jacobianFunction(const Vector& x) // 已知函数形式，直接用解析解表示出来
{
    Matrix jacobian(3, 2);
    jacobian(0, 0) = 1;
    jacobian(0, 1) = 2;
    jacobian(1, 0) = x(1) + 1;
    jacobian(1, 1) = x(0) + 1;
    jacobian(2, 0) = 2 * x(0);
    jacobian(2, 1) = 2 * x(1);
    return jacobian;
}

int main()
{
    Vector x(2); // 初始参数向量
    x << 0, 0;

    const int maxIterations = 100;
    const double convergenceThreshold = 1e-6;

    for (int i = 0; i < maxIterations; ++i)
    {
        Vector residuals = residualFunction(x);
        Matrix jacobian = jacobianFunction(x);

        // 求解线性方程组 J * delta = -r(x)，residual里是含有当前迭代的x的，解出delta即可
        // colPivHouseholderQr使用了Eigen库的QR分解方法，将矩阵jacobian分解为Q和R
        // solve通过R * delta = -Q^T * residuals来解delta
        Vector delta = jacobian.colPivHouseholderQr().solve(-residuals); // 最小二乘
        x += delta; // 用delta来更新参数向量

        if (delta.norm() < convergenceThreshold)
        {
            std::cout << "Converged after " << i+1 << " iterations." << std::endl;
            break;
        }
    }

    std::cout << "Solution: x = " << x.transpose() << std::endl;
    return 0;
}