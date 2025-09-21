#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  size_t n = 10;
  float *matrix = calloc(n * n, sizeof(float));
  if (matrix == NULL) {
    return -1;
  }
  for (size_t r = 0; r < n; ++r) {
    for (size_t c = 0; c < n; ++c) {
      printf("%f", matrix[r * n + c]);
    }
    printf("\n");
  }
  return 0;
}
