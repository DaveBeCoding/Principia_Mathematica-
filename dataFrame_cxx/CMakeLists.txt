# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(DataFrameExample)

# Set C++ standard to C++17 for std::variant support
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the Eigen3 package
find_package(Eigen3 REQUIRED)

# Add the executable target with the source file
add_executable(dataFrames dataFrame.cxx)

# Link Eigen3 to the target
target_link_libraries(dataFrames Eigen3::Eigen)
