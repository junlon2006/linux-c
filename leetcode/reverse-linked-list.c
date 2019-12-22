/**
 *
 * 反转一个单链表。

示例:

输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
进阶:
你可以迭代或递归地反转链表。你能否用两种方法解决这道题？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
**/

/* Definition for singly-linked list. */
struct ListNode {
    int val;
    struct ListNode *next;
};

/* 递归 */
struct ListNode* reverseList(struct ListNode* head){
    if (NULL == head || NULL == head->next) {
        return head;
    }
    
    struct ListNode* left = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return left;
}

/* 循环 */
struct ListNode* reverseList(struct ListNode* head){
    struct ListNode*p, *q, *r;
    if (NULL == head || NULL == head->next) {
        return head;
    }

    p = head;
    q = p->next;
    head->next = NULL;
    while (q != NULL) {
        r = q->next;
        q->next = p;
        p = q;
        q = r;
    }

    return p;
}