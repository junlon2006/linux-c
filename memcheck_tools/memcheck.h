#ifndef _MEMCHECK_H_
#define _MEMCHECK_H_

#ifdef __cplusplus
extern "C" {
#endif

#define uni_malloc(address)   uni_memcheck_malloc(__FILE__, __FUNCTION__, __LINE__, address)
#define uni_free(address) uni_memcheck_free(__FILE__, __FUNCTION__, __LINE__, address)

extern void* uni_memcheck_malloc(const char *file, const char *function, int line, unsigned int len);
extern void uni_memcheck_free(const char *file, const char *function, int line, void *address);

#ifdef __cplusplus
}
#endif
#endif