#include <memcheck.h>
#include <stdio.h>

size_t alloc_size = 0;

#define MEMCHECK_HEADER_LEN  (sizeof(size_t))

extern void *__libc_malloc(size_t size);
void* malloc(size_t size) {
  void *p = __libc_malloc(size + MEMCHECK_HEADER_LEN);
  *((size_t*)p) = size;
  alloc_size += size;
  return (void *)((char *)p + MEMCHECK_HEADER_LEN);
}

extern void __libc_free(void *ptr);
void free(void *ptr) {
  size_t *p = (size_t *)((char *)ptr - MEMCHECK_HEADER_LEN);
  alloc_size -= *p;
  __libc_free(p);
}
