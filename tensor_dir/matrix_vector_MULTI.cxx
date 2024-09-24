// w = A · v -> A = [MxN] 
//w_i = Σ (from j=1 to n) [ A_ij * v_j ]

/*
  +-----------------------------------------------+
  |                  w_i                         |
  |  (i)                                             |
  +-----------------------------------------------+
           |
           |
           v
  +-----------------------------------------------+
  |        ∑   A_ij     *    v_j         (j=1 to n)  |
  |          (i)                                |
  +-----------------------------------------------+
 * */

#include <iostream>
#include <vector>

// Function to perform matrix-vector multiplication
std::vector<double> matrix_vector_multiply(const std::vector<std::vector<double>>& A, const std::vector<double>& v) {
    int m = A.size();    // Number of rows in the matrix
    int n = v.size();    // Size of the vector (number of columns in the matrix)

    std::vector<double> w(m, 0.0);  // Initialize result vector with 0's

    // Perform matrix-vector multiplication
    for (int i = 0; i < m; ++i) {   // Loop through rows of the matrix
        for (int j = 0; j < n; ++j) { // Loop through columns of the matrix
            // ASCII: w[i] += A[i][j] * v[j] => w_i = sum(A_ij * v_j)
            w[i] += A[i][j] * v[j];
        }
    }

    return w;  // Return the resulting vector
}

int main() {
    // Define a 3x3 matrix (2D vector)
    std::vector<std::vector<double>> A = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    // Define a vector of size 3
    std::vector<double> v = {1.0, 2.0, 3.0};

    // Perform matrix-vector multiplication
    std::vector<double> result = matrix_vector_multiply(A, v);

    // Display the result
    std::cout << "Resulting vector:\n";
    for (double x : result) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}
