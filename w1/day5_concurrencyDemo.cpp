#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

// basic function, arguments are copied by default
void basic_func(int i, const std::string &s) {
  std::cout << i << " " << s << std::endl;
}

// modify string, needs ref
void modify_string(std::string &s) {
  s += "hello";
  std::cout << "[modify_string] inside thread: " << s << std::endl;
}

void dangling_pointer_demo() {
  char buffer[32];
  snprintf(buffer, 3, "42");
  std::thread t{basic_func, 2, std::string(buffer)};
  t.join();
}

// member function demo
class Worker {
public:
  void do_work(int n) { std::cout << n << std::endl; }
};

// thread ownership demo
void thread_ownership() {
  std::thread t1([] { std::cout << "Hello" << std::endl; });
  std::thread t2 = std::move(t1);
  t2.join();
}

int main() {
  std::thread t_basic(basic_func, 10, "hello");
  t_basic.join();

  std::string mystr = "Hello";
  // need to use std::ref when trying to change a local var
  std::thread t_ref(modify_string, std::ref(mystr));
  t_ref.join();
  std::cout << "[main] mystr after thread: " << mystr << std::endl;

  dangling_pointer_demo();

  Worker w;
  std::thread t_member(&Worker::do_work, &w, 5);
  t_member.join();

  thread_ownership();

  return 0;
}
