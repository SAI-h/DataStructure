/*
02.删除带头结点的单链表中所有值为x的结点
*/

#include "relatedFun.c"

// 法一: cur从头至尾扫描单链表,pre指向cur所指结点的前驱.
// 若cur所指的结点值为x,删除该节点并后移;否则,让pre和cur同步后移
void delValEqualsX_1(LinkList L, ElemType x) {
    LNode *pre = L, *cur = L -> next;
    while(cur) {
        if(cur -> data == x) {
            LNode *tmp = cur;
            pre -> next = cur -> next;
            cur = cur -> next;
            free(tmp);
        }else cur = cur -> next, pre = pre -> next;
    }
}

// 法二: 相当于将头结点与后续分离开来了,遍历后续结点.
// 若遍历到的结点的值是应该被删除,则删除;否则,把该结点用尾插法的方式插入链表
// 初始链表仅有头结点,每次遇到非删除结点,则将其插入至对应位置
void delValEqualsX_2(LinkList L, ElemType x) {
    LNode *tail = L, *cur = L -> next;
    while(cur) {
        if(cur -> data != x) {
            tail -> next = cur;
            tail = cur;
            cur = tail -> next;
            tail -> next = NULL;
        }else {
            LNode *tmp = cur;
            cur = cur -> next;
            free(tmp);
        }
    }
}

int main(void) {
    srand((size_t)time(NULL));
    int range = rand() % Maxsize;
    // 创建带有头结点的单链表
    LinkList L = createRandomLinkList(rand() % Maxsize + 1, range, true);
    printf("The original linkList is:\n");
    output(L, true);
    ElemType delItemX = rand() % range;
    printf("The deleted item is:%d\n", delItemX);
    // delValEqualsX_1(L, delItemX);
    delValEqualsX_2(L, delItemX);
    printf("The linkList after the operation:\n");
    output(L, true);
    delLinkList(&L);
    return 0;
}