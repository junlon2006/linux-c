/**
 * 
 * 1122. 数组的相对排序
给你两个数组，arr1 和 arr2，

arr2 中的元素各不相同
arr2 中的每个元素都出现在 arr1 中
对 arr1 中的元素进行排序，使 arr1 中项的相对顺序和 arr2 中的相对顺序相同。未在 arr2 中出现过的元素需要按照升序放在 arr1 的末尾。

 

示例：

输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
输出：[2,2,2,1,4,3,3,9,6,7,19]
 

提示：

arr1.length, arr2.length <= 1000
0 <= arr1[i], arr2[i] <= 1000
arr2 中的元素 arr2[i] 各不相同
arr2 中的每个元素 arr2[i] 都出现在 arr1 中
 * 
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* relativeSortArray(int* arr1, int arr1Size, int* arr2, int arr2Size, int* returnSize){
    int buckets[1001] = {0};
    int idx = 0;
    int *result = malloc(sizeof(int) * arr1Size);
    for (int i = 0; i < arr1Size; i++) {
        buckets[arr1[i]]++;
    }

    for (int i = 0; i < arr2Size; i++) {
        while (buckets[arr2[i]]-- > 0) result[idx++] = arr2[i];
    }

    for (int i = 0; i < 1001; i++) {
        while (buckets[i]-- > 0) result[idx++] = i;
    }

    *returnSize = arr1Size;
    return result;
}