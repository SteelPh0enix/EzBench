#include <iostream>
#include "EzBench.hpp"

unsigned long long f() {
  unsigned long long x = 0;
  for (auto i = 1ull; i < 100000000ull; i *= 2) x += i;
  return x;
}

int main() {
  auto result = EzBench::run<std::nano>(f, 1000);

  std::cout << "Function is running approximately " << result
            << EzBench::getTimeUnit<std::nano>() << '\n';
}
