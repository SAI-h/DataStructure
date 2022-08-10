/*
07.[2019统考真题]请设计一个队列,要求满足:(1).初始化时队列为空;(2).入队时,允许增加队列占有的空间;
(3).出队后,出对元素所占的空间可重复使用;(4).入队操作和出队操作的时间复杂度始终保持为O(1)

分析:
本题可以采用单循环链表来实现队列,在队头指向处出队,在队尾指向处入队.
对于整个队列而言,队尾指针(入队操作后)永远指向的是所有的最后数据项的后一个位置.可以认为牺牲了这个结点,来完成整体的入队操作.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define bool int 
#define true 1
#define false 0
#define Maxsize 100
#define ElemType int
#define MAXLIM 0x7f7f7f7f

// 队列中的结点
typedef struct queueNode {
    ElemType data;
    struct queueNode* next;
}*queueNode;

// 队列
typedef struct queue {
    struct queueNode* head;
    struct queueNode* rear;
}*queue;

// 队列初始化
bool initQueue(queue *q) {
    *q = (queue)malloc(sizeof(struct queue));
    if(*q == NULL) return false;
    queueNode headNode = (queueNode)malloc(sizeof(struct queueNode));
    if(headNode == NULL) return false;
    headNode -> data = MAXLIM;
    (*q) -> head = (*q) -> rear = headNode;
    headNode -> next = headNode;
    return true;
}

// 判断队列是否为空
bool queueEmpty(queue q) {
    return q -> head == q -> rear;
}

// 入队
bool queuePush(queue q, ElemType x) {
    q -> rear -> data = x;
    if(q -> rear -> next == q -> head) { // 可以视为队满,需要引入新的存储空间
        queueNode e = (queueNode)malloc(sizeof(struct queueNode));
        if(e == NULL) return false;
        e -> data = MAXLIM;
        q -> rear -> next = e;
        e -> next = q -> head;
    }
    q -> rear = q -> rear -> next;
    return true;
}

// 出队
bool queuePop(queue q, ElemType *x) {
    if(queueEmpty(q)) return false;
    *x = q -> head -> data;
    q -> head = q -> head -> next;
    return true;
}

// 队列的可视化
void queueShow(queue q) {
    if(queueEmpty(q)) {
        printf("NULL\n");
    }else {
        queueNode op = q -> head;
        while(op != q -> rear) {
            printf(" | %d", op -> data);
            op = op -> next;
        }
        printf(" |\n");
    }
}

// 释放空间
void freeSpace(queue *q) {
    queueNode op = (*q) -> head;
    if(op -> next == op) free(op);
    op = op -> next;
    while(op != (*q) -> head) {
        queueNode tmp = op;
        op = op -> next;
        free(tmp);
    }
    free(op);
    free(*q);
}

int main(void) {
    queue q;
    bool result = initQueue(&q);
    if(! result) {
        printf("The queue initialization failed!");
        exit(1);
    }
    char ch[2];
    do {
        printf("Operation list:\n");
        printf("1.Push X into the queue.\t\t\t2.Remove the top element of the queue.\n");
        printf("Please enter the operation to be performed:");
        char choice[2];
        scanf("%s", choice);
        switch (choice[0])
        {
            case '1': {
                printf("Please enter the element x:");
                int x;
                scanf("%d", &x);
                if(queuePush(q, x))  
                    printf("Execute successfully!\n");
                else
                    printf("Execute failed!\n");
                break;
            }
            case '2': {
                int top;
                if(queuePop(q, &top))
                    printf("Execute successfully!\n"
                    "The element at the top of the queue that is removed is %d!\n", top);
                else
                    printf("The queue is empty!\n");
                break;
            }
        }
        printf("The queue after the operation is:\n");
        queueShow(q);
        printf("Exit? (y or n):");
        scanf("%s", ch);
    }while(ch[0] != 'y');
    freeSpace(&q);
    return 0;
}