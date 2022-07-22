/*
13.将两个按元素值递增排列的单链表,归并为一个按元素递减的单链表.要求利用原来的两个单链表的结点存放归并后的单链表.
*/

#include "relatedFun.c"

// 单链表的归并操作
LinkList merge(LinkList A, LinkList B) {
    LinkList C = createRandomLinkList(0, 0, true); // 辅助头结点,简化操作
    while(A && B) {
        if(A -> data < B -> data) { // 每次取出双方链表者比较元素的较小者,以头插法的方式插入即可,以保证了较小的元素一直处于尾部
            LNode *tmp = A -> next;
            A -> next = C -> next;
            C -> next = A;
            A = tmp;
        }else {
            LNode *tmp = B -> next;
            B -> next = C -> next;
            C -> next = B;
            B = tmp;
        }
    }
    while(A) { // 两个while循环至多只会运行一个
        LNode *tmp = A -> next;
        A -> next = C -> next;
        C -> next = A;
        A = tmp;
    }
    while(B) {
        LNode *tmp = B -> next;
        B -> next = C -> next;
        C -> next = B;
        B = tmp;
    }
    LinkList res = C -> next;
    free(C); // 释放辅助头结点
    return res;
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList A = createOrederLinkList(rand() % Maxsize + 1, rand() % Maxsize, false, 1);
    LinkList B = createOrederLinkList(rand() % Maxsize + 1, rand() % Maxsize, false, 1);
    printf("The linkList A is:\n");
    output(A, false);
    printf("The linkList B is:\n");
    output(B, false);
    LinkList C = merge(A, B);
    printf("The linkList after merging:\n");
    output(C, false);
    delLinkList(&C);
    return 0;
}