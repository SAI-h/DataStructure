/*
07.删除无序的带有头结点的单链表中值介于给定的两个值之间的所有元素
*/

#include "relatedFun.c"

// 和02题的做法一致,只是将等于判断改为是否落入区间的判断,亦可以将区间外的项依次插入链表的方式
void delItemBetweenAandB(LinkList L, ElemType s, ElemType t) {
    LNode *pre = L, *op = L -> next;
    while(op) {
        if(op -> data <= t && op -> data >= s) {
            LNode *tmp = op;
            pre -> next = op -> next;
            op = op -> next;
            free(tmp);
        }else op = op -> next, pre = pre -> next;
    }
}

int main(void) {
    srand((size_t)time(NULL));
    int range = rand() % Maxsize;
    LinkList L = createRandomLinkList(rand() % Maxsize + 1, range, true);
    printf("The original linkList is:\n");
    output(L, true);
    ElemType s = rand() % range;
    ElemType t = min(rand() % range + s, range - 1);
    printf("Delete the value between %d and %d.\n", s, t);
    delItemBetweenAandB(L, s, t);
    printf("The linkList after the operation:\n");
    output(L, true);
    delLinkList(&L);
    return 0;
}