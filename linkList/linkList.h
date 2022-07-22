#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bool int 
#define true 1
#define false 0
#define Maxsize 100
#define ElemType int
#define MAXLIM 0x7f7f7f7f

// 单链表
typedef struct LNode {
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

// 双链表
typedef struct DNode {
    ElemType data;
    struct DNode *prior, *next; // 前驱和后继
}DNode, *DLinkList;

// 创建单链表 lenth:单链表的长度, dataRange:结点的值域, hasHead:是否带有头结点
LinkList createRandomLinkList(int length, int dataRange, bool hasHead);
// 输出单链表 可用于对单链表和循环单链表的输出
bool output(LinkList L, bool hasHead);
// 取二者中的较小者
ElemType min(ElemType a, ElemType b);
// 拼接两个单链表
LinkList joinTogether(LinkList L, LinkList com);
// 释放空间 可用于对单链表和循环单链表的空间释放
void delLinkList(LinkList *L);
// 创建单链表, 单链表中的元素递增
LinkList createOrederLinkList(int length, int seed, bool hasHead, int choice);
// 创建循环双链表
DLinkList createCircularDLinkList(int length, int dataRange, bool hasHead);
// 输出双链表中元素的值 whetherForward:是否沿着next方向前进(否则沿着prior前进)
void outputDList(DLinkList L, bool hasHead, bool whetherForward);
// 释放双链表的空间
void delDLinkList(DLinkList *L);
// 创建循环单链表
LinkList createCircularLinkList(int length, int dataRange, bool hasHead);