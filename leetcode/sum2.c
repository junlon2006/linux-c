/**
 *  给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
    你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
    示例:
    给定 nums = [2, 7, 11, 15], target = 9
    因为 nums[0] + nums[1] = 2 + 7 = 9
    所以返回 [0, 1]
    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/two-sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * 
 * 
 **/
#include <stdio.h>
#include <stdlib.h>

/* solution1：傻瓜式破解 */
static int* __twoSum_1(int* nums, int numsSize, int target, int* returnSize){
    int i, j, i_max = numsSize - 1;
    for (i = 0; i < i_max; i++) {
        for (j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                int *result = malloc(sizeof(int) * 2);
                result[0] = i;
                result[1] = j;
                *returnSize = 2;
                return result;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

/* solution2：简单hash桶 */
typedef struct node {
    struct node *next;
    int         value;
    int         index;
} node;

static int __hashcode(int key, int size) {
    if (key < 0) {
        key = 0 - key;
    }
    return key & (size - 1);
}

static void __destroy_hashmap(node **n, int size) {
    node *p, *q;
    for (int i = 0; i < size; i++) {
      p = n[i];
      while (p){
        q = p->next;
        free(p);
        p = q;
      }
    }
}

static node* __insert_new_key(int value, int index) {
  node *n = malloc(sizeof(node));
  n->index = index;
  n->value = value;
  n->next = NULL;
  return n;
}

static int* __twoSum_2(int* nums, int numsSize, int target, int* returnSize) {
    node **hashMap = malloc(sizeof(node) * numsSize);
    node *tmp, *p, *q;
    int i, peer;
    for (i = 0; i < numsSize; i++) {
        peer = target - nums[i];
        tmp = hashMap[__hashcode(peer, numsSize)];
        while (tmp != NULL) {
          if (tmp->value == peer && tmp->index != i) {
            int *result = malloc(sizeof(int) * 2);
            if (tmp->index > i) {
                result[0] = i;
                result[1] = tmp->index;
            } else {
                result[0] = tmp->index;
                result[1] = i;
            }
            
            *returnSize = 2;
            __destroy_hashmap(hashMap, numsSize);
            free(hashMap);
            return result;
          }
          tmp = tmp->next;
        }

        if (NULL == (tmp = hashMap[__hashcode(nums[i], numsSize)])) {
          tmp = hashMap[__hashcode(nums[i], numsSize)] = __insert_new_key(nums[i], i);
          continue;
        }

        p = tmp->next;
        while (p != NULL) {
            tmp = tmp->next;
            p = tmp->next;
        }
        tmp->next = __insert_new_key(nums[i], i);
    }

    __destroy_hashmap(hashMap, numsSize);
    free(hashMap);
    *returnSize = 0;
    return NULL;
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int resultSize;
    int *r = __twoSum_2(a, sizeof(a) / sizeof(a[0]), 9, &resultSize);
    printf("%d,%d\n", r[0], r[1]);
    free(r);
    return 0;
}