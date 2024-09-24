#include <iostream>
#include <vector>

int main() {
    std::vector<double> v = {1.0, 2.0, 3.0};  // 1D vector

    // 2D vector (3x3 matrix)
    std::vector<std::vector<double>> m = {
        {1.0, 2.0, 3.0}, 
        {4.0, 5.0, 6.0}, 
        {7.0, 8.0, 9.0}
    };
    
    std::cout << "1D Vector (v):" << std::endl;
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "2D Vector (Matrix):" << std::endl;
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m[i].size(); ++j) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
