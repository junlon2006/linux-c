/**
 * 
 * 
 * 编写一个方法，找出两个数字a和b中最大的那一个。不得使用if-else或其他比较运算符。

示例：

输入： a = 1, b = 2
输出： 2

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-lcci/
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
**/

int maximum(int a, int b){ 
  int sign = (int)((((long long)a - (long long)b) >> (sizeof(long long) * 8 - 1)) & 0x01);
  return a * (sign ^ 1) + b * sign;
}