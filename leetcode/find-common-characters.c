/**
 * 
 * 给定仅有小写字母组成的字符串数组 A，返回列表中的每个字符串中都显示的全部字符（包括重复字符）组成的列表。例如，如果一个字符在每个字符串中出现 3 次，但不是 4 次，则需要在最终答案中包含该字符 3 次。

你可以按任意顺序返回答案。

示例 1：

输入：["bella","label","roller"]
输出：["e","l","l"]
示例 2：

输入：["cool","lock","cook"]
输出：["c","o"]
 
提示：
1 <= A.length <= 100
1 <= A[i].length <= 100
A[i][j] 是小写字母

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-common-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#define __my_min(x, y) (x > y ? y : x)
char ** commonChars(char ** A, int ASize, int* returnSize){
    char arr[128][26] = {0};
    char **result = (char **)malloc(128 * 128);
    int idx;
    for (int i = 0; i < ASize; i++) {
        idx = 0;
        while (A[i][idx] != '\0') {
            arr[i][A[i][idx] - 'a']++;
            idx++;
        }
    }
    idx = 0;
    int min, j;
    for (int i = 'a'; i <= 'z'; i++) {
        j = 0;
        min = arr[j][i - 'a'];
        for (int j = 1; j < ASize; j++) {
            min = __my_min(min, arr[j][i - 'a']);
        }
        while (min-- > 0) {
            result[idx] = (char *)malloc(2);
            result[idx][0] = (char)i;
            result[idx][1] = '\0';
            idx++;
        }
    }
    *returnSize = idx;
    return result;
}