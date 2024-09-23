#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

// Grid size and time step
const int grid_size = 100; // Size of 2D grid for simulation
const double dt = 0.01;    // Time step (small for accuracy)
const double dx = 0.1;     // Grid spacing

// Electric and magnetic fields (2D grid)
std::vector<std::vector<double>> E(grid_size, std::vector<double>(grid_size, 0.0)); // Electric field
std::vector<std::vector<double>> B(grid_size, std::vector<double>(grid_size, 0.0)); // Magnetic field

std::mutex field_mutex; // Mutex to ensure safe multithreading

// Function to update electric field using finite-difference equations
void update_electric_field(double dt, double dx) {
    std::lock_guard<std::mutex> guard(field_mutex); // Ensure thread-safe access
    for (int i = 1; i < grid_size - 1; ++i) {
        for (int j = 1; j < grid_size - 1; ++j) {
            // Simplified update equation: change in E depends on B
            E[i][j] += dt * (B[i+1][j] - B[i][j]) / dx;
        }
    }
}

// Function to update magnetic field using finite-difference equations
void update_magnetic_field(double dt, double dx) {
    std::lock_guard<std::mutex> guard(field_mutex); // Ensure thread-safe access
    for (int i = 1; i < grid_size - 1; ++i) {
        for (int j = 1; j < grid_size - 1; ++j) {
            // Simplified update equation: change in B depends on E
            B[i][j] += dt * (E[i][j+1] - E[i][j]) / dx;
        }
    }
}

int main() {
    // Initialize chrono for performance measurement
    auto start_time = std::chrono::high_resolution_clock::now();

    // Threads for updating electric and magnetic fields
    std::thread electric_thread(update_electric_field, dt, dx);
    std::thread magnetic_thread(update_magnetic_field, dt, dx);

    // Join threads to ensure both complete before proceeding
    electric_thread.join();
    magnetic_thread.join();

    // End time for performance measurement
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    std::cout << "Simulation completed in " << elapsed_time.count() << " seconds.\n";

    return 0;
}
