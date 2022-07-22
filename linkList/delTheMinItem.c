/*
04.删除带头结点的单链表中的其中一个最小结点
*/

#include "relatedFun.c"

// 找到最小值的前驱,利用其前驱指向其后驱的方式删除最小结点
// 当参与删除的是不带头结点的链表时,还需对起始位置的结点进行特判
void delTheMinItem(LinkList L) {
    LNode *op = L, *preMinv = L;;
    ElemType minv = MAXLIM;
    while(op -> next) {
        if(minv > op -> next -> data) {
            minv = op -> next -> data;
            preMinv = op;
        }
        op = op -> next;
    }
    LNode *tmp = preMinv -> next;
    preMinv -> next = preMinv -> next -> next;
    free(tmp);
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList L = createRandomLinkList(rand() % Maxsize, rand() % Maxsize, true);
    printf("The original linkList:\n");
    output(L, true);
    delTheMinItem(L);
    printf("The linkList after the operation:\n");
    output(L, true);
    delLinkList(&L);
    return 0;
}