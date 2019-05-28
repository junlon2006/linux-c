#include "test.h"
#include <stdio.h>

void __attribute__ ((weak)) test(void) {
  printf("%s%d: this is weak function\n", __FUNCTION__, __LINE__);
}