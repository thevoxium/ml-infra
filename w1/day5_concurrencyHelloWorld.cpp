#include <iostream>
#include <thread>

int main() {
  std::thread t([] { std::cout << "Hello" << std::endl; });
  t.join();
  return 0;
}
