
/**
 * 
 *给定两个二进制字符串，返回他们的和（用二进制表示）。

输入为非空字符串且只包含数字 1 和 0。

示例 1:

输入: a = "11", b = "1"
输出: "100"
示例 2:

输入: a = "1010", b = "1011"
输出: "10101"

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-binary
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
**/

char * addBinary(char * a, char * b){
    int len_a, len_b, i;
    len_a = strlen(a);
    len_b = strlen(b);
    i = len_a > len_b ? len_a : len_b;
    char *ret = malloc(i + 2);
    ret[i + 1] = '\0';
  
    int sum = 0;
    for (; i >= 0; i--) {
        if (len_a > 0) {
            sum += (a[--len_a] - '0');
        }

        if (len_b > 0) {
            sum += (b[--len_b] - '0');
        }

        if (sum == 0) {
            ret[i] = '0';
        } else if (sum == 1) {
            ret[i] = '1';
            sum = 0;
        } else if (sum == 2) {
            ret[i] = '0';
            sum = 1;
        } else {
            ret[i] = '1';
            sum = 1;
        }
       
    }

    if (ret[0] == '0') {
        char *p = ret;
        while (*p) {
            p[0] = p[1];
            p++;
        }
    }

    return ret;
}