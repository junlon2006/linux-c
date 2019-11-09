#ifndef JUNLON_MEMCHECK_H_
#define JUNLON_MEMCHECK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void *malloc(size_t size);
void free(void *ptr);

#ifdef __cplusplus
}
#endif
#endif
