/*
15.A、B代表两个以单链表方式存储的集合,两个链表中的元素均递增,求A、B两个集合的交集.
且最终结果存放于A中(不另开空间)
*/

#include "relatedFun.c"

void generateCommonLinkList(LinkList A, LinkList B) {
    LNode *tailA = A; // tailA:新的链表A的尾结点
    LNode *op1 = A -> next, *op2 = B -> next;
    while(op1 && op2) {
        if(op1 -> data == op2 -> data) {
            tailA -> next -> data = op1 -> data; // 直接进行值的覆盖,类似于快慢指针
            tailA = tailA -> next;
            op1 = op1 -> next;
            op2 = op2 -> next;
        }else if(op1 -> data < op2 -> data) {
            op1 = op1 -> next;
        }else {
            op2 = op2 -> next;
        }
    }
    delLinkList(&(tailA -> next)); // 删除单链表A中tailA中后续的所有结点
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList A = createOrederLinkList(rand() % Maxsize + 1, rand() % Maxsize, true, 0);
    LinkList B = createOrederLinkList(rand() % Maxsize + 1, rand() % Maxsize, true, 0);
    printf("The linkList A is:\n");
    output(A, true);
    printf("The linkList B is:\n");
    output(B, true);
    generateCommonLinkList(A, B);
    printf("The result is:\n");
    output(A, true);
    delLinkList(&A);
    delLinkList(&B);
    return 0;
}