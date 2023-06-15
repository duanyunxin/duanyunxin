#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

double euclidean_distance(const std::vector<double>& point1, const std::vector<double>& point2) {
    double sum = 0.0;
    for (size_t i = 0; i < point1.size(); i++) {
        double diff = point1[i] - point2[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

double manhattan_distance(const std::vector<double>& point1, const std::vector<double>& point2) {
    double sum = 0.0;
    for (size_t i = 0; i < point1.size(); i++) {
        sum += std::abs(point1[i] - point2[i]);
    }
    return sum;
}

double chebyshev_distance(const std::vector<double>& point1, const std::vector<double>& point2) {
    double max_diff = 0.0;
    for (size_t i = 0; i < point1.size(); i++) {
        max_diff = std::max(max_diff, std::abs(point1[i] - point2[i]));
    }
    return max_diff;
}

int main() {
    std::vector<double> point1 = {1.0, 2.0, 3.0};
    std::vector<double> point2 = {4.0, 6.0, 7.0};
  
    std::cout << "Euclidean distance: " << euclidean_distance(point1, point2) << std::endl;
    std::cout << "Manhattan distance: " << manhattan_distance(point1, point2) << std::endl;
    std::cout << "Chebyshev distance: " << chebyshev_distance(point1, point2) << std::endl;

    return 0;
}