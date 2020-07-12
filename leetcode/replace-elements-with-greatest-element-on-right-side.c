/**
 * 
 * 1299. 将每个元素替换为右侧最大元素
给你一个数组 arr ，请你将每个元素用它右边最大的元素替换，如果是最后一个元素，用 -1 替换。

完成所有替换操作后，请你返回这个数组。

 

示例：

输入：arr = [17,18,5,4,6,1]
输出：[18,6,6,6,1,-1]
 

提示：

1 <= arr.length <= 10^4
1 <= arr[i] <= 10^5
 * 
 */

#define __MAX(a, b) (a > b ? a : b)
int* replaceElements(int* arr, int arrSize, int* returnSize){
    int *result = malloc(sizeof(int) * arrSize);
    for (int i = 0; i < arrSize; i++) {
        result[i] = -1;
        for (int j = i + 1; j < arrSize; j++) {
            result[i] = __MAX(result[i], arr[j]);
        }
    }

    *returnSize = arrSize;
    return result;
}

#define __MAX(a, b) (a > b ? a : b)
int* replaceElements(int* arr, int arrSize, int* returnSize){
    int *result = malloc(sizeof(int) * arrSize);
    result[arrSize - 1] = -1;
    for (int i = arrSize - 2; i >= 0; i--) {
        result[i] = __MAX(result[i + 1], arr[i + 1]);
    }
    *returnSize = arrSize;
    return result;
}