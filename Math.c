#include <stdio.h>

#define __MIN(x,y)         ({ \
                                typeof(x) _x = (x); \
                                typeof(y) _y = (y); \
                                (void)(&_x == &_y); \
                                _x < _y ? _x : _y;})

#define __MAX(x,y)         ({ \
                                typeof(x) _x = (x); \
                                typeof(y) _y = (y); \
                                (void)(&_x == &_y); \
                                _x > _y ? _x : _y;})

int main() {
    int a = 10;
    unsigned int b = -1;
    printf("the min of a and b is %d\n", __MIN(a, b)); /* warning: comparison of distinct pointer types */
    printf("the min of a and b is %d\n", __MIN((unsigned int)a, b)); /* no warning */
    
    return 0;
}