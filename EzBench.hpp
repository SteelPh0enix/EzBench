#pragma once
#include <numeric>
#include <chrono>
#include <cmath>
#include <vector>

namespace EzBench {
struct BenchResult {
  double mean;
  double stdDev;
};

namespace {
  double squareDeviationSum(std::vector<double> const& data, double mean) {
    double sum{0.};
    for (auto x : data) {
      sum += std::pow(x - mean, 2);
    }
    return sum;
  }

  double standardDeviation(std::vector<double> const& data, double mean) {
    return std::sqrt(squareDeviationSum(data, mean) /
                     static_cast<double>(data.size()));
  }

  BenchResult calculateResult(std::vector<double> const& times) {
    BenchResult result{};

    result.mean = std::accumulate(times.begin(), times.end(), 0.) /
                  static_cast<double>(times.size());
    result.stdDev = standardDeviation(times, result.mean);

    return result;
  }
}

template <typename TimeT, typename F>
BenchResult run(F f, unsigned runs) {
  auto time = std::chrono::duration<double, TimeT>{};
  std::vector<double> times(runs);

  for (unsigned i = 0; i < runs; i++) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    times[i] = (end - start).count();
  }

  return calculateResult(times);
}

template <typename TimeT, typename BenchF, typename CleanupF>
BenchResult run(BenchF f, CleanupF cleanup, unsigned runs) {
  auto time = std::chrono::duration<double, TimeT>{};
  std::vector<double> times(runs);

  for (unsigned i = 0; i < runs; i++) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    cleanup();
    times[i] = (end - start).count();
  }

  return calculateResult(times);
}

}  // namespace EzBench
