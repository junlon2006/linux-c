
// In  <s><SetMode_><Please_> 请 </Please_> 设置 <Room_> 厨房 </Room_> <Device_> 冰箱 </Device_> <Mode_> 冰冻 模式 </Mode_> </SetMode_></s>
// Out {"cmd":"SetMode","replay":"已为你打开冰冻模式|已打开冰箱的冰冻模式","solts":{"Device":"冰箱","Mode":"冰冻模式","Please":"请","Room":"厨房"}}

#include <stdio.h>
#define START_TAG  "<s>"
#define END_TAG    "</s>"

#define uni_min(x,y)         ({ \
                                typeof(x) _x = (x); \
                                typeof(y) _y = (y); \
                                (void)(&_x == &_y); \
                                _x < _y ? _x : _y;})

static void __nlu_parse(const char *asr_result) {
    
}

int main() {
    int a = 100;
    unsigned int b = 99;

    int *c;
    char *d;
    if ((void*)c == d) {

    }

    uni_min(1, 2);
    return 0;
}