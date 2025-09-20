// thread can not be copied, it can be moved
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void print_thread_id() {
  std::cout << "thread id" << std::this_thread::get_id() << std::endl;
}

void func1() { std::cout << "func1 running" << std::endl; }

void func2(int x) { std::cout << "func2 running with " << x << std::endl; }

void func3(std::thread t) {
  if (t.joinable()) {
    print_thread_id();
    t.join();
  }
}

void some_work(int id) {
  std::cout << id << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main() {
  std::thread t1{func1};
  std::thread t2 = std::move(t1);

  t2.join();

  std::thread t3 = std::thread{func2, 42};
  t3.join();

  std::thread t4{func2, 42};
  func3(std::move(t4));

  const int num_threads = 5;
  std::vector<std::thread> threads;

  for (int i = 0; i < num_threads; ++i) {
    threads.emplace_back(some_work, i);
  }

  for (auto &t : threads) {
    t.join();
  }
  return 0;
}
