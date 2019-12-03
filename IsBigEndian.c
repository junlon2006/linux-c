#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

static bool __is_big_endian() {
    uint16_t s = 0x1234;
    uint8_t c = *((uint8_t *)&s);
    return 0x12 == c;
}

int main() {
    bool bigEndian = __is_big_endian();
    if (bigEndian) {
        printf("the cpu is big endian\n");
    } else {
        printf("the cpu is little endian\n");
    }
    
    return 0;
}