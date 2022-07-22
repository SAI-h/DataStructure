/*
18.有两个循环单链表,链表头指针分别为h1和h2,编写一个函数将链表h2链接到链表h1之后,
要求链接后仍保持循环链表形式
*/

#include "relatedFun.c"

void joinLoopLinkList(LinkList h1, LinkList h2) {
    LNode *op1 = h1; // 寻找h1的尾结点的位置
    while(op1 -> next != h1) op1 = op1 -> next;
    LNode *op2 = h2; // 寻找h2的尾结点的位置
    while(op2 -> next != h2) op2 = op2 -> next;
    op1 -> next = h2; // h1的尾部结点的next指针指向h2的头部位置
    op2 -> next = h1; // h2的尾部结点的next指针指向h1的头部位置
}

int main(void) {
    srand((size_t)time(NULL));
    // 创建两个循环单链表
    LinkList h1 = createCircularLinkList(rand() % Maxsize + 1, rand() % Maxsize, false);
    LinkList h2 = createCircularLinkList(rand() % Maxsize + 1, rand() % Maxsize, false);
    printf("The cyclic linkList h1 is:\n");
    output(h1, false);
    printf("The cyclic linkList h2 is:\n");
    output(h2, false);
    joinLoopLinkList(h1, h2);
    printf("The linkList h1 after the operation:\n");
    output(h1, false);
    printf("The linkList h2 after the operation:\n");
    output(h2, false);
    delLinkList(&h1);
    return 0;
}