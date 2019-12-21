#include <stdio.h>
#include <stdlib.h>

int *twoSum(int* nums, int numSize, int target, int *returnSize) {
    *returnSize = sizeof(int) * 2;
    int *result = (int *)malloc(*returnSize);
    int i, j, two, find = 0;
    for (i = 0; i < numSize; i++) {
        two = target - nums[i];
        for (j = i + 1; j < numSize; j++) {
            if (nums[j] == two) {
                find = 1;
                break;
            }
        }
        if (find == 1) {
            break;
        }
    } 
    result[0] = i;
    result[1] = j;
    return result;
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int resultSize;
    int *r = twoSum(a, sizeof(a) / sizeof(a[0]), 9, &resultSize);
    printf("%d,%d\n", r[0], r[1]);
    free(r);
    return 0;
}