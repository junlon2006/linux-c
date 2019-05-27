#include <stdio.h>
#include <execinfo.h>

void __frame2() {
  void *addr = __builtin_return_address(0);
  backtrace_symbols_fd(&addr, 1, 1);
}

void __frame1() {
  __frame2();
}

int main() {
  __frame1();
  return 0;
}
