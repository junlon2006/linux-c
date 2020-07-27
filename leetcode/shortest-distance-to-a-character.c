/**
 * 
 * 821. 字符的最短距离
给定一个字符串 S 和一个字符 C。返回一个代表字符串 S 中每个字符到字符串 S 中的字符 C 的最短距离的数组。

示例 1:

输入: S = "loveleetcode", C = 'e'
输出: [3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0]
说明:

字符串 S 的长度范围为 [1, 10000]。
C 是一个单字符，且保证是字符串 S 里的字符。
S 和 C 中的所有字母均为小写字母。
 * 
 */

#define __MIN(a, b) (a < b ? a : b)
int* shortestToChar(char * S, char C, int* returnSize) {
    int len = strlen(S);
    int *result = malloc(sizeof(int) * len);
    memset(result, 0xFF, sizeof(int) * len);
    int idx;
    int c_idx = -1;
    for (int i = 0; i < len; i++) {
        if (S[i] != C) {
            if (c_idx != -1) result[i] = i - c_idx;
            continue;
        }
        idx = i;
        c_idx = i;
        while (idx >= 0) {
            if (result[idx] == -1 || result[idx] > i - idx) {
                result[idx] = i - idx;
                idx--;
                continue;
            }
            break;
        }
    }

    *returnSize = len;
    return result;
}