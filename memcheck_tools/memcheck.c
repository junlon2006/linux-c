#include "memcheck.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAGICNUM             (0xabcdef)
#define HEAP_ALLOC_SIZE_MAX  (1 << 20)

typedef struct {
    unsigned int magicNum;
    unsigned int sequeceId;
    unsigned int customAllocLen;
} MemcheckHeader;

/* 采用CAS，提升高并发下的竞争性能 */
#define LOCK(lkp) do{  \
    while(!__sync_bool_compare_and_swap(lkp, 0, 1)){    \
        usleep(1000); \
    }   \
} while(0)

#define UNLOCK(lkp) do{    \
    *(lkp) = 0;  \
} while(0)

static int __used_heap_size = 0; /* 记录一共malloc了多少内存 */
static int __used_heap_cnt = 0; /* 记录一共malloc了多少次 */
static int __lock = 0;
static unsigned int __sequence_id = 0;

static void* __malloc_status(void *args) {
    while (1) {
        usleep(1000 * 1000 * 2);

        LOCK(&__lock);
        printf("%s%d: cnt=%d, size=%d\n", __FUNCTION__, __LINE__, __used_heap_cnt, __used_heap_size);
        UNLOCK(&__lock);
    }

    return NULL;
}

static void __init_memcheck() {
    static char init = 0;
    if (0 == init) {
        init = 1;
        pthread_t pid;
        pthread_create(&pid, NULL, __malloc_status, NULL);
        pthread_detach(pid);
    }
}

static unsigned int __get_align4_size(unsigned int size) {
    return ((size + (4 - 1)) & ~(4 - 1));
}

void* uni_memcheck_malloc(const char *file, const char *function, int line, unsigned int len) {
    char *p;

    __init_memcheck();

    len += sizeof(MemcheckHeader);
    len = __get_align4_size(len);

    if (NULL == (p = malloc(len))) {
        printf("[ERROR] %s:%s:%d: alloc memory failed\n", file, function, line);
        return NULL;
    }

    MemcheckHeader *header = (MemcheckHeader *)p;
    header->customAllocLen = len;
    header->magicNum = MAGICNUM;
    header->sequeceId = __sequence_id++;

    LOCK(&__lock);
    __used_heap_cnt++;
    __used_heap_size += len;
    UNLOCK(&__lock);

    if (len > HEAP_ALLOC_SIZE_MAX) {
        printf("[ERROR] %s:%s:%d: alloc length[%u] invalid\n", file, function, line, len);
    }

    return p + sizeof(MemcheckHeader);
}

void uni_memcheck_free(const char *file, const char *function, int line, void *address) {
    if (NULL == address) {
        printf("[ERROR] %s:%s:%d: null pointer error\n", file, function, line);
        return;
    }

    char *p = (char *)address;
    MemcheckHeader *header = (MemcheckHeader *)(p - sizeof(MemcheckHeader));
    if (header->magicNum != MAGICNUM) {
        printf("[ERROR] %s:%s:%d: magic[%0x][%0x] invalid\n", file, function, line, header->magicNum, MAGICNUM);
        return;
    }
    if (header->sequeceId > __sequence_id) {
        printf("[ERROR] %s:%s:%d: sequeceId[%u][%u] invalid\n", file, function, line, header->sequeceId, __sequence_id);
        return;
    }
    if (header->customAllocLen <= 0 || header->customAllocLen > HEAP_ALLOC_SIZE_MAX) {
        printf("[ERROR] %s:%s:%d: allocSize[%u][%u] invalid\n", file, function, line, header->customAllocLen, HEAP_ALLOC_SIZE_MAX);
        return;
    }

    LOCK(&__lock);
    __used_heap_cnt--;
    __used_heap_size -= header->customAllocLen;
    UNLOCK(&__lock);

    free(p - sizeof(MemcheckHeader));
}

#define ALLOC_SIZE  (1024 * 1024 - 100)
int main() {
    int count = 0;

    while (1) {
        char *buf = (char *)uni_malloc(ALLOC_SIZE);
        count++;
        printf("alloc[%d][%u]\n", ALLOC_SIZE * count, __get_align4_size((ALLOC_SIZE + sizeof(MemcheckHeader))) * count);
        uni_free(buf);
        usleep(1000 * 1000 * 1);
    }

    return 0;
}