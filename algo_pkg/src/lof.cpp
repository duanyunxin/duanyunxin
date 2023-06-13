// 离群点检测
// 1. 计算数据点之间距离
// 2. 计算局部可达密度（LRD）
// 3. 计算局部离群因子（LOF）
// 4. 根据LOF识别离群点

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

template <typename T>
struct Point
{
    Point(T _x, T _y)
    {
        x = _x;
        y = _y;
    }
    T x;
    T y;
};

template <typename T>
double euclideanDistance(const Point<T>& pnt1, const Point<T>& pnt2)
{
    double dist2 = 0.0;
    dist2 = pow(pnt1.x - pnt2.x, 2) + pow(pnt1.y - pnt2.y, 2);
    return sqrt(dist2);
}

// 计算可达距离
double reachabilityDistance(const vector<vector<double>>& distances, int point_index, int k)
{
    vector<double> k_distances;
    for (int i = 0; i < distances.size(); ++i)
    {
        if (i != point_index) // 排除当前点
        {
            k_distances.push_back(distances[point_index][i]); // 当前点到第i个数据点间的距离
        }
    }
    std::nth_element(k_distances.begin(), k_distances.begin() + k - 1, k_distances.end()); // 排序，第k近的元素放在k-1的位置，前k个元素就是前k近的距离，而不关系其他元素，提高效率
    return k_distances[k - 1]; // 返回第k近的距离
}

// 计算局部可达密度
double localReachabilityDensity(const vector<vector<double>>& distances, int point_index, int k)
{
    double sum_reachability_distances = 0.0;
    for (int i = 0; i < distances.size(); ++i)
    {
        if (i != point_index)
        {
            double reachability_distance = reachabilityDistance(distances, i, k);
            sum_reachability_distances += reachability_distance;
        }
    }
    return (distances.size() - 1) / sum_reachability_distances;
}

// 计算局部离群因子
double localOutlierFactor(const vector<vector<double>>& distances, int point_index, int k)
{
    double sum_local_reachability_densities = 0.0;
    for (int i = 0; i < distances.size(); ++i)
    {
        if (i != point_index)
        {
            double local_reachability_density = localReachabilityDensity(distances, i, k);
            sum_local_reachability_densities += local_reachability_density;
        }
    }
    double average_local_reachability_density = sum_local_reachability_densities / (distances.size() - 1);
    double local_outlier_factor = localReachabilityDensity(distances, point_index, k) / average_local_reachability_density;
    return local_outlier_factor;
}

int main()
{
    vector<Point<double>> data = {{1.0, 2.0}, {2.0, 3.0}, {3.0, 4.0}, {4.0, 5.0}, {10.0, 11.0}};
    int k = 2; // k近邻的数量

    vector<vector<double>> distances(data.size(), vector<double>(data.size()));
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data.size(); ++j) {
            distances[i][j] = euclideanDistance(data[i], data[j]);
        }
    }

    vector<double> lof_values(data.size());
    for (int i = 0; i < data.size(); ++i)
    {
        lof_values[i] = localOutlierFactor(distances, i, k);
        cout << "LOF value for data point " << i << ": " << lof_values[i] << endl;
    }
    return 0;
}