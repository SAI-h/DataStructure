/*
12.一个递增有序的线性表中,有数值相同的元素存在.若存储方式为单链表.
设计算法去掉数值相同的元素,使表中不再有重复的元素
*/

#include "relatedFun.c"

void removeDuplicateElem(LinkList *L) {
    // 除去头部的重复元素, 保证头部结点的元素值唯一
    while((*L) -> next && (*L) -> next -> data == (*L) -> data) (*L) = (*L) -> next;
    LinkList op = *L;
    while(op) {
        LNode *tmp = op -> next; // tmp定位到op直接后继位置
        while(tmp && tmp -> data == op -> data) { // 单链表未严格递增,逐一比较,这里每次均保留首次出现该值的位置
            LNode *del = tmp;
            tmp = tmp -> next;
            free(del);
        }
        op -> next = tmp;
        op = tmp;
    }
}

int main(void) {
    srand((size_t)time(NULL));
    // 构建递增的单链表
    LinkList L = createOrederLinkList(rand() % Maxsize + 1, rand() % Maxsize, false, 1);
    printf("The original linkList is:\n");
    output(L, false);
    removeDuplicateElem(&L);
    printf("The linkList after the operation:\n");
    output(L, false);
    delLinkList(&L);
    return 0;
}