#include "test.h"
#include <stdio.h>

void test(void) {
  printf("%s%d: this is real function\n", __FUNCTION__, __LINE__);
}