// 计算jacobian，相当于一元函数的导数，因为采用迭代的方法，所有每一步都有一个jacobian，直到收敛，即求得我们想要的那个X的值
// 这个程序只计算了一步，在x+h（h=1e-6）这里的jacobian，实际用于非线性求解时，我们直接将当前迭代的x值代入jacobian的表达式
// 得到一个当前的h即delta，再用当前迭代值去加上这个delta，即更新x，直到delta或者h很小

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

// f1(x, y) = x^2 + y^2
// f2(x, y) = e^x - y

typedef double (*Function)(double, double); // 定义一个函数指针来存储要计算的偏导数的函数，将结果存储在一个二维数据中

double f1(double x, double y)
{
    return x * x + y * y;
}

double f2(double x, double y)
{
    return std::exp(x) - y;
}

void computeJacobian(double x, double y, double h, Function function[], double jacobian[][2])
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            double f_plus_h = function[i](x + h * (j == 0), y + h * (j == 1));
            double f = function[i](x, y);
            jacobian[i][j] = (f_plus_h - f) / h;
        }
    }
}

void computeJacobianByEigen(double x, double y, double h, Function functions[], Eigen::MatrixXd& jacobian)
{
    int num_functions = jacobian.rows();
    int num_variables = jacobian.cols();

    for (int i = 0; i < num_functions; ++i) 
    {
        for (int j = 0; j < num_variables; ++j) 
        {
            Eigen::VectorXd perturbed_state(num_variables);
            perturbed_state << x, y;

            perturbed_state(j) += h;
            double f_plus_h = functions[i](perturbed_state(0), perturbed_state(1));

            perturbed_state(j) -= 2 * h; // 中心差分
            double f_minus_h = functions[i](perturbed_state(0), perturbed_state(1));

            jacobian(i, j) = (f_plus_h - f_minus_h) / (2 * h);
        }
    }
}

int main()
{
    double x = 1.0;
    double y = 2.0;
    double h = 1e-6; // 步长

    Function function[2] = {f1, f2};
    double jacobian[2][2];

    computeJacobian(x, y, h, function, jacobian);

    std::cout << "Jacobian Matrix:\n";
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            std::cout << jacobian[i][j] << " ";
        }
        std::cout << "\n";
    }

    Function function_dual[2] = {f1, f2};
    int num_functions = sizeof(function_dual) / sizeof(function_dual[0]);
    int num_variables = 2;
    Eigen::MatrixXd jacobian_eigen(num_functions, num_variables);
    computeJacobianByEigen(x, y, h, function_dual, jacobian_eigen);

    std::cout << "Jacobian Matrix:\n" << jacobian_eigen << std::endl;

    return 0;
}