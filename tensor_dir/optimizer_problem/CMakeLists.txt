# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(EigenTestProject LANGUAGES CXX)

# Set C++ standard to 11 (or higher)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Eigen package
find_package(Eigen3 REQUIRED)

# Add the executable target
add_executable(eigen_test main.cxx)

# Link the Eigen include directories to the target
target_include_directories(eigen_test PRIVATE ${EIGEN3_INCLUDE_DIR})

# Include standard library path for AppleClang (on macOS)
target_include_directories(eigen_test PRIVATE /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1)

# If you want to set additional compile options or warnings, you can uncomment this line:
# target_compile_options(eigen_test PRIVATE -Wall -Wextra -pedantic)
