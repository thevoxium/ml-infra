// thread can not be copied, it can be moved
#include <iostream>
#include <thread>

void func1() { std::cout << "func1 running" << std::endl; }

void func2(int x) { std::cout << "func2 running with " << x << std::endl; }

int main() {
  std::thread t1{func1};
  std::thread t2 = std::move(t1);

  t2.join();

  std::thread t3 = std::thread{func2, 42};
  t3.join();
  return 0;
}
