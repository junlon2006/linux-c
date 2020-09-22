/*
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-two-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int sum, carry = 0;
    struct ListNode *p = NULL, *t, *head;
    head = malloc(sizeof(struct ListNode));
    while (l1 || l2 || carry) {
        sum = carry;
        if (l1) sum += l1->val;
        if (l2) sum += l2->val;
        if (NULL == p) {
            head->val = sum % 10;
            head->next = NULL;
            p = head;
        } else {
            t = malloc(sizeof(struct ListNode));
            t->val = sum % 10;
            t->next = NULL;
            p->next = t;
            p = t;
        }
        carry = sum / 10;
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    return head;
}