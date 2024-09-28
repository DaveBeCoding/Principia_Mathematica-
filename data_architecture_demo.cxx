#include <iostream>
#include <vector>
#include <string>

// Struct: Lightweight data structure for holding related data.
struct DataPoint {
    int id;
    double value;
    std::string label;

    // Constructor for initializing data members.
    DataPoint(int id, double value, const std::string& label) 
        : id(id), value(value), label(label) {}
};

// Class: Abstracts functionality and encapsulates data.
class DataProcessor {
public:
    // Constructor for initialization
    DataProcessor() { /* Initialization code */ }

    // Public Interface (methods exposed to other parts of the code)
    void addDataPoint(const DataPoint& dp) {
        data_.push_back(dp);
    }

    // Pure virtual function (to be implemented by derived classes)
    virtual void process() = 0;

protected:
    std::vector<DataPoint> data_; // Protected data member for derived class access
};

// Inheritance: Specialized type of DataProcessor
class StatisticalAnalyzer : public DataProcessor {
public:
    // Override process function with specific functionality
    void process() override {
        // Perform some statistical analysis on `data_`
    }
};

// Composition: Using objects to build more complex behavior
class DataFrame {
public:
    DataFrame() = default;

    // Add data column using composition
    void addColumn(const std::vector<double>& column, const std::string& name) {
        columns_.push_back(column);
        column_names_.push_back(name);
    }

private:
    std::vector<std::vector<double>> columns_;
    std::vector<std::string> column_names_;
};

// Template Class: For type flexibility (e.g., numerical operations on different types)
template <typename T>
class Calculator {
public:
    T add(const T& a, const T& b) {
        return a + b;
    }
};

// Singleton Design Pattern: Ensures only one instance exists
class Logger {
public:
    // Static method to get the instance of Logger
    static Logger& getInstance() {
        static Logger instance; // Guaranteed to be destroyed, thread-safe in C++11
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "[LOG]: " << message << std::endl;
    }

private:
    // Private constructor to prevent multiple instances
    Logger() {}
};

// Main Program: Tying everything together
int main() {
    // Example of creating a DataPoint struct
    DataPoint dp1(1, 42.5, "Sample Label");

    // Example of using DataProcessor polymorphism
    StatisticalAnalyzer analyzer;
    analyzer.addDataPoint(dp1);
    analyzer.process();

    // Using DataFrame composition to store data
    DataFrame df;
    df.addColumn({1.0, 2.0, 3.0}, "Column1");

    // Using template class Calculator
    Calculator<int> intCalc;
    std::cout << "Sum: " << intCalc.add(3, 5) << std::endl;

    // Using Singleton Logger
    Logger::getInstance().log("This is a singleton logger example.");

    return 0;
}
