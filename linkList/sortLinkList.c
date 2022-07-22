/*
06.使带头结点的单链表中的元素递增有序
*/

#include "relatedFun.c"

// 带头结点的单链表上实现插入排序
void sort(LinkList L) {
    LNode *op = L -> next;
    L -> next = NULL;
    while(op) {
        LNode *tmp = op -> next;
        LNode *head = L; // 遍历链表查找插入位置
        while(head -> next && head -> next -> data < op -> data) head = head -> next;
        op -> next = head -> next;
        head -> next = op;
        op = tmp;
    }
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList L = createRandomLinkList(rand() % Maxsize + 1, rand() % Maxsize, true);
    printf("The original linkList is:\n");
    output(L, true);
    sort(L);
    printf("The linkList after the operation:\n");
    output(L, true);
    delLinkList(&L);
    return 0;
}