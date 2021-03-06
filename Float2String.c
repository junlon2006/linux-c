#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Number on countu **/
static int __n_tu(int number, int count) {
  int result = 1;
  while (count-- > 0) result *= number;
  return result;
}

/*** Convert float to string ***/
static void __float_to_string(float f, char r[]) {
  long long int length, length2, i, number, position, sign;
  float number2;

  sign = -1;   // -1 == positive number
  if (f < 0) {
    sign = '-';
    f *= -1;
  }

  number2 = f;
  number = f;
  length = 0;  // Size of decimal part
  length2 = 0; // Size of tenth

  /* Calculate length2 tenth part */
  while((number2 - (float)number) != 0.0 && !((number2 - (float)number) < 0.0)) {
    number2 = f * (__n_tu(10.0, length2 + 1));
    number = number2;
    length2++;
  }

  /* Calculate length decimal part */
  for (length = (f > 1) ? 0 : 1; f > 1; length++) f /= 10;
  position = length;
  length = length + 1 + length2;
  number = number2;
  if (sign == '-') {
    length++;
    position++;
  }

  for (i = length; i >= 0 ; i--) {
    if (i == (length)) r[i] = '\0';
    else if(i == (position)) r[i] = '.';
    else if(sign == '-' && i == 0) r[i] = '-';
    else {
      r[i] = (number % 10) + '0';
      number /=10;
    }
  }
}

/* Thread unsafe 线程不安全函数，有效精度8位（包含整数和小数部分），超过不能保证准确性 */
const char* float_to_string(float f) {
    f += 0.00001;
    static char floatBuf[128];
    __float_to_string(f, floatBuf);
    return floatBuf;
}

#define EPSION      (0.001)
int main(int argc, char *argv[]) {
  float f = -100;
  int count = 0;
  while (f <= 100) {
    float nf = strtof(float_to_string(f += EPSION), NULL);
    if (fabsf(nf - f) > 0.002) {
      printf("ERROR: f=%f, nf=%f\n", f, nf);
    }
    count++;
  }
  printf("count=%d\n", count);
  return 0;
}
