// 在最小二乘迭代法中，参数会根据学习率进行迭代更新，直到达到收敛条件。学习率决定了每次迭代中参数的调整幅度。较大的学习率可能导致迭代过程中的震荡或发散，而较小的学习率可能导致收敛速度较慢。

// 闭式解是通过直接求解最小二乘问题的正规方程得到的。它是一种解析解，不需要迭代过程。闭式解在数学上是精确的，可以得到问题的全局最优解。

// 当你将学习率设置为0.1时，迭代法和闭式解得到相同的结果，这可能是因为这个学习率的设置比较合适，能够使迭代法在迭代过程中趋于收敛。然而，当学习率设置为0.01时，迭代法可能无法充分收敛到最优解，导致与闭式解不同。

// 从准确性的角度来看，闭式解提供了最优解的数学保证，它是全局最优解。而迭代法可能受到学习率和迭代次数的影响，可能只能得到局部最优解。因此，从准确性的角度来说，闭式解更可靠。

// 然而，迭代法具有一些优势。它可以处理大规模的数据集，而闭式解在数据量较大时可能会受到计算资源和内存限制。此外，迭代法还可以应用于在线学习等动态环境中，能够逐步适应数据的变化。

// 综上所述，选择最适合问题需求和数据规模的方法。如果数据量较小且计算资源充足，闭式解可能更合适。如果数据量较大或需要动态学习，迭代法可能更具优势。

#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

const double eps = 1e-6; // 小于该值收敛

template<typename T>
struct Data
{
    Data(const vector<T>& x_data, const vector<T>& y_data)
    {
        int n = x_data.size();
        MatrixXd X(n, 2);
        VectorXd Y(n);
        for (int i = 0; i < n; i++)
        {
            X(i, 0) = x_data[i];
            X(i, 1) = static_cast<T>(1.0);
            Y(i) = y_data[i];
        }
        X_ = std::move(X);
        Y_ = std::move(Y);
    }
    MatrixXd getX() const
    {
        return X_;
    }
    VectorXd getY() const
    {
        return Y_;
    }
    MatrixXd X_;
    VectorXd Y_;
};

// 闭式解
VectorXd leastSquaredClosed(MatrixXd X, VectorXd Y)
{
    MatrixXd XtX = X.transpose() * X;
    VectorXd Xty = X.transpose() * Y;
    VectorXd theta = XtX.inverse() * Xty;
    return theta;
}

// 迭代，学习率太小导致无法收敛或者陷入局部最优解
VectorXd leastSquaredIteration(MatrixXd X, VectorXd Y, double w, double b, double learning_rate, int max_iter)
{
    VectorXd W(2);
    W << w, b;
    int iter = 0;
    int n = Y.size();
    while (iter < max_iter) {
        VectorXd y_pred = X * W;
        VectorXd error = y_pred - Y;
        double cost = error.squaredNorm() / (2.0 * n);
        if (cost < eps) {
            break;
        }
        VectorXd gradient = X.transpose() * error / n; // 残差的梯度
        W -= learning_rate * gradient; // 学习率*梯度，梯度下降，最终是要求w和b
        iter++;
    }
    // cout << "Iteration: " << iter <<endl;
    return W;
}

int main()
{
    vector<double> x_data {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 3.0};
    vector<double> y_data {0.5, 2.5, 2.0, 4.0, 3.5, 5.5, 4.0};

    Data data(x_data, y_data); // 准备数据
    MatrixXd X = data.getX();
    VectorXd Y = data.getY();

    // 初始化参数模型
    double w = 1.0, b = 0.0, learning_rate = 0.05;
    int max_iter = 1000;
    
    VectorXd W = leastSquaredIteration(X, Y, w, b, learning_rate, max_iter);    
    cout << "iter w = " << W(0) << ", b = " << W(1) << endl;

    VectorXd W_closed = leastSquaredClosed(X, Y); // 闭式解
    cout << "closed w = " << W_closed(0) << ", b = " << W_closed(1) << endl;

    return 0;
}