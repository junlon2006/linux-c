#include <stdlib.h>
#include <stdio.h>

extern size_t alloc_size;

int main() {
  char *p = malloc(1024);
  printf("alloc_szie=%lu\n", alloc_size);
  return 0;
}
