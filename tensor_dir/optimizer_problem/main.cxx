/*

             Portfolio Optimization in Finance
---------------------------------------------------
The goal is to allocate investments across assets
to minimize risk while achieving a desired return.

Key Concepts:
1. Covariance Matrix (V)
2. Weight Vector (w)
3. Expected Return Vector (R)

We will break down each of these and how to calculate
them step by step.


Covariance Matrix represents risk (variance & covariance).

- Diagonal Elements: Variance of individual assets (risk)
- Off-Diagonal Elements: Covariance between pairs of assets
  (how assets move together)

Example Matrix `V`:
  [ 0.1  0.05  0.02 ]
  [ 0.05 0.2   0.03 ]
  [ 0.02 0.03  0.15 ]

Explanation:
  - V[0][0] = 0.1  -> Variance of Asset 1
  - V[1][1] = 0.2  -> Variance of Asset 2
  - V[2][2] = 0.15 -> Variance of Asset 3
  - V[0][1] = 0.05 -> Covariance between Asset 1 & 2
*/



#include <iostream>
#include <Eigen/Dense>

int main() {
    // Covariance matrix V (3 assets)
    Eigen::Matrix3d V;
    V << 0.1, 0.05, 0.02,
         0.05, 0.2, 0.03,
         0.02, 0.03, 0.15;

    // Expected return vector R
    Eigen::Vector3d R;
    R << 0.1, 0.15, 0.12;

    // Weight vector w
    Eigen::Vector3d w;
    w << 0.4, 0.4, 0.2;

    // Calculate expected return of the portfolio
    double portfolio_return = R.dot(w);  // R^T * w

    // Calculate portfolio variance (risk)
    double portfolio_variance = w.transpose() * V * w;  // w^T * V * w

    std::cout << "Expected Portfolio Return: " << portfolio_return << std::endl;
    std::cout << "Portfolio Variance (Risk): " << portfolio_variance << std::endl;

    return 0;
}

/*

        [  Var(X)    Cov(X, Y)  Cov(X, Z)  ]
    V = [ Cov(Y, X)  Var(Y)     Cov(Y, Z)  ]
        [ Cov(Z, X)  Cov(Z, Y)  Var(Z)     ]

*/
