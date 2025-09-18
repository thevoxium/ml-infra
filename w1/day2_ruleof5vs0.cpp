
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

class managed_array {
private:
  int *m_data;
  size_t m_size;

public:
  managed_array(size_t size = 0)
      : m_data((size > 0) ? new int[size] : nullptr), m_size(size) {}

  ~managed_array() { delete[] m_data; }

  managed_array(const managed_array &other)
      : m_data((other.m_size > 0) ? new int[other.m_size] : nullptr),
        m_size(other.m_size) {
    std::copy(other.m_data, other.m_data + other.m_size, m_data);
  }

  managed_array &operator=(const managed_array &other) {
    if (this != &other) {
      managed_array temp(other);
      std::swap(*this, temp);
    }
    return *this;
  }

  managed_array(managed_array &&other) noexcept
      : m_data(std::exchange(other.m_data, nullptr)),
        m_size(std::exchange(other.m_size, 0)) {}

  managed_array &operator=(managed_array &&other) noexcept {
    if (this != &other) {
      delete[] m_data;
      m_data = std::exchange(other.m_data, nullptr);
      m_size = std::exchange(other.m_size, 0);
    }
    return *this;
  }
};

class managed_array_new {
private:
  std::vector<int> m_data;

public:
  managed_array_new(size_t size = 0) : m_data(std::vector<int>(size)) {}
};

int main() {
  std::cout << "Rule of 5 vs 0" << std::endl;
  return 0;
}
