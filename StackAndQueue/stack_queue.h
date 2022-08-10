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

// 链栈,一个带头结点的单链表,栈顶元素总是头结点的后继(头插法)
typedef struct stackNode {
    ElemType data;
    struct stackNode *next;
}*stack, stackNode;

// (循环)队列
typedef struct queue {
    ElemType *data;
    int front; // 队首
    int rear; // 队尾
    int capacity; // 队列的最大容量(实际最大容量为capacity-1,因为循环队列设计时会牺牲一个存储单元)
}*queue;

// 栈的初始化
bool initStack(stack *s);
// 栈的判空
bool stackEmpty(stack s);
// 进栈
bool stackPush(stack s, ElemType e);
// 出栈
bool stackPop(stack s);
// 读取栈顶元素
ElemType stackTop(stack s);
// 队列的初始化
bool initQueue(queue *q);
// 队列判空
bool queueEmpty(queue q);
// 入队
bool queuePush(queue q, ElemType e);
// 出队
bool queuePop(queue q);
// 读取队头元素
ElemType queueTop(queue q);
// 取小
int min(int _a, int _b);
// 输出并清空栈中的元素
void outputAndclearStack(stack s);
// 输出并清空队列中的元素
void outputAndclearQueue(queue q);