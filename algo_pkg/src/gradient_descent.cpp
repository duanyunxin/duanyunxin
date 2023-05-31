#include <iostream>
#include <cmath>

// 定义目标函数f(x)=x^2+5
double objectiveFunction(double x)
{
    return std::pow(x, 5) + std::pow(x, 2) + 100;
}

// 目标函数对参数的梯度
double gradient(double x) // 这里直接写出导数的解析解，梯度下降法一般是针对简单形式的计算
{
    return 5 * x + 2 * x;
}

double gradientDescent(double initial_x, double learning_rate, int max_iterations) 
{
    double x = initial_x;
    for (int i = 0; i < max_iterations; ++i)
    {
        double grad = gradient(x);
        x -= learning_rate * grad;
    }

    return x;
}

int main()
{
    double initial_x = 0.0;
    double learning_rate = 0.01;
    int max_iterations = 100;

    double optimal_x = gradientDescent(initial_x, learning_rate, max_iterations);
    double optimal_value = objectiveFunction(optimal_x);

    std::cout << "Optimal x: " << optimal_x << std::endl;
    std::cout << "Optimal value: " << optimal_value << std::endl;

    return 0;
}