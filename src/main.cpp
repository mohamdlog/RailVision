#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <omp.h>

double fusion_serial(std::vector<float>& lidar, std::vector<float>& camera, std::vector<float>& fused, size_t N, float alpha) {
    auto t0 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        fused[i] = alpha * lidar[i] + (1.0f - alpha) * camera[i];
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Serial Time: " << dt.count() << " seconds" << std::endl;
    return dt.count();
}

double fusion_openmp(std::vector<float>& lidar, std::vector<float>& camera, std::vector<float>& fused, size_t N, float alpha) {
    auto t0 = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < N; ++i) {
        fused[i] = alpha * lidar[i] + (1.0f - alpha) * camera[i];
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << "Parallel (OpenMP) Time: " << dt.count() << " seconds" << std::endl;
    return dt.count();
}

int main() {
    std::cout << "Sensor Fusion Benchmark\n"
              << "---------------------------\n"
              << "This program simulates high-speed fusion of LiDAR\nand camera data streams using both serial and parallel methods.\n"
              << "It will now execute both versions, measure the execution time,\nand report the performance difference.\n";

    // Constants and data setup
    const size_t N = 50'000'000;
    const float alpha = 0.7f;

    std::vector<float> lidar(N), camera(N), fused(N);
    std::mt19937_64 rng(0);
    std::uniform_real_distribution<float> dist(0.0f, 100.0f);

    for (size_t i = 0; i < N; ++i) {
        lidar[i]  = dist(rng);
        camera[i] = dist(rng);
    }

    // Open file to save times
    std::ofstream outFile("execution_times.csv");
    outFile << "Threads,Time (seconds)\n";

    // Run serial implementation (1 thread)
    std::cout << "\nRunning serial implementation...\n";
    double serial_time = fusion_serial(lidar, camera, fused, N, alpha);
    outFile << "1," << serial_time << "\n";

    // Run parallel implementation with different thread counts (2, 4, 8, 16)
    std::cout << "\nRunning parallel implementations...\n";
    for (int num_threads = 2; num_threads <= 16; num_threads *= 2) {
        omp_set_num_threads(num_threads);
        std::cout << "\nRunning with " << num_threads << " threads...\n";
        double parallel_time = fusion_openmp(lidar, camera, fused, N, alpha);
        outFile << num_threads << "," << parallel_time << "\n";
    }

    outFile.close();

    // Run Python script for plotting
    const char* python_cmd = 
        "import pandas as pd; import matplotlib.pyplot as plt; "
        "plt.switch_backend('Agg'); "  // Use non-GUI backend
        "data = pd.read_csv('execution_times.csv'); "
        "data['Speedup'] = data['Time (seconds)'].iloc[0] / data['Time (seconds)']; "
        "plt.plot(data['Threads'], data['Speedup'], marker='o'); "
        "plt.xlabel('Number of Threads'); plt.ylabel('Speedup over Serial'); "
        "plt.title('OpenMP Speedup for Sensor Fusion'); plt.grid(True); "
        "plt.savefig('speedup_plot.png'); print('Plot saved to speedup_plot.png')";

    std::cout << "\nRunning Python script for visualization...\n";
    int status = system(("python3 -c \"" + std::string(python_cmd) + "\"").c_str());
    (void)status;  // Explicitly mark return value as unused

    return 0;
}