/*
05.就地逆置(空间复杂度为O(1))带头结点的单链表
*/

#include "relatedFun.c"

// 将头结点从链表中分离出来,将后续链表的元素采用头插法的方式一一插入链表即可
void reverse(LinkList L) {
    LNode *op = L -> next;
    L -> next = NULL;
    while(op) {
        LNode *tmp = op -> next;
        op -> next = L -> next;
        L -> next = op;
        op = tmp;
    }
}

// 假设存在链表为 1->2->3->a->b->3->4
// 假使前四个位置已完成逆序,则形如 1<-2<-3<-a b->3->4
// 此时我们要处理下一步则需要将b的next指针指向a,但为了保证不断链,即可以继续获取到b原先的后继3,我们需要事先保存b的后继位置
// 所以我们进行操作时实际上需要三个相邻的结点位置:已完成逆置的新的单链表的末尾、现在操作到的位置、下一个操作的位置
// 我们做的事情就是保存下一个操作的位置、让操作到的位置指向新单链表的末尾,使其位于表头、让三个记录结点的位置同步后移
// 循环往复直至链表完成逆置
void reverse_2(LinkList *L) {
    LNode *pre = *L, *cur = (*L) -> next; // 每次操作完成后pre都会位于表头,因此实际上不必开pre指针进行操作,直接用L操作即可,这样传参可以不用传地址
    (*L) -> next = NULL;
    while(cur) {
        LNode *tmp = cur -> next;
        cur -> next = pre;
        pre = cur;
        cur = tmp;
    }
    *L = pre;
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList L = createRandomLinkList(rand() % Maxsize + 1, rand() % Maxsize, true);
    printf("(1).Have a header node\n");
    printf("The original linkList is:\n");
    output(L, true);
    reverse(L);
    printf("The linkList after the operation:\n");
    output(L, true);
    delLinkList(&L);

    // 那么如果对于不带头结点的单链表又该如何操作呢?(不采用冗余一个头结点的方式)
    printf("(2).No header node\n");
    LinkList P = createRandomLinkList(rand() % Maxsize + 1, rand() % Maxsize, false);
    printf("The original linkList is:\n");
    output(P, false);
    reverse_2(&P); // 链表的初始位置会发生变更,因此传入的是地址
    printf("The linkList after the operation:\n");
    output(P, false);
    delLinkList(&P);
    return 0;
}