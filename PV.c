#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define PATH_NAME  "/tmp"

static void __sem_p(int sem_id) {
    struct sembuf  sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = -1;
    sem_buf.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_buf, 1) == -1) {
        perror("semop");
    }
}

static void __sem_v(int sem_id) {
    struct sembuf  sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = 1;
    sem_buf.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_buf, 1) == -1) {
        perror("semop");
    }
}

static int p_count = 0;
static void* __p(void *args) {
    int semId = *((int *)args);

    while (1) {
        __sem_p(semId);
        __sync_fetch_and_add(&p_count, 1);
        printf("%s[%0x]: count=%d\n", __FUNCTION__, (u_int32_t)pthread_self(), p_count);
        usleep(1000 * 1000);
    }

    return NULL;
}

static void* __v(void *args) {
    int count = 0;
    int semId = *((int *)args);

    while (1) {
        __sem_v(semId);
        printf("%s[%0x]: count=%d\n", __FUNCTION__, (u_int32_t)pthread_self(), ++count);
        usleep(1000 * 1000);
    }

    return NULL;
}

int main() {
    key_t key = ftok(PATH_NAME, 9527);
    if (-1 == key) {
        perror("ftok");
        return -1;
    }

    int semid = semget(key, 1, IPC_CREAT);
    if (-1 == semid) {
        if (EEXIST == errno) {
            printf("EXIST\n");
        } else {
            perror("semget");
        }
    }
    printf("semid=%d\n", semid);

    pthread_t pid[3];
    pthread_create(&pid[0], NULL, __p, &semid);
    pthread_create(&pid[1], NULL, __p, &semid);
    pthread_create(&pid[2], NULL, __v, &semid);

    pthread_join(pid[0], NULL);
    pthread_join(pid[1], NULL);
    pthread_join(pid[2], NULL);

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
    }

    return 0;
}
