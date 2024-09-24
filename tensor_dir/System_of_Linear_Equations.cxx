//(Ax = b)
//x = A^(-1) * b


#include <iostream>
#include <vector>

// Function to perform Gaussian elimination
std::vector<double> gaussian_elimination(std::vector<std::vector<double>> A, std::vector<double> b) {
    /***************************************************************
 *                          Gaussian Elimination
 * -------------------------------------------------------------
 * Gaussian elimination is a method for solving systems of 
 * linear equations. The algorithm transforms the system's 
 * augmented matrix into an upper triangular form (row echelon 
 * form) through a series of row operations, which simplifies 
 * solving for the unknowns.
 *
 * Steps:
 * 1. Forward Elimination: 
 *    - Convert the matrix into an upper triangular form by 
 *      eliminating the entries below the main diagonal.
 *    - Use row operations such as:
 *        A[k][j] = A[k][j] - (A[k][i] / A[i][i]) * A[i][j]
 *        b[k] = b[k] - (A[k][i] / A[i][i]) * b[i]
 *      This makes the elements below the pivot element (on the 
 *      diagonal) equal to zero.
 *
 * 2. Back Substitution:
 *    - Once the matrix is in upper triangular form, start from 
 *      the last row and solve for the unknowns by substituting 
 *      the values of already solved variables.
 *    - Use the equation:
 *        x[i] = (b[i] - Σ(A[i][j] * x[j])) / A[i][i]  for j > i
 *      This allows us to solve for x starting from the bottom.
 *
 * Applications:
 * - Gaussian elimination is commonly used in linear algebra, 
 *   engineering, physics, computer science, and more.
 * - It provides a systematic way of solving equations for 
 *   unknowns in matrix form.
 *
 * Time Complexity: O(n^3), where n is the number of equations.
 ***************************************************************/

    int n = A.size();  // Get the number of equations/rows in the matrix

    // Perform forward elimination
    for (int i = 0; i < n; ++i) {
        // Partial pivoting to improve numerical stability
        for (int k = i + 1; k < n; ++k) {
            // Calculate the elimination factor: factor = A[k][i] / A[i][i]
            double factor = A[k][i] / A[i][i];

            // Update row k: A[k][j] -= factor * A[i][j]
            for (int j = i; j < n; ++j) {
                A[k][j] -= factor * A[i][j];  // ASCII: A[k][j] = A[k][j] - (factor * A[i][j])
            }

            // Update the result vector b: b[k] -= factor * b[i]
            b[k] -= factor * b[i];  // ASCII: b[k] = b[k] - (factor * b[i])
        }
    }

    // Back substitution to solve for x
    std::vector<double> x(n);  // Solution vector x of size n
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i];  // Initialize x[i] with b[i]

        // Subtract already solved variables from the equation
        for (int j = i + 1; j < n; ++j) {
            x[i] -= A[i][j] * x[j];  // ASCII: x[i] = x[i] - (A[i][j] * x[j])
        }

        // Divide by the diagonal element to solve for x[i]: x[i] /= A[i][i]
        x[i] /= A[i][i];  // ASCII: x[i] = x[i] / A[i][i]
    }

    return x;  // Return the solution vector

    /***************************************************************
 *                     Gaussian Elimination
 * -------------------------------------------------------------
 * Visual representation:
 *
 * Step 1: System of linear equations in matrix form (Ax = b):
 *
 *  [ A11  A12  A13 | b1 ]    -> Matrix A and vector b combined
 *  [ A21  A22  A23 | b2 ]    -> Each row represents an equation
 *  [ A31  A32  A33 | b3 ]
 *
 * Step 2: Forward Elimination:
 *         - Eliminate entries below the diagonal (A21, A31, A32):
 *
 *  [ A11  A12  A13 | b1 ]
 *  [  0   A22' A23'| b2' ]   -> A21 is eliminated by row operations
 *  [  0    0  A33' | b3' ]   -> A31 and A32 are eliminated by row operations
 *
 *         - Now we have an upper triangular matrix (row echelon form).
 *
 * Step 3: Back Substitution:
 *         - Solve for x3, x2, x1 by substitution:
 *
 *  x3 = b3' / A33'                -> Solve last equation first
 *  x2 = (b2' - A23'*x3) / A22'    -> Then solve for x2
 *  x1 = (b1 - A12*x2 - A13*x3) / A11 -> Finally solve for x1
 *
 * -------------------------------------------------------------
 * Example:
 * 
 * System of equations:
 *  2x1 -  x2 +  x3 =  3
 *   x1 + 3x2 + 2x3 = 13
 *   x1 -  x2 + 2x3 =  2
 *
 * Matrix representation (A | b):
 *  [  2  -1   1 |  3 ]
 *  [  1   3   2 | 13 ]
 *  [  1  -1   2 |  2 ]
 *
 * After forward elimination (upper triangular form):
 *  [  2  -1   1  |  3   ]
 *  [  0  3.5 1.5 | 11.5 ]
 *  [  0   0   2  |  2   ]
 *
 * Back substitution:
 *  x3 =  2 / 2 = 1
 *  x2 = (11.5 - 1.5*1) / 3.5 ≈ 3
 *  x1 = (3 - (-1)*3 - 1*1) / 2 ≈ 1
 *
 * Solution: x1 = 1, x2 = 3, x3 = 1
 ***************************************************************/
}

int main() {
    // Define a 3x3 matrix A (coefficients)
    std::vector<std::vector<double>> A = {
        {2.0, -1.0, 1.0},  // Row 1: 2x1 - x2 + x3 = 3
        {1.0, 3.0, 2.0},   // Row 2: x1 + 3x2 + 2x3 = 13
        {1.0, -1.0, 2.0}   // Row 3: x1 - x2 + 2x3 = 2
    };

    // Define vector b (results)
    std::vector<double> b = {3.0, 13.0, 2.0};  // The right-hand side of the equations

    // Solve the system Ax = b using Gaussian elimination
    std::vector<double> x = gaussian_elimination(A, b);

    // Display the solution vector x
    std::cout << "Solution vector x:\n";
    for (double xi : x) {
        std::cout << xi << " ";  // Print each solution value
    }
    std::cout << std::endl;

    return 0;
}

