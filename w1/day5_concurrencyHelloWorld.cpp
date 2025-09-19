#include <iostream>
#include <thread>

void hello() { std::cout << "Hello threading" << std::endl; }

int main() {
  std::thread t(hello);
  t.join();
  return 0;
}
