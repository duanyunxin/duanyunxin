#include <Eigen/Dense>
#include <iostream>

double cosine_similarity(const Eigen::VectorXd& A, const Eigen::VectorXd& B) 
{
    double dot_product = A.dot(B);
    double normA = A.norm();
    double normB = B.norm();

    return dot_product / (normA * normB); // 返回余弦相似度，通过方向判断相似性
}

int main()
{
    Eigen::VectorXd A(3);
    A << 1, 2, 3;
    Eigen::VectorXd B(3);
    B << 4, 5, 6;

    // 计算余弦相似度并打印
    double cos_sim = cosine_similarity(A, B);
    std::cout << "Cosine Similarity: " << cos_sim << std::endl;

    return 0;

}