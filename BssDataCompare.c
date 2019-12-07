#include <stdio.h>

int main() {
  static char buf[1024 * 1024] = {0}; //对比赋值为{1}和{0}的区别
  printf("buf=%p\n", buf);
  return 0;
}
