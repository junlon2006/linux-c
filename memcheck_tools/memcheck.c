#include "memcheck.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define MAGICNUM             (0x7fabcdef)
#define HEAP_ALLOC_SIZE_MAX  (1 << 20)

typedef struct list_head_ {
  struct list_head_ *next, *prev;
} list_head_;

typedef struct {
    unsigned int magicNum;
    unsigned int sequeceId;
    unsigned int customAllocLen;
    list_head_   link;
} MemcheckHeader;

typedef struct {
  unsigned int magicNum;
} MemcheckTail;

#define list_entry_(ptr, type, member) ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
#define __LIST_ADD_(entry,before,after) {list_head_ *new_= (entry), *prev = (before), *next = (after); (next)->prev = (new_); (new_)->next = (next); (new_)->prev = (prev); (prev)->next = (new_);}
#define list_init_(entry) do {(entry)->next = (entry); (entry)->prev = (entry);} while(0)
#define list_add_(entry,base) do { __LIST_ADD_((entry),(base),(base)->next); } while(0)
#define list_for_each_entry_(p, head, type, member) for (p = list_entry_((head)->next, type, member); (list_head_ *)&p->member != (head); p = list_entry_(p->member.next, type, member))
#define list_del_(entry) do { (entry)->prev->next = (entry)->next; (entry)->next->prev = (entry)->prev; (entry)->next = (entry)->prev = (entry);} while(0)

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
static list_head_ __heap_alloc_list;

static void* __malloc_status(void *args) {
    MemcheckHeader *header;
    MemcheckTail *tail;
    char *p;
    while (1) {
        usleep(1000 * 1000 * 2);

        LOCK(&__lock);
        printf("%s%d: cnt=%d, size=%d\n", __FUNCTION__, __LINE__, __used_heap_cnt, __used_heap_size);

         list_for_each_entry_(header, &__heap_alloc_list, MemcheckHeader, link) {
            p = (char *)header;
            tail = (MemcheckTail *)(p + (sizeof(MemcheckHeader) + header->customAllocLen));

            if (header->magicNum != MAGICNUM) {
                printf("[ERROR] %s:%s:%d: magic[%0x][%0x] [h=%p, t=%p, l=%d]\n", __FILE__, __FUNCTION__, __LINE__, header->magicNum, MAGICNUM, header, tail, header->customAllocLen);
            }
            if (header->sequeceId > __sequence_id) {
                printf("[ERROR] %s:%s:%d: sequeceId[%u][%u] [h=%p, t=%p, l=%d]\n", __FILE__, __FUNCTION__, __LINE__, header->sequeceId, __sequence_id, header, tail, header->customAllocLen);
            }
            if (header->customAllocLen <= 0 || header->customAllocLen > HEAP_ALLOC_SIZE_MAX) {
                printf("[ERROR] %s:%s:%d: allocSize[%u][%u] [h=%p, t=%p, l=%d]\n", __FILE__, __FUNCTION__, __LINE__, header->customAllocLen, HEAP_ALLOC_SIZE_MAX, header, tail, header->customAllocLen);
            }
            if (tail->magicNum != MAGICNUM) {
                printf("[ERROR] %s:%s:%d: tail magic[%0x][%0x] [h=%p, t=%p, l=%d]\n", __FILE__, __FUNCTION__, __LINE__, tail->magicNum, MAGICNUM, header, tail, header->customAllocLen);
            }
            printf("%s%d: h=%p,t=%p,l=%u,seq=%u,m=%u\n", __FUNCTION__, __LINE__, header, tail, header->customAllocLen, header->sequeceId, header->magicNum);
        }

        UNLOCK(&__lock);
    }

    return NULL;
}

static void __init_memcheck() {
    static char init = 0;
    if (0 == init) {
        init = 1;
        list_init_(&__heap_alloc_list);
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
    int alloc_len = len;

    __init_memcheck();

    alloc_len += sizeof(MemcheckHeader);
    alloc_len += sizeof(MemcheckTail);
    //len = __get_align4_size(len);

    if (NULL == (p = malloc(alloc_len))) {
        printf("[ERROR] %s:%s:%d: alloc memory failed\n", file, function, line);
        return NULL;
    }

    MemcheckHeader *header = (MemcheckHeader *)p;
    MemcheckTail *tail = (MemcheckTail *)(p + sizeof(MemcheckHeader) + len);
    header->customAllocLen = len;
    header->magicNum = MAGICNUM;

    tail->magicNum = MAGICNUM;

    LOCK(&__lock);
    header->sequeceId = __sequence_id++;
    __used_heap_cnt++;
    __used_heap_size += len;
    list_add_(&header->link, &__heap_alloc_list);
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
    MemcheckTail *tail = (MemcheckTail *)(p + header->customAllocLen);
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
    if (tail->magicNum != MAGICNUM) {
        printf("[ERROR] %s:%s:%d: tail[%0x][%0x] invalid\n", file, function, line, tail->magicNum, MAGICNUM);
        return;
    }

    LOCK(&__lock);
    __used_heap_cnt--;
    __used_heap_size -= header->customAllocLen;
    list_del_(&header->link);
    UNLOCK(&__lock);

    free(p - sizeof(MemcheckHeader));
}

#define ALLOC_SIZE  (1024 * 1024 - 100)
int main() {
    int count = 0;

    char *buf = (char *)uni_malloc(4097);
    buf = (char *)uni_malloc(1111);
    buf = (char *)uni_malloc(64);
    buf = (char *)uni_malloc(128);
    buf = (char *)uni_malloc(256);

    while (1) {
        usleep(1000 * 1000 * 10);
    }

    return 0;
}
