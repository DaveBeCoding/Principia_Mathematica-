/*
   **************************************************************
   *              Professional DataFrame with Eigen             *
   **************************************************************
   * This example shows how to create a DataFrame-like          *
   * structure in C++ that can handle mixed data types,         *
   * and perform a mathematical operation similar to a NumPy    *
   * operation in Python. We use `Eigen` for matrix operations  *
   * and `std::variant` for flexible data types.                *
   * Demonstrates safe type handling and clear data operations. *
   **************************************************************
*/

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
    // Ensure all columns have the same row count
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

    // Check if DataFrame is empty
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
*        EXTRACTING NUMERIC DATA FOR EIGEN OPERATIONS         *
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
            // Corrected: Ensure the extraction is properly casting numeric types
            if constexpr (std::is_same_v<decltype(val), int> || std::is_same_v<decltype(val), double>) {
                result[i] = static_cast<double>(val);  // Convert to double to ensure consistency
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

    if (numeric_columns.empty()) {
        throw std::runtime_error("No numeric columns found in DataFrame.");
    }

    // Create an Eigen matrix from the extracted numeric columns
    Eigen::MatrixXd matrix(num_rows, numeric_columns.size());
    for (size_t i = 0; i < numeric_columns.size(); ++i) {
        matrix.col(i) = numeric_columns[i];
    }

    return matrix;
}

// Function to perform element-wise multiplication on numeric columns
Eigen::MatrixXd elementwise_multiply(const DataFrame& df1, const DataFrame& df2) {
    // Build matrices from both DataFrames
    Eigen::MatrixXd matrix1 = build_numeric_matrix(df1);
    Eigen::MatrixXd matrix2 = build_numeric_matrix(df2);

    if (matrix1.rows() != matrix2.rows() || matrix1.cols() != matrix2.cols()) {
        throw std::invalid_argument("Matrices must have the same dimensions for element-wise multiplication.");
    }

    // Perform element-wise multiplication
    return matrix1.array() * matrix2.array();
}

/**************************************************************
*                         MAIN FUNCTION                       *
**************************************************************/

int main() {
    /*
        Initialize two DataFrames with numeric data types:
        ------------------------------------------------
        | Integers | Doubles |                        |
        ------------------------------------------------
        | 1        | 1.5     |                        |
        | 2        | 2.5     |                        |
        | 3        | 3.5     |                        |
        ------------------------------------------------
    */

    try {
        DataFrame df1;
        DataFrame df2;

        // Create columns for the first DataFrame
        DataFrameColumn int_col1 = {1, 2, 3};
        DataFrameColumn double_col1 = {1.5, 2.5, 3.5};

        // Create columns for the second DataFrame (same dimensions)
        DataFrameColumn int_col2 = {4, 5, 6};
        DataFrameColumn double_col2 = {2.0, 3.0, 4.0};

        // Add columns to DataFrames
        add_column(df1, "Integers", int_col1);
        add_column(df1, "Doubles", double_col1);

        add_column(df2, "Integers", int_col2);
        add_column(df2, "Doubles", double_col2);

        // Print both DataFrames
        std::cout << "---------------- DataFrame 1 ----------------\n";
        print_dataframe(df1);
        std::cout << "--------------------------------------------\n";

        std::cout << "\n---------------- DataFrame 2 ----------------\n";
        print_dataframe(df2);
        std::cout << "--------------------------------------------\n";

        // Perform an element-wise multiplication similar to NumPy
        std::cout << "\nPerforming element-wise multiplication...\n";
        Eigen::MatrixXd result_matrix = elementwise_multiply(df1, df2);

        // Output the result matrix
        std::cout << "Resulting Matrix after element-wise multiplication:\n" << result_matrix << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
