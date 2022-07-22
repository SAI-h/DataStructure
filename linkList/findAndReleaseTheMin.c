/*
19.有一个带头结点的循环单链表,结点值均为正数.设计一个算法,反复找出链表中的结点最小值,
然后将其从链表中删除,直到单链表为空为止,再删除表头结点.
*/

#include "relatedFun.c"

void findAndReleaseTheMin(LinkList L) {
    while(L -> next != L) {
        LNode *op = L -> next, *pre = L, *del = L;
        ElemType MinItem = MAXLIM;
        while(op != L) {
            if(op -> data < MinItem) {
                MinItem = op -> data;
                del = pre;
            }
            pre = pre -> next;
            op = op -> next;
        }
        LNode *tmp = del -> next;
        del -> next = del -> next -> next;
        free(tmp);
        printf("The item %d has been deleted!\n", MinItem);
    }
    free(L);
    printf("The table header has been deleted!\n");
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList L = createCircularLinkList(rand() % Maxsize + 1, rand() % Maxsize, true);
    printf("The original linkList is:\n");
    output(L, true);
    findAndReleaseTheMin(L);
    return 0;
}