#pragma once
#include <chrono>

namespace EzBench {

template <typename T>
constexpr const char* getTimeUnit() {
  if (typeid(T) == typeid(std::milli))
    return "ms";
  else if (typeid(T) == typeid(std::micro))
    return "us";
  else if (typeid(T) == typeid(std::nano))
    return "ns";

  return "";
}

template <typename TimeT, typename F>
double run(F f, unsigned runs) {
  auto time = std::chrono::duration<double, TimeT>{};
  for (unsigned i = 0; i < runs; i++) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    time += end - start;
  }

  return time.count() / runs;
}

};  // namespace EzBench
