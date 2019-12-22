/**
 * 
 * 判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

示例 1:
输入: 121
输出: true

示例 2:
输入: -121
输出: false
解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
示例 3:

输入: 10
输出: false
解释: 从右向左读, 为 01 。因此它不是一个回文数。
进阶:

你能不将整数转为字符串来解决这个问题吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindrome-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
**/

bool isPalindrome(int x) {
    char buf[16];
    int y = x;
    long long z = 0;
    int len = 0;
    if (x < 0) {
        return false;
    }
    if (x == 0) {
        return true;
    }
    while (x > 0) {
        buf[len++] = x % 10;
        x /= 10;
    }
    for (int i = 0; i < len; i++) {
        z *= 10;
        z += buf[i];
    }
    return y == z;
}

bool isPalindrome(int x){
    char buf[16];
    sprintf(buf, "%d", x);
    int len = strlen(buf);
    int i = 0, j = len - 1;
    while (i < j) {
        if (buf[i] != buf[j]) {
            return false;
        }
        i++, j--;
    }
    return true;
}