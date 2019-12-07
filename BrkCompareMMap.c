#include <stdio.h>
#include <stdlib.h>

#define SMALL_BINS   (1024 * 16)
#define BIG_BINS     (1024 * 256)

int main() {
  char *p1 = (char *)malloc(SMALL_BINS);
  printf("p1=%p\n", p1);

  char *p2 = (char *)malloc(BIG_BINS);
  printf("p2=%p\n", p2);

  char *p3 = (char *)malloc(SMALL_BINS);
  printf("p3=%p\n", p3);

  char *p4 = (char *)malloc(BIG_BINS);
  printf("p4=%p\n", p4);

  static int i = 110;
  static int j;
  static int k = 110;
  static int m;

  printf("i=%p\n", &i);
  printf("j=%p\n", &j);
  printf("k=%p\n", &k);
  printf("m=%p\n", &m);

  free(p1);
  free(p2);
  free(p3);
  free(p4);

  return 0;
}
