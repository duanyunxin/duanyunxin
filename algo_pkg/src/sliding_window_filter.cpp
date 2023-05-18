// 原理是通过计算窗口内数据的平均值来减小噪声和快速变化的影响，
// 从而得到更平滑的输出
// 优点：
// 1. 平滑效果好：滑动窗口平均可以有效地减少传感器数据中的噪声和突变，从而提供更平滑的输出。
// 2. 实现简单：滑动窗口平均算法的实现相对简单，不需要复杂的数学模型或参数调整。
// 缺点：
// 1. 响应延迟：滑动窗口平均会引入延迟，因为需要等待足够的数据样本来计算平均值。这可能会导致滤波后的数据响应变慢。
// 2. 信息损失：滑动窗口平均会将窗口内的数据平均化，从而使得一些快速变化的细节信息丢失。这对于某些应用场景可能不可取。
// 3. 窗口大小选择：选择合适的窗口大小是滑动窗口平均的关键。较小的窗口可以提供更快的响应和更好的保留细节信息，但噪声抑制效果较差；较大的窗口可以更好地抑制噪声，但响应变慢并可能丢失快速变化的信息。
// 注意事项：
// 1. 确定合适的窗口大小：选择合适的窗口大小要考虑传感器数据的特性、期望的平滑效果和响应速度等因素。
// 2. 平滑与响应折中：滑动窗口平均是一种平滑技术，但需要权衡平滑效果和响应速度之间的折中。
// 3. 数据边界处理：在滑动窗口滤波过程中，边界处的数据处理需要特别注意，以避免计算错误或引入不必要的偏差。

#include <iostream>
#include <deque>
#include <vector>

class SlidingAvg 
{
public:
    SlidingAvg(int window_size): window_size_(window_size), sum_(0.0) {}
    double update(double new_val)
    {
        values_.push_back(new_val);
        sum_ += new_val;

        if (values_.size() > window_size_)
        {
            double oldest_val = values_.front();
            values_.pop_front();
            sum_ -= oldest_val;
        }

        return sum_ / values_.size();
    }
private:
    int window_size_;
    double sum_;
    std::deque<double> values_;
};

int main()
{
    SlidingAvg s_avg(5);
    std::vector<double> input = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    std::vector<double> output;
    for (double value : input)
    {
        double smooth_val = s_avg.update(value);
        output.push_back(smooth_val);
    }

    // 输出结果
    std::cout << "Smoothed values: ";
    for (double value : output) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}