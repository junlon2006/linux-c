#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

#define FIFO_NAME "/tmp/my_fifo"

int main() {
  int ret = mkfifo(FIFO_NAME, 0644);
  int fd;
  char buf[] = "ping";
  if (ret < 0 && errno != EEXIST) {
    printf("mkfifo failed, rc=%d\n", ret);
    exit(EXIT_SUCCESS);
  }
  fd = open(FIFO_NAME, O_WRONLY);
  if (fd < 0) {
    printf("open file[%s] failed\n", FIFO_NAME);
    exit(EXIT_SUCCESS);
  }
  signal(SIGPIPE, SIG_IGN);
  while (1) {
    if (sizeof(buf) != (ret = write(fd, buf, sizeof(buf)))) {
      printf("write failed, len=%d\n", ret);
    } else {
      printf("write %s success\n", buf);
    }
    sleep(1);
  }
  return 0;
}
