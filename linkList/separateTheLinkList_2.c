/*
11. 设C={a1,b1,a2,b2,...,an,bn}为线性表,采用带头结点的单链表存放,
设计一个算法,将其拆分为两个线性表,使得A={a1,a2,...,an},B={bn,...,b2,b1}
*/

#include "relatedFun.c"

// 遍历单链表C,将C中元素依次更迭(交叉)地插入到A和B中,
// 其中A中要求的元素顺序与原链表一致(相对),故其采用尾插法, 而B则与原链表顺序相背, 故其采用头插法
void separateTheLinkList(LinkList C, LinkList A, LinkList B) {
    LinkList op = C -> next;
    while(op) {
        A -> next = op; // 尾插法
        A = A -> next;
        op = op -> next; // 指向下一个元素,倘若当前结点分配在A中,那么下一个结点(若存在)一定分配在B中,因此下面直接对分配于B的情况加以处理
        A -> next = NULL;
        if(op) { // 头插法,若op为NULL, 则op->next没有意义
            LNode* tmp = op -> next; // 暂存C中下一个结点位置
            op -> next = B -> next;
            B -> next = op;
            op = tmp;
        }
    }
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList C = createRandomLinkList(rand() % Maxsize + 1, rand() % Maxsize, true);
    printf("The original linkList is:\n");
    output(C, true);
    LinkList A = createRandomLinkList(0, 0, true);
    LinkList B = createRandomLinkList(0, 0, true);
    separateTheLinkList(C, A, B);
    printf("A={a1,a2,...,an} ==>\n");
    output(A, true);
    printf("B={bn,...,b2,b1} ==>\n");
    output(B, true);
    delLinkList(&A);
    delLinkList(&B);
    delLinkList(&C);
    return 0;
}