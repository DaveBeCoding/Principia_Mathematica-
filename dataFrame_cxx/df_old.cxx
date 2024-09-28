/*
   **************************************************************
   *                 Portfolio DataFrame Overview               *
   **************************************************************
   * The aim is to demonstrate how to manage mixed data types   *
   * and perform mathematical operations on numeric data using  *
   * C++ libraries like `std::variant` for flexible data and    *
   * `Eigen` for matrix calculations. This example can be used  *
   * in financial modeling, data science, and analytics.        *
   **************************************************************
*/

/**************************************************************
*                   STRUCTURE OF THE PROGRAM                  *
***************************************************************
* 1. Creating a flexible data frame to handle multiple types. *
* 2. Adding data and printing the DataFrame.                  *
* 3. Extracting numeric data for mathematical operations.     *
* 4. Using Eigen for vector and matrix calculations.          *
**************************************************************/

#include <iostream>
#include <variant>  // For mixed data types
#include <vector>
#include <string>
#include <Eigen/Dense>  // For matrix operations
#include <stdexcept>    // For error handling

// Define a variant to hold various data types
using DataFrameElement = std::variant<int, double, char, std::string>;

// Define a column as a vector of variant elements
using DataFrameColumn = std::vector<DataFrameElement>;

// Define the DataFrame as a structure with columns and column names
struct DataFrame {
    std::vector<DataFrameColumn> columns;
    std::vector<std::string> column_names;
};

// Function to add a column to the DataFrame
void add_column(DataFrame& df, const std::string& name, const DataFrameColumn& column) {
    // Check column consistency
    if (!df.columns.empty() && df.columns[0].size() != column.size()) {
        throw std::invalid_argument("Column size does not match existing DataFrame row count.");
    }
    df.column_names.push_back(name);
    df.columns.push_back(column);
}

// Function to print the contents of the DataFrame
void print_dataframe(const DataFrame& df) {
    // Print column names
    for (const auto& name : df.column_names) {
        std::cout << name << "\t";
    }
    std::cout << std::endl;

    // Validate if DataFrame has columns
    if (df.columns.empty()) {
        std::cout << "DataFrame is empty!" << std::endl;
        return;
    }

    // Print each row of the DataFrame
    size_t row_count = df.columns[0].size();
    for (size_t i = 0; i < row_count; ++i) {
        for (const auto& column : df.columns) {
            std::visit([](auto&& val) { std::cout << val << "\t"; }, column[i]);
        }
        std::cout << std::endl;
    }
}

/**************************************************************
*           NUMERIC DATA OPERATIONS WITH EIGEN                *
**************************************************************/

// Utility function to verify if a column contains only numeric values
bool is_numeric_column(const DataFrameColumn& column) {
    return std::all_of(column.begin(), column.end(), [](const DataFrameElement& val) {
        return std::holds_alternative<int>(val) || std::holds_alternative<double>(val);
    });
}

// Extract numeric data (int or double) from a column to an Eigen vector
Eigen::VectorXd extract_numeric_column(const DataFrameColumn& column) {
    if (!is_numeric_column(column)) {
        throw std::invalid_argument("Column contains non-numeric values, cannot extract as numeric.");
    }

    Eigen::VectorXd result(column.size());
    for (size_t i = 0; i < column.size(); ++i) {
        std::visit([&result, i](auto&& val) {
            if constexpr (std::is_same_v<decltype(val), int> || std::is_same_v<decltype(val), double>) {
                result[i] = static_cast<double>(val);  // Safely convert int to double if necessary
            }
        }, column[i]);
    }
    return result;
}

// Combine numeric columns into a single Eigen matrix
Eigen::MatrixXd build_numeric_matrix(const DataFrame& df) {
    size_t num_rows = df.columns[0].size();
    std::vector<Eigen::VectorXd> numeric_columns;

    // Extract all numeric columns
    for (const auto& column : df.columns) {
        if (is_numeric_column(column)) {
            numeric_columns.push_back(extract_numeric_column(column));
        }
    }

    // Handle case when no numeric columns are found
    if (numeric_columns.empty()) {
        throw std::runtime_error("No numeric columns found in DataFrame.");
    }

    // Build an Eigen matrix from the extracted numeric vectors
    Eigen::MatrixXd matrix(num_rows, numeric_columns.size());
    for (size_t i = 0; i < numeric_columns.size(); ++i) {
        matrix.col(i) = numeric_columns[i];
    }

    return matrix;
}

// Function to calculate column means and covariance using Eigen
void analyze_data_frame(DataFrame& df) {
    Eigen::MatrixXd data_matrix = build_numeric_matrix(df);

    // Example: Calculate mean of each column
    Eigen::VectorXd column_means = data_matrix.colwise().mean();
    std::cout << "Column means:\n" << column_means << std::endl;

    // Example: Calculate covariance matrix
    Eigen::MatrixXd centered = data_matrix.rowwise() - column_means.transpose();
    Eigen::MatrixXd covariance_matrix = (centered.transpose() * centered) / double(data_matrix.rows() - 1);
    std::cout << "Covariance matrix:\n" << covariance_matrix << std::endl;

    /****************************************************
    * Covariance Matrix Formula:                        *
    *                                                   *
    *        [  Var(X)    Cov(X, Y)  Cov(X, Z)  ]       *
    *    V = [ Cov(Y, X)  Var(Y)     Cov(Y, Z)  ]       *
    *        [ Cov(Z, X)  Cov(Z, Y)  Var(Z)     ]       *
    *                                                   *
    ****************************************************/
}

/**************************************************************
*                         MAIN FUNCTION                       *
**************************************************************/

int main() {
    /*
        Initialize the DataFrame with mixed data types:
        ------------------------------------------------
        | Integers | Doubles | Chars | Strings          |
        ------------------------------------------------
        | 1        | 1.5     | A     | Alice            |
        | 2        | 2.5     | B     | Bob              |
        | 3        | 3.5     | C     | Charlie          |
        ------------------------------------------------
    */

    try {
        DataFrame df;

        // Create example columns
        DataFrameColumn int_col = {1, 2, 3};
        DataFrameColumn double_col = {1.5, 2.5, 3.5};
        DataFrameColumn char_col = {'A', 'B', 'C'};
        DataFrameColumn string_col = {"Alice", "Bob", "Charlie"};

        // Add columns to the DataFrame
        add_column(df, "Integers", int_col);
        add_column(df, "Doubles", double_col);
        add_column(df, "Chars", char_col);
        add_column(df, "Strings", string_col);

        // Print the DataFrame structure
        std::cout << "---------------- DataFrame ----------------\n";
        print_dataframe(df);
        std::cout << "-------------------------------------------\n";

        // Perform numeric data analysis
        std::cout << "\nAnalyzing numeric data in the DataFrame...\n";
        analyze_data_frame(df);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
