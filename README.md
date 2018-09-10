# EzBench
Extremely simple and easy, header-only microlibrary for function benchmarking

Also, kinda shitty, but it's written in 10 minutes for a friend, and i thought it might be an "OK-tier" idea to put this here

Anyway, enjoy. Maybe i'll do something with this later, when i'll have *free time*

## Example, literally copy-pasted from `main.cpp` because i'm too lazy to do anything else right now

```cpp
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
```
