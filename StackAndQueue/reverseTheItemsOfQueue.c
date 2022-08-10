/*
05.Q是一个队列,S是一个空栈,实现将队列中的元素逆置的算法
*/

#include "relatedFun.c"

void randomQueue_ouput(queue q) {
    int len = min(rand() % q -> capacity + 1, q -> capacity - 1);
    printf("Elements in the queue:\n");
    while(len --) {
        ElemType x = rand() % Maxsize;
        printf("%d ", x);
        queuePush(q, x);
    }
    printf("\n");
}

// 利用栈s逆置队列q中的元素
void reverse(queue q, stack s) {
    while(!queueEmpty(q)) { // 将队列q中的元素逐个放入栈s中
        ElemType t = queueTop(q);
        queuePop(q);
        stackPush(s, t);
    }
    while(!stackEmpty(s)) { // 将栈s中的元素逐个放回队列q中
        ElemType t = stackTop(s);
        stackPop(s);
        queuePush(q, t);
    }
}

int main(void) {
    srand((size_t)time(NULL));
    queue Q;
    initQueue(&Q);
    randomQueue_ouput(Q); // 向队列中填入随机个数的随机数并输出原队列
    stack S;
    initStack(&S);
    reverse(Q, S);
    printf("The queue after the operation is :\n");
    outputAndclearQueue(Q);
    return 0;
}