/*
04.希望循环队列中的元素都能够得到利用,则需要设置一个标志域tag,并以tag的值为0或1来区分头指针和尾指针相同时
的队列状态是"空"还是"满",试编写此结构的入队和出队算法
*/

#include <stdio.h>
#include <stdlib.h>

#define bool int 
#define true 1
#define false 0
#define Maxsize 10
#define ElemType int
#define MAXLIM 0x7f7f7f7f

// 带标记域的循环队列
typedef struct cyclic_queue {
    ElemType data[Maxsize];
    int front; // 头指针
    int rear; // 尾指针
    int capacity; // 队列的最大容量
    int tag; // 判断队列是否为空
}*cyclic_queue;

// 初始化
bool initQueue(cyclic_queue *q) {
    (*q) = (cyclic_queue)malloc(sizeof(struct cyclic_queue));
    if(q == NULL) return false;
    (*q) -> capacity = Maxsize;
    (*q) -> front = (*q) -> rear = 0;
    (*q) -> tag = 0;
    return true;
}

// 入队
bool queuePush(cyclic_queue q, ElemType e) {
    if(q -> tag == 1) return false; // 队列已满
    q -> data[q -> rear] = e;
    q -> rear = (q -> rear + 1) % (q -> capacity);
    if(q -> rear == q -> front) q -> tag = 1; // 加入元素之后,队列满
    return true;
}

// 出队, 带回队头元素
bool queuePop(cyclic_queue q, ElemType *top) {
    if(q -> front == q -> rear && q -> tag == 0) return false;
    *top = q -> data[q -> front];
    q -> front = (q -> front + 1) % (q -> capacity);
    if(q -> tag == 1) q -> tag = 0; // 之前队列是满的,但是有一个元素出队了,则该队列现在不满
    return true;
}

// 循环队列的可视化
void queueShow(cyclic_queue q) {
    for(int i = 0; i < q -> capacity; i ++) {
        if(q -> front < q -> rear) {
            if(i < q -> rear && i >= q -> front) printf(" | %d", q -> data[i]);
            else printf(" | NULL");
        }else if(q -> front > q -> rear){
            if(i < q -> rear || i >= q -> front) printf(" | %d", q -> data[i]);
            else printf(" | NULL");
        }else {
            if(q -> tag) printf("| %d", q -> data[i]);
            else printf(" | NULL");
        }
        if(i == q -> front && i == q -> rear) printf(" (front & rear)");
        else if(i == q -> front) printf(" (front)");
        else if(i == q -> rear) printf(" (rear)");
    }
    printf(" |\n");
}

int main(void) {
    cyclic_queue q;
    bool result = initQueue(&q);
    if(! result) {
        printf("The queue initialization failed!");
        exit(1);
    }
    printf("The original queue is:\n");
    queueShow(q);
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
                    printf("The queue is full!\n");
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
    free(q);
    return 0;
}