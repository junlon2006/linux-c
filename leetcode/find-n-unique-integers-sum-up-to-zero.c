/**
 * 
 * 给你一个整数 n，请你返回 任意 一个由 n 个 各不相同 的整数组成的数组，并且这 n 个数相加和为 0 。

示例 1：

输入：n = 5
输出：[-7,-1,1,3,4]
解释：这些数组也是正确的 [-5,-1,1,2,3]，[-3,-1,2,-2,4]。
示例 2：

输入：n = 3
输出：[-1,0,1]
示例 3：

输入：n = 1
输出：[0]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-n-unique-integers-sum-up-to-zero
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

int* sumZero(int n, int* returnSize){
    *returnSize = n;
    int *a = malloc(sizeof(int) * n);
    int max = n / 2;
    int cnt = max;
    for (int i = 0; i < cnt; i++) {
        a[i * 2] = max;
        a[i * 2 + 1] = 0 - max;
        max--;
    }
    if (n % 2 == 1) a[n - 1] = 0;
    return a;
}