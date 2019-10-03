#include <fstream>
#include <iostream>
#include "EzBench.hpp"

constexpr char const* const TestString{
    "This is a test string! Probably long enough to take a moment to write, "
    "but i don't know exactly, so i guess i have to make it longer by writing "
    "complete nonsense. Also, i think i should put some lorem ipsum there "
    "instead.\n"};

void writeTextToFile(std::string const& text,
                     std::fstream& stream,
                     bool flush = false) {
  stream << text;
  if (flush) {
    stream.flush();
  }
}

int main() {
  std::fstream testOutput("test.txt", std::ios::out);
  if (!testOutput.is_open()) {
    std::cout << "Test failed, cannot open file 'test.txt'!\n";
    return 1;
  }

  auto resultNoFlush = EzBench::run<std::micro>(
      [&]() { writeTextToFile(TestString, testOutput, false); }, 10000);

  auto resultWithFlush = EzBench::run<std::micro>(
      [&]() { writeTextToFile(TestString, testOutput, true); }, 10000);

  std::cout << "Writing text to file:\n"
            << "Without flushing: " << resultNoFlush.mean
            << "us (standard deviation: " << resultNoFlush.stdDev << "us)\n"
            << "With flushing: " << resultWithFlush.mean
            << "us (standard deviation " << resultWithFlush.stdDev << "us)\n";
}
