/**
 * 剑指 Offer 52. 两个链表的第一个公共节点
 * 输入两个链表，找出它们的第一个公共节点。 
 */

static int __get_list_len(struct ListNode *head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    int len_a = __get_list_len(headA);
    int len_b = __get_list_len(headB);

    if (0 == len_a || 0 == len_b) {
        return NULL;
    }

    while (len_a > len_b) {
        headA = headA->next;
        len_a--;
    }

    while (len_b > len_a) {
        headB = headB->next;
        len_b--;
    }

    while (headA) {
        if (headA == headB) return headA;
        headA = headA->next;
        headB = headB->next;
    }

    return NULL;
}

