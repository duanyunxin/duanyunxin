#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <unsupported/Eigen/AutoDiff>

typedef Eigen::Matrix<double, 3, 1> StateVector;  // 状态参数
typedef Eigen::Matrix<double, 1, 1> ObservationVector;

template<typename T>
T errorFunction(const StateVector& state, const ObservationVector& observation)
{
    // 函数表达式 y = x1*x2+x3，是一个非线性的表达式
    // 表示了状态向量(x1, x2, x3)和观测值之间的关系
    // 我传入了3个观测值，通过状态向量和y的关系，用非线性最小二乘的方式得到了一个状态向量
    T error;
    error = observation(0) - (state(0) * state(1) + state(2));
    return error;
}

void nonlinearLeastSquaresFilter(const std::vector<ObservationVector>& observations,
                                 StateVector& estimated_state)
{
    const int num_observations = observations.size();
    const int max_iterations = 100; // 迭代次数
    const double convergence_threshold = 1e-6;

    for (int i = 0; i < num_observations; ++i)
    {
        StateVector current_state = estimated_state;
        for (int iter = 0; iter < max_iterations; ++iter)
        {
            Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> jacobian;
            Eigen::Matrix<double, Eigen::Dynamic, 1> residuals;
            Eigen::Matrix<double, Eigen::Dynamic, 1> update;

            jacobian.resize(1, 3);
            residuals.resize(1, 1);
            update.resize(1, 1);

            // Compute the residuals using the current state
            residuals(0) = errorFunction<double>(current_state, observations[i]); // 体现出非线性
            // 有限差分计算雅可比矩阵（这里其实可以直接写出雅可比的解析解）
            const double h = 1e-8;
            for (int j = 0; j < 3; ++j)
            {
                StateVector perturbed_state_plus = current_state;
                perturbed_state_plus(j) += h;
                double perturbed_residual_plus = errorFunction<double>(perturbed_state_plus, observations[i]);

                StateVector perturbed_state_minus = current_state;
                perturbed_state_minus(j) -= h;
                double perturbed_residual_minus = errorFunction<double>(perturbed_state_minus, observations[i]);

                jacobian(0, j) = (perturbed_residual_plus - perturbed_residual_minus) / (2 * h);
            }

            // 最小二乘构建残差通过雅可比反解处更新量
            update =  jacobian.colPivHouseholderQr().solve(-residuals); //
            current_state += update;

            if (update.norm() < convergence_threshold) {
                break;
            }
        }
        estimated_state = current_state;
    }
}

int main()
{
    // 输入三个观测值，这三个值是同一时刻观测的结果，用一个状态向量来做最小二乘
    std::vector<ObservationVector> observations; // 这个观测值相当于y
    observations.push_back(ObservationVector(10.0));
    observations.push_back(ObservationVector(20.0));
    observations.push_back(ObservationVector(30.0));

    StateVector estimated_state;
    estimated_state << 1.0, 2.0, 3.0; // 有三个状态变量x1，x2，x3，jocabian包含3个分量


    nonlinearLeastSquaresFilter(observations, estimated_state); // 输出通过最小二乘估计的状态向量
    std::cout << "Estimated state: " << estimated_state.transpose() << std::endl;
    return 0;
}