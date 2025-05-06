#include <vector>
#include <chrono>
#include <random>
#include <iostream>

int fusion_serial() {
    const size_t N = 50'000'000;
    const float alpha = 0.7f;

    // Allocate & generate synthetic data
    std::vector<float> lidar(N), camera(N), fused(N);
    std::mt19937_64 rng(0);
    std::uniform_real_distribution<float> dist(0.0f, 100.0f);
    for (size_t i = 0; i < N; ++i) {
        lidar[i]  = dist(rng);
        camera[i] = dist(rng);
    }

    // Serial fusion benchmark
    auto t0 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        fused[i] = alpha * lidar[i] + (1.0f - alpha) * camera[i];
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dt = t1 - t0;
    std::cout << dt.count() << std::endl;  // only print time in seconds
    return 0;
}
