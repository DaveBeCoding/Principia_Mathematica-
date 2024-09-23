# Minimum CMake version required
cmake_minimum_required(VERSION 3.14)

# Project name and language
project(FDTD_Simulation LANGUAGES CXX)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the executable target
add_executable(FDTD_Simulation main.cxx)

# Include directories (if any headers are separate, include them here)
# include_directories(include)

# Find Threads package (for multithreading)
find_package(Threads REQUIRED)

# Link libraries (e.g., Threads)
target_link_libraries(FDTD_Simulation PRIVATE Threads::Threads)

# Add compiler options for warnings and optimization
target_compile_options(FDTD_Simulation PRIVATE -Wall -Wextra -O2)

# Add definitions or macros (optional)
# add_definitions(-DEXAMPLE_MACRO)

# Output executable in the build directory
set_target_properties(FDTD_Simulation PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Message to display at the end of the configuration
message("CMake configuration complete! Build the project using 'make'.")
