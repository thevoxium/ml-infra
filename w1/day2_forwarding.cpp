#include <iostream>
#include <utility>

void process(int &value) {
  std::cout << "process(lvalue): " << value << std::endl;
}

void process(int &&value) {
  std::cout << "process(rvalue): " << value << std::endl;
}

template <typename T> void relay(T &&arg) { process(std::forward<T>(arg)); }

int main() {
  int x = 10;
  relay(x);
  relay(20);
  relay(std::move(x));
  return 0;
}
