#include <iostream>
#include <Eigen/Dense>

struct MowerState
{
    double x;
    double y;
    double theta;
}

class MPCController
{
public:
    MPCController() {} // 初始化控制器参数

    double objectiveFuncion(const MowerState& state) // 传入当前在局部地图上的pose
    {
        int x_idx = static_cast<int>(state.x); // 在图片上的坐标
        int y_idx = static_cast<int>(state.y); 
        double distance = std::numeric_limits<double>::max();
        // 通过这个pose再dst图上找到最小近距离，赋值给min_distance;

        return std::pow(distance - target_distance_, 2); 
    }

    // 计算割草机与边界的距离
    // 返回距离的加权作为目标函数值

    bool checkConstraints(const MowerState& state, double v, double w) // 传入当前在局部地图上的pose
    {
        // 检查割草机的位置是否在有效范围内
        if (state.x < 0 || state.x > maxX || state.y < 0 || state.y > maxY) // maxX, maxY是地图最大尺寸
        {
            return false;
        }

        // 检查割草机速度是否在限制范围内
        if (v < minV || v > maxV)
        {
            return false;
        }

        // 检查割草机转弯半径（线速度和角速度的比值？）

        // 检查是否出边界（设一参数，割草机和边界必须保持一定的距离，且不能出边界）
        return true;
    }

    MowerState predictModel(const MowerState& cur_state, double v, double w, double dt)
    {
        MowerState next_state;

        // 根据当前状态和控制输入计算割草机的下一个状态

        // double dt = 1.0 / N;  // 这是我们选择的时间间隔，N是步数。
        double dx = v * cos(cur_state.theta) * dt;
        double dy = v * sin(cur_state.theta) * dt;
        double dTheta = w * dt;

        // 计算割草机下一个状态
        next_state.x = cur_state.x + dx;
        next_state.y = cur_state.y + dy;
        next_state.theta = cur_state.theta + dTheta;

        return next_state;
    }

    void runMPC(const MowerState& initial_state)
    {
        MowerState current_state = initial_state;
        double dt = 0.1;

        while(/* 终止条件 */)
        {
            // 计算最佳控制输入
            double best_v = 0.0;
            double best_w = 0.0;
            double best_objective_value = std::numeric_limits<double>::max();

            for (double v = 0.0; v <= max_linear_vel_; v += 0.05)
            {
                for (double w = -max_angular_vel_; w <= max_linear_vel_; w += 0.05)
                {
                    LawnMowerState next_state = predictModel(current_state, v, w, dt);
                    if (checkConstraints(next_state, v, w))
                    {
                        // 计算目标函数值
                        double objective_value = objectiveFuncion(next_state);
                        // 更新最佳目标函数值和最佳控制输入
                        if (objective_value < best_objective_value)
                        {
                            best_objective_value = objective_value;
                            best_v = v;
                            best_w = w;
                        }
                    }
                }
            }

            current_state = predictModel(current_state, best_v, best_w, dt);
        }
    }

private:
    int N; // 预测视窗
    double max_linear_vel_;
    double max_angular_vel_;
    double max_x_; // 不能走出边界 
    double max_y_; // 
    double target_distance_;
};