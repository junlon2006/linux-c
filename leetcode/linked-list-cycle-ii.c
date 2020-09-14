142. 环形链表 II
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。

说明：不允许修改给定的链表。

struct ListNode *detectCycle(struct ListNode *head) {
    struct ListNode *fast, *slow;
    fast = head;
    slow = head;
    while (fast) {
        if(NULL == fast->next || NULL == fast->next->next) return NULL;
        else {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) break;
        }
    }

    fast = head;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    
    return slow;
}