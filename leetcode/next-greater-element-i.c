/**
 * 
 * 496. 下一个更大元素 I
给定两个 没有重复元素 的数组 nums1 和 nums2 ，其中nums1 是 nums2 的子集。找到 nums1 中每个元素在 nums2 中的下一个比其大的值。

nums1 中数字 x 的下一个更大元素是指 x 在 nums2 中对应位置的右边的第一个比 x 大的元素。如果不存在，对应位置输出 -1 。

 

示例 1:

输入: nums1 = [4,1,2], nums2 = [1,3,4,2].
输出: [-1,3,-1]
解释:
    对于num1中的数字4，你无法在第二个数组中找到下一个更大的数字，因此输出 -1。
    对于num1中的数字1，第二个数组中数字1右边的下一个较大数字是 3。
    对于num1中的数字2，第二个数组中没有下一个更大的数字，因此输出 -1。
示例 2:

输入: nums1 = [2,4], nums2 = [1,2,3,4].
输出: [3,-1]
解释:
    对于 num1 中的数字 2 ，第二个数组中的下一个较大数字是 3 。
    对于 num1 中的数字 4 ，第二个数组中没有下一个更大的数字，因此输出 -1 。
 

提示：

nums1和nums2中所有元素是唯一的。
nums1和nums2 的数组大小都不超过1000。
 * 
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    int *result = malloc(sizeof(int) * nums1Size);
    int max;
    int start_find_max;
    for (int i = 0; i < nums1Size; i++) {
        max = -1;
        start_find_max = 0;
        for (int j = 0; j < nums2Size; j++) {
            if (nums1[i] == nums2[j]) {start_find_max = 1; continue;}
            if (start_find_max == 1 && nums2[j] > nums1[i]) {max = nums2[j]; break;}
        }
        result[i] = max;
    }

    *returnSize = nums1Size;
    return result;
}