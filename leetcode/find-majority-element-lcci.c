/**
 * 
 * 面试题 17.10. 主要元素
数组中占比超过一半的元素称之为主要元素。给定一个整数数组，找到它的主要元素。若没有，返回-1。

示例 1：

输入：[1,2,5,9,5,9,5,5,5]
输出：5
 

示例 2：

输入：[3,2]
输出：-1
 

示例 3：

输入：[2,2,1,1,1,2,2]
输出：2
 

说明：
你有办法在时间复杂度为 O(N)，空间复杂度为 O(1) 内完成吗？
 * 
 */

int majorityElement(int* nums, int numsSize){
    int sum = 1;
    int cur = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == cur) {
            sum++;
        } else {
            sum--;
            if (sum == -1) {
                cur = nums[i];
                sum = 1;
            }
        } 
    }

    return sum >= 1 ? cur : -1;
}