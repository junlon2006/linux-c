#include <stdio.h>
#include "malloc_hook.h"

void* malloc(size_t size) {
  void *caller = __builtin_return_address(0);
  extern void* __libc_malloc(size_t size);
  return __libc_malloc(size);
}

void free(void *addr) {
  void *caller = __builtin_return_address(0);
  extern void __libc_free(void *addr);
  __libc_free(addr);
}