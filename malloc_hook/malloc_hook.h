#ifdef LINUX_C_MALLOC_HOOK_MALLOC_HOOK_H_
#define LINUX_C_MALLOC_HOOK_MALLOC_HOOK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void* malloc(size_t size);
void free(void *addr);

#ifdef __cplusplus
}
#endif

#endif // LINUX_C_MALLOC_HOOK_MALLOC_HOOK_H_
