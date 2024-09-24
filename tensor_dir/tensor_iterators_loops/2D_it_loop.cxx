#include <iostream>
#include <vector>

int main() {
    // Create a 2D matrix (3x3)
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Loop through rows (outer loop)
    for (size_t i = 0; i < matrix.size(); ++i) {
        // Loop through columns (inner loop)
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            std::cout << "matrix[" << i << "][" << j << "] = " << matrix[i][j] << std::endl;
        }
    }

    return 0;
}
