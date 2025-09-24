#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#define __min_size (1 << 10)
#define __max_size (1 << 30)
#define __iterations 10000000
#define __cache_line_size 64
#define __page_size 4096

static inline uint64_t rdtsc(){
  unsigned int lo, hi;
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main(){

  srand(time(NULL));
  
  for(size_t size = __min_size; size <= __max_size; size *= 2){
    size_t elements = size / sizeof(uintptr_t);
    uintptr_t* memory = (uintptr_t*)malloc(size);
    if(memory == NULL){
      fprintf(stderr, "failed to allocate memory %zu, for %zu elements\n", size, elements);
      return -1;
    }


    for(size_t i=0; i<elements-1; i++){
      size_t j = i + rand() % (elements -i);
      memory[i] = (uintptr_t)(memory + j);
    }
    memory[elements-1] = (uintptr_t)memory;

    uint64_t start = rdtsc();
    volatile uintptr_t ptr = (uintptr_t)memory;
    for (int i = 0; i < __iterations; i++) {
      ptr = *(uintptr_t*)ptr;
    }

    uint64_t end = rdtsc();
    uint64_t cycles = end - start;
    double cycles_per_access = (double)cycles / __iterations;

    printf("Size: %8zu bytes | Avg. cycles/access: %.2f\n", 
           size, cycles_per_access);
        
    free(memory);
  }


  return 0;
}
