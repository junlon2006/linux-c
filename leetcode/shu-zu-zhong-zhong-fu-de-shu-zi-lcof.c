/**
 * 
 * 剑指 Offer 03. 数组中重复的数字
找出数组中重复的数字。


在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

示例 1：

输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 
 

限制：

2 <= n <= 100000
 * 
 */ 

int findRepeatNumber(int* nums, int numsSize){
    int bucket[numsSize];

    memset(bucket, 0, sizeof(int) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        bucket[nums[i]]++;
        if (bucket[nums[i]] > 1) {
            return nums[i];
        }
    }

    return 0;
}