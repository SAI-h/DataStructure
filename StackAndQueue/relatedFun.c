#include "stack_queue.h"

// 栈的初始化
bool initStack(stack *s) {
    *s = (stack)malloc(sizeof(stackNode));
    if(*s == NULL) return false;
    (*s) -> data = MAXLIM;
    (*s) -> next = NULL;
    return true;
}

// 栈的判空
bool stackEmpty(stack s) {
    return s -> next == NULL;
}

// 进栈
bool stackPush(stack s, ElemType e) {
    stackNode *sItem = (stackNode *)malloc(sizeof(stackNode));
    if(sItem == NULL) return false;
    sItem -> data = e;
    sItem -> next = s -> next;
    s -> next = sItem;
    return true;
}

// 出栈
bool stackPop(stack s) {
    if(stackEmpty(s)) return false;
    stackNode *tmp = s -> next;
    s -> next = s -> next -> next;
    free(tmp);
    return true;
}

// 读取栈顶元素
ElemType stackTop(stack s) {
    if(stackEmpty(s)) return MAXLIM;
    return s -> next -> data;
}

// 队列的初始化
bool initQueue(queue *q) {
    (*q) = (queue)malloc(sizeof(struct queue));
    if(q == NULL) return false;
    (*q) -> front = (*q) -> rear = 0;
    (*q) -> capacity = Maxsize;
    (*q) -> data = (ElemType *)malloc(sizeof(ElemType) * ((*q) -> capacity));
    if((*q) -> data == NULL) return false;
    return true;
}

// 队列判空
bool queueEmpty(queue q) {
    return q -> front == q -> rear;
}

// 入队
bool queuePush(queue q, ElemType e) {
    if((q -> rear + 1) % q -> capacity == q -> front) return false;
    q -> data[q -> rear] = e;
    q -> rear = (q -> rear + 1) % q -> capacity;
    return true;
}

// 出队
bool queuePop(queue q) {
    if(queueEmpty(q)) return false;
    q -> front = (q -> front + 1) % q -> capacity;
}

// 读取队头元素
ElemType queueTop(queue q) {
    if(queueEmpty(q)) return MAXLIM;
    return q -> data[q -> front];
}

// 取小
int min(int _a, int _b) {
    return _a > _b ? _b : _a;
}

// 输出并清空栈中的元素
void outputAndclearStack(stack s) {
    while(!stackEmpty(s)) {
        printf("%d ", stackTop(s));
        stackPop(s);
    }
    printf("\n");
}

// 输出并清空队列中的元素
void outputAndclearQueue(queue q) {
    while(!queueEmpty(q)) {
        printf("%d ", queueTop(q));
        queuePop(q);
    }
    printf("\n");
}