# High-Speed Sensor Fusion with Parallel Computing

## Welcome

This project benchmarks high-speed sensor fusion using synthetic LiDAR and camera data streams to simulate real-time data processing in autonomous systems. Two implementations are compared: a baseline serial version and a parallel OpenMP version, to analyze performance improvement through shared-memory parallelism.

## Problem Statement

Autonomous vehicles rely on data from multiple high-frequency sensors (e.g., LiDAR, cameras). This data must be fused quickly and accurately to make real-time decisions such as obstacle detection or path planning. Fusion generally involves weighted averaging of sensor data over time. With high-resolution sensors generating millions of data points per second, the fusion process becomes computationally intensive.

This project simulates that fusion process over 50 million data points, comparing a standard serial approach to an optimized OpenMP-parallelized version.

## Motivation for Parallelization

- Each fusion computation is independent (data-parallel).
- Multi-core processors allow fusion steps to run in parallel.
- Faster fusion means lower latency for safety-critical applications.
- OpenMP enables low-overhead parallelism on CPU-bound workloads with minimal code changes.

## Background: OpenMP & Parallelism

- OpenMP (Open Multi-Processing) is a widely-used API for parallel programming on shared-memory architectures (multi-core CPUs).
- The #pragma omp parallel for directive automatically distributes loop iterations across available threads.
- Modern CPUs may have 4–64 cores. Using OpenMP allows us to take full advantage of this hardware.
- We use compiler optimizations (-O3 -march=native -fopenmp) to further boost performance.

## Implementation Overview

**Serial Version** (`fusion_serial`)

- Generates random LiDAR and camera arrays of size 50M.
- Fuses them using a single-threaded for-loop.

**Parallel Version** (`fusion_openmp`)

- Same input and logic as serial.
- Uses `#pragma omp parallel` for to distribute fusion work across cores.