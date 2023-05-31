#include <iostream>
#include <cmath>

double wrapRadiantoPi(double radian) {
    double normalizedAngle = std::fmod(radian + M_PI, 2 * M_PI);  // 将角度映射到0到2*pi范围内
    if (normalizedAngle < 0)
        normalizedAngle += 2 * M_PI;  // 将负角度映射到正角度范围内
    return normalizedAngle - M_PI;  // 将角度映射到-pi到pi范围内
}

int main() {
    double radian = 4.19017;  // 任意角度
    double normalizedAngle = wrapRadiantoPi(radian);

    std::cout << "Original angle: " << radian << std::endl;
    std::cout << "Normalized angle: " << normalizedAngle << std::endl;

    return 0;
}