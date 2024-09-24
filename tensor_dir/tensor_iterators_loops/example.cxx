#include <iostream>
#include <vector>

std::vector<std::vector<int>> multiply_matrices(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int rows = A.size();
    int cols = B[0].size();
    int inner_dim = B.size();  // A.cols == B.rows
    
    std::vector<std::vector<int>> C(rows, std::vector<int>(cols, 0)); // Result matrix
    
    // Matrix multiplication loop
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < inner_dim; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int main() {
    std::vector<std::vector<int>> A = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<int>> B = {{7, 8}, {9, 10}, {11, 12}};

    std::vector<std::vector<int>> C = multiply_matrices(A, B);

    // Print the result matrix
    for (const auto& row : C) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
