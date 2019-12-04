#include <stdio.h>

#define IS_UNSIGNED_TYPE(val) (((val) >= 0) && ((~(val)) > 0)) 

int main() {

    printf("Question 10U is unsigned type? Answer: %s\n", IS_UNSIGNED_TYPE(10U) ? "yes" : "no");
    printf("Question 10 is unsigned type? Answer: %s\n", IS_UNSIGNED_TYPE(10) ? "yes" : "no");
    printf("Question current int default unsigned? Answer: %s\n", IS_UNSIGNED_TYPE(-1) ? "yes" : "no");
    
    return 0;
}