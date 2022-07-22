/*
01.递归地删除不带头结点的单链表L中所有值为x的结点
*/

#include "relatedFun.c"

// L:待删除的单链表 Head:初始单链表的起始位置 pre:当前结点的上个结点 x:待删除的元素
// L使用采用指针的指针是因为无头结点,其起始位置因被删除而发生变更
void delValEqualsX(LinkList *L, LinkList Head, LinkList pre, ElemType x) {
    if((*L) == NULL) return;
    if((*L) -> data == x) { // 如果当前结点的值为x,则需要对当前结点进行删除
        LNode *p = *L; 
        if(*L == Head) { // 如果当前结点处于链表起始位置,那么删除当前结点的方式就是让其后继结点取代自己的位置
            *L = Head -> next;
            free(p);
            delValEqualsX(L, *L, NULL, x); // 起始位置无前驱,用NULL来表示
        }else { // 如果当前结点有前驱,那么删除该结点的方式就是让前驱结点指向自己的后继结点
            pre -> next = (*L) -> next;
            free(p);
            delValEqualsX(&(pre -> next), Head, pre, x);
        }
    }else { // 当前结点的值不为x,则对其后续的结点进行判断
        delValEqualsX(&((*L) -> next), Head, *L, x);
    }
}

int main(void) {
    srand((size_t)time(NULL));
    int range = rand() % Maxsize;
    // 获取不带头结点的单链表L
    LinkList L = createRandomLinkList(rand() % Maxsize + 1, range, false);
    printf("The original linkList is:\n");
    output(L, false);
    ElemType delX = rand() % range;
    printf("The deleted Item is: %d\n", delX);
    delValEqualsX(&L, L, NULL, delX);
    printf("The linkList after the operation:\n");
    output(L, false);
    delLinkList(&L);
    return 0;
}