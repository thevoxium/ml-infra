#include <cstddef>
#include <iostream>
#include <thread>
struct func {
  int &num;
  func(int &num_) : num(num_) {}
  void operator()() const {
    for (size_t j = 0; j < 10000000; ++j) {
      if (j % 100000) {
        std::cout << num << std::endl;
      }
    }
  }
};

void bug() {
  int num_local = 10;
  func f{num_local};
  std::thread t{f};
}
int main() {
  bug();
  return 0;
}
