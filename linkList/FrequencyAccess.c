/*
20.设头指针L的带头结点的非循环双向链表,其中每个节点除了前驱指针、数据和后继指针外,
还有一个访问频度域freq.在链表被启用前,其值被初始化为0.每当链表中进行一次Locate(L,x)运算时,
令元素值为x的结点中的freq域的值增1,并使此链表中结点保持按访问频度非增(递减)的顺序排列.
同时最近访问的结点排在频度相同的结点前面,以使频繁访问的结点总是靠近表头.
试编写符合上述要求的Locate(L,x)运算的算法,该运算为函数过程,返回找到结点的地址,类型为指针型.
*/

// 注:本题没有采用之前已写好的函数和相关数据结构

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define bool int 
#define true 1
#define false 0
#define Maxsize 100
#define ElemType int
#define MAXLIM 0x7f7f7f7f

typedef struct DNode {
    ElemType data;
    struct DNode *prior, *next; // 前驱和后继
    int freq; // 频度域
}DNode, *DLinkList;

// 获取数据数组
ElemType* getDataSave(int length) {
    bool *hasSet = (bool *)malloc(sizeof(bool) * Maxsize); // 保证设置值的唯一性
    for(int i = 0; i < Maxsize; i ++) hasSet[i] = false;
    ElemType *dataSave = (ElemType *)malloc(sizeof(ElemType) * length);
    for(int i = 0; i < length; i ++) {
        int x;
        do{
            x = rand() % Maxsize;
        }while(hasSet[x]);
        dataSave[i] = x;
        hasSet[x] = true;
    }
    free(hasSet);
    return dataSave;
}

// 根据数据数组创建带头结点的非循环双链表
DLinkList createDLinkList(ElemType *dataSave, int length) {
    DLinkList L = (DNode *)malloc(sizeof(DNode));
    L -> data = MAXLIM;
    L -> next = NULL;
    L -> prior = NULL;
    L -> freq = 0;
    DNode *op = L;
    for(int i = 0; i < length; i ++) {
        DNode *tmp = (DNode *)malloc(sizeof(DNode));
        tmp -> data = dataSave[i];
        tmp -> freq = 0;
        op -> next = tmp;
        tmp -> prior = op;
        tmp -> next = NULL;
        op = tmp;
    }
    return L;
}

// 输出双链表的数据域和频度域
void output(DLinkList L) {
    while(L -> next) {
        printf("(%d:%d)", L -> next -> data, L -> next -> freq);
        L = L -> next;
        if(L -> next) printf("->");
    }
    printf("\n\n");
}

// 访问双链表中的x元素,并调节双链表中元素位置
DNode *locate(DLinkList L, ElemType x) {
    if(L == NULL) return NULL; // 传入链表非法
    DNode *op = L -> next;
    while(op && op -> data != x) op = op -> next;
    if(op == NULL) return NULL; // 没有找到x元素
    op -> freq ++; // 频度值加一
    DNode *result = op;
    result -> prior -> next = result -> next; // 先将result从链表中摘除,再向前找到首个频度大于自己的结点(或头结点),并插入至该节点之后
    if(result -> next)
        result -> next -> prior = result -> prior;
    op = op -> prior; // 寻找插入位置
    while(op != L && result -> freq >= op -> freq) op = op -> prior;
    if(op != result -> prior) {
        result -> next = op -> next; // 插入操作,注意次序
        result -> prior = op;
        op -> next -> prior = result;
        op -> next = result;
    }
    return result;
}

// 释放链表空间,递归归还占用空间
void delDLinkList(DLinkList L) {
    if(L == NULL) return;
    delDLinkList(L -> next);
    free(L);
}

int main(void) {
    srand((size_t)time(NULL));
    int length = rand() % Maxsize + 1;
    ElemType *dataSave = getDataSave(length); // 数据数组,根据此数组来生成双链表,并据此数组随机生成locate函数中的x参数
    DLinkList L = createDLinkList(dataSave, length);
    printf("The original DLinkList L(data:freq) is:\n");
    output(L);
    int operatingNum = rand() % Maxsize + 1; // 访问次数
    while(operatingNum --) {
        ElemType x = dataSave[rand() % length];
        printf("The value of this access element is %d.\n", x);
        DNode *result = locate(L, x);
        printf("This element is located in %p.\n", result);
        printf("The DLinkList after the operation:\n");
        output(L);
    }
    free(dataSave);
    delDLinkList(L);
    return 0;
}