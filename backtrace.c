#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 100

void __frame3(void) {
  int j, nptrs;
  void *buffer[100];
  char **strings;
  nptrs = backtrace(buffer, SIZE);
  printf("backtrace() returned %d addresses\n", nptrs);
  /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
     would produce similar output to the following: */
  strings = backtrace_symbols(buffer, nptrs);
  if (strings == NULL) {
    perror("backtrace_symbols");
    exit(EXIT_FAILURE);
  }
  for (j = 0; j < nptrs; j++) {
    printf("%s\n", strings[j]);
  }
  free(strings);
}

static void __frame2(void) {
  __frame3();
}

void __frame1(int ncalls) {
  if (ncalls > 1) {
    __frame1(ncalls - 1);
  } else {
    __frame2();
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "%s num-calls\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  __frame1(atoi(argv[1]));
  exit(EXIT_SUCCESS);
}
