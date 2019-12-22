
/**
 * 
 * 给你一个单链表的引用结点 head。链表中每个结点的值不是 0 就是 1。已知此链表是一个整数数字的二进制表示形式。

请你返回该链表所表示数字的 十进制值 。
示例 1：
输入：head = [1,0,1]
输出：5
解释：二进制数 (101) 转化为十进制数 (5)
示例 2：

输入：head = [0]
输出：0
示例 3：

输入：head = [1]
输出：1
示例 4：

输入：head = [1,0,0,1,0,0,1,1,1,0,0,0,0,0,0]
输出：18880

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/convert-binary-number-in-a-linked-list-to-integer
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
**/

#include <stdio.h>
 /* Definition for singly-linked list. */
 struct ListNode {
    int val;
    struct ListNode *next;
 };

int getDecimalValue(struct ListNode* head){
    int len = -1, sum = 0;
    struct ListNode *p = head;
    while (NULL != p) {
        len++;
        p = p->next;
    }

    while (NULL != head) {
        if (head->val == 1) sum += (1 << len);
        len--;
        head = head->next;
    }

    return sum;
}