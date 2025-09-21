
#include <chrono>
#include <iostream>
#include <vector>

// Naive prime checker (slow on purpose)
bool isPrime(int n) {
  if (n <= 1)
    return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0)
      return false;
  }
  return true;
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  int limit = 1000000; // Change this to make it heavier
  std::vector<int> primes;

  for (int i = 2; i < limit; i++) {
    if (isPrime(i)) {
      primes.push_back(i);
    }
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;

  std::cout << "Found " << primes.size() << " primes up to " << limit << " in "
            << diff.count() << " seconds.\n";

  return 0;
}
