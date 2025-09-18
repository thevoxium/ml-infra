#include <iostream>
#include <unistd.h>
#include <utility>

struct FileHandler {
  int fd{-1};
  explicit FileHandler(int _fd) : fd(_fd) {}
  FileHandler(const FileHandler &) = delete;
  FileHandler &operator=(const FileHandler &) = delete;
  FileHandler(FileHandler &&other) noexcept : fd(std::exchange(other.fd, -1)) {}
  FileHandler &operator=(FileHandler &&other) noexcept {
    if (this != &other) {
      fd = std::exchange(other.fd, -1);
    }
    return *this;
  }
};

void printFileHandler(const FileHandler &fh) { std::cout << fh.fd << "\n"; }
int openFile(const char *filename) {
  std::cout << "Opening file: " << filename << "\n";
  return 3;
}
int main() {
  FileHandler fh1(openFile("test.txt"));
  FileHandler fh4 = std::move(fh1);
  FileHandler fh5(openFile("another.txt"));
  fh5 = std::move(fh4);
  {
    FileHandler fh6(openFile("temp.txt"));
    std::cout << "fh6 will be automatically closed when scope ends\n";
  }
  return 0;
}
