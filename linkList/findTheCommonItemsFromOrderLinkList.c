/*
14.A和B是两个所含元素递增的单链表,设计一个算法从A和B中的公共元素产生单链表C,且不破坏A、B结点
*/

#include "relatedFun.c"

// 同步比较A、B链表的当前值, 将较小者的链表指针后移, 相等时以尾插法的方式进行插入
LinkList createCommonLinkList(LinkList A, LinkList B) {
    LinkList C = createRandomLinkList(0, 0, true);
    LNode *op = C;
    while(A -> next && B -> next) { // 两个链表存在一个为空,就没有继续往下的意义了, 因为公共元素来自于取决于两个链表
        if(A -> next -> data == B -> next -> data) {
            LNode *tmp = (LNode *)malloc(sizeof(LNode));
            tmp -> next = NULL;
            tmp -> data = A -> next -> data;
            op -> next = tmp;
            op = op -> next;
            A = A -> next;
            B = B -> next;
        }else if(A -> next -> data < B -> next -> data) {
            A = A -> next;
        }else {
            B = B -> next;
        }
    }
    return C;
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList A = createOrederLinkList(rand() % Maxsize + 1, rand() % Maxsize, true, 0);
    LinkList B = createOrederLinkList(rand() % Maxsize + 1, rand() % Maxsize, true, 0);
    printf("The linkList A is:\n");
    output(A, true);
    printf("The linkList B is:\n");
    output(B, true);
    LinkList C = createCommonLinkList(A, B);
    printf("The result is:\n");
    output(C, true);
    delLinkList(&A);
    delLinkList(&B);
    delLinkList(&C);
    return 0;
}