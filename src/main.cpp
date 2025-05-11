#include <iostream>
#include <omp.h>
#include "sensor_fusion_serial.hpp"
#include "sensor_fusion_omp.hpp"

int main() {
    std::cout
        << "🔧 Sensor Fusion Benchmark\n"
        << "---------------------------\n"
        << "This program simulates high‑speed fusion of LiDAR\n"
        << "and camera data streams using both serial and\n"
        << "parallel (OpenMP) methods.\n\n";

    // Serial
    std::cout << "⏱ Running serial implementation...\n";
    double t_serial = fusion_serial();
    std::cout << "✅ Serial time: " << t_serial << " seconds\n\n";

    // OpenMP
    std::cout << "⚙️  Running OpenMP implementation...\n";
    double t_parallel = fusion_openmp();
    std::cout << "✅ OpenMP time (" << omp_get_max_threads()
              << " threads): " << t_parallel << " seconds\n\n";

    // Summary
    double speedup = t_serial / t_parallel;
    std::cout
        << "📊 Speedup (serial / parallel): " << speedup << "×\n\n"
        << "Benchmark complete.\n";
    return 0;
}
