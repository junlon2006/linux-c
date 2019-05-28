#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  char *p = malloc(1024);
  printf("%s%d: p=%p\n", __FUNCTION__, __LINE__, p);
  free(p);
  return 0;
}
