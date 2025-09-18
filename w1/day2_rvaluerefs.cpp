#include <cstddef>
#include <cstring>
#include <utility>

class simple_string {
private:
  char *data;
  size_t size;

public:
  simple_string(const char *str = "") {
    size = strlen(str);
    data = new char[size + 1];
    strcpy(data, str);
  }
  ~simple_string() {
    if (data != nullptr) {
      delete[] data;
    }
  }

  simple_string(const simple_string &other) = delete;
  simple_string &operator=(const simple_string &other) = delete;

  simple_string(simple_string &&other) noexcept {
    if (this != &other) {
      data = std::exchange(other.data, nullptr);
      size = std::exchange(other.size, 0);
    }
  }
  simple_string &operator=(simple_string &&other) = delete;
};

int main() {
  simple_string s1("Hello");
  simple_string s2(std::move(s1));
  simple_string s3("World");
  simple_string s4 = std::move(s3);
  return 0;
}
