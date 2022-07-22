#include "linkList.h"

// 创建单链表 lenth:单链表的长度, dataRange:结点的值域, hasHead:是否带有头结点
LinkList createRandomLinkList(int length, int dataRange, bool hasHead) {
    LinkList res = NULL, op = NULL;
    for(int i = 0; i < length; i ++) {
        LNode *tmp = (LinkList)malloc(sizeof(LNode));
        tmp -> next = NULL;
        tmp -> data = rand() % dataRange;
        if(i == 0) {
            res = tmp;
            op = res;
        }else {
            op -> next = tmp;
            op = tmp;
        }
    }
    if(hasHead) {
        LNode *head = (LinkList)malloc(sizeof(LNode));
        head -> data = MAXLIM;
        head -> next = res;
        res = head;
    }
    return res;
}

// 输出单链表 可用于对单链表和循环单链表的输出
bool output(LinkList L, bool hasHead) {
    if(hasHead && L == NULL) return false;
    LNode *op = L;
    if(hasHead) op = op -> next;
    do{    
        printf("%d", op -> data);
        op = op -> next;
        if(op && op != L) printf("->");
    }while(op && op != L);
    printf("\n");
    return true;
}

// 取二者中的较小者
ElemType min(ElemType a, ElemType b) {
    return a < b ? a : b;
}

// 拼接两个单链表
LinkList joinTogether(LinkList L, LinkList com) {
    LinkList res = L;
    while(L -> next) L = L -> next;
    L -> next = com;
    return res;
}

// 释放空间 可用于对单链表和循环单链表的空间释放
void delLinkList(LinkList *L) {
    if(*L == NULL) return;
    LNode *head = *L;
    *L = (*L) -> next;
    while(*L && (*L) -> next != head) {
        LNode *tmp = *L;
        *L = (*L) -> next;
        free(tmp);
    }
    free(head);
}

// 创建单链表, 单链表中的元素递增 choice:0,序列必须严格递增, 1:序列可以不严格递增
LinkList createOrederLinkList(int length, int seed, bool hasHead, int choice) {
    LinkList head = NULL, op = NULL;
    int last = -MAXLIM;
    for(int i = 0; i < length; i ++) {
        LNode *node = (LNode *)malloc(sizeof(LNode));
        int data = -MAXLIM;
        do{
            data = rand() % seed;
            if(data == seed - 1) seed += 10;
        }while(data + choice <= last);
        last = data;
        node -> data = data;
        node -> next = NULL;
        if(i == 0){
            head = node;
            op = node;
        }else {
            op -> next = node;
            op = op -> next;
        }
    }
    if(hasHead) {
        LNode *TrueHead = (LNode *)malloc(sizeof(LNode));
        TrueHead -> data = MAXLIM;
        TrueHead -> next = head;
        head = TrueHead;
    }
    return head;
}

// 创建循环双链表
DLinkList createCircularDLinkList(int length, int dataRange, bool hasHead) {
    DLinkList head = NULL, tail = NULL;
    for(int i = 0; i < length; i ++) {
        DNode *item = (DNode *)malloc(sizeof(DNode));
        item -> data = rand() % dataRange;
        if(i == 0) {
            item -> next = item -> prior = NULL;
            head = item;
            tail = head;
        }else {
            tail -> next = item;
            item -> prior = tail;
            item -> next = NULL;
            tail = tail -> next;
        }
    }
    if(hasHead) {
        DNode *actHead = (DNode *)malloc(sizeof(DNode));
        actHead -> data = MAXLIM;
        actHead -> prior = NULL;
        actHead -> next = head;
        head -> prior = actHead;
        head = actHead;
    }
    head -> prior = tail;
    tail -> next = head;
    return head;
}

// 输出双链表中元素的值 whetherForward:是否沿着next方向前进(否则沿着prior前进), hasCycle:是否是循环链表
void outputDList(DLinkList L, bool hasHead, bool whetherForward) {
    if(whetherForward) { // 沿着next方向输出
        DNode *op = L;
        if(hasHead) op = op -> next;
        do{
            printf("%d", op -> data);
            op = op -> next;
            if(op && op != L) printf("->");
        }while(op && op != L);
    }else { // 沿着prior方向输出, 目前只实现循环双链表的逆向输出
        DNode *op = L -> prior;
        do{
            printf("%d", op -> data);
            op = op -> prior;
            if((hasHead && op != L) || (!hasHead && op != L -> prior)) printf("->");
        }while((hasHead && op != L) || (!hasHead && op != L -> prior));
    }
    printf("\n");
}

// 释放双链表的空间
void delDLinkList(DLinkList *L) {
    if((*L) -> prior) {
        (*L) -> prior -> next = NULL;
        (*L) -> prior = NULL;
    }
    while(*L) {
        DNode *tmp = *L;
        *L = (*L) -> next;
        free(tmp);
    }
}

// 创建循环单链表
LinkList createCircularLinkList(int length, int dataRange, bool hasHead) {
    LinkList head = NULL, op = NULL;
    for(int i = 0; i < length; i ++) {
        LNode *tmp = (LNode *)malloc(sizeof(LNode));
        tmp -> data = rand() % dataRange;
        tmp -> next = NULL;
        if(i == 0) {
            head = tmp;
            op = tmp;
        }else {
            op -> next = tmp;
            op = op -> next;
        }
    }
    if(hasHead) {
        LNode *actHead = (LNode *)malloc(sizeof(LNode));
        actHead -> data = MAXLIM;
        actHead -> next = head;
        head = actHead;
        if(op == NULL) op = head;
    }
    op -> next = head;
    return head;
}