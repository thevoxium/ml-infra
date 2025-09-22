#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  size_t n = 8192;
  float *matrix = calloc(n * n, sizeof(float));
  if (matrix == NULL) {
    return -1;
  }
  printf("row major \n");
  float sum = 0;
  for (size_t r = 0; r < n; ++r) {
    for (size_t c = 0; c < n; ++c) {
      matrix[r*n+c] = r*n+c;
    }
  }
  return 0;
}
