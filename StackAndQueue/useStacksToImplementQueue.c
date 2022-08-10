/*
06.用两个栈来模拟实现一个队列

分析:栈s1用来进行输入,进来的元素优先放到s1的栈顶位置,栈s2进行输出,所有元素出栈(队)的位置都是在s2的栈顶位置.
在第一次出队操作前,s2为空,若要进行出队操作,即获取到的是s1的栈底元素,那么此时需要将s1中的元素依次出栈,再向s2入栈,
此时要出队的元素就到了s2的栈顶位置,这时只需要对s2进行出栈操作即可完成出队的操作了.
完成出队的操作后无需将s2中的元素(若有)重新转移到s1,下一次出队操作时,仅仅需要再次对s2进行出栈操作即可.
但是s1向s2中转移时需要注意保证s2必须为空.s2中的元素是早先入队(相较于s1中的元素)的元素,也应该早出队,
若s2不空就将s1中的元素纳入,那么晚入队的元素会比之前的元素更早出队.
*/

#include "relatedFun.c"

// 模拟的队列
typedef struct _queue{
    stack s1; // 输入栈
    stack s2; // 输出栈
}*_queue;

// 队列的初始化
bool init(_queue *q) {
    *q = (_queue)malloc(sizeof(struct _queue));
    if(*q == NULL) return false;
    stack s1, s2;
    initStack(&s1), initStack(&s2);
    (*q) -> s1 = s1, (*q) -> s2 = s2;
    return true;
}

// 判断栈是否满(为了程序的完整性,需要对栈进行判满,实现的栈是以链表的方式存储的,一般情况下不会满,所以默认返回false,后续若栈结构发生变化可更改代码)
bool stackOverflow(stack s) {
    /*
    code area
    */
   return false;
}

// 判断队列是否为空
bool queue_empty(_queue q) {
    return stackEmpty(q -> s1) && stackEmpty(q -> s2);
}

// 将元素x入队
bool en_queue(ElemType x, _queue q) {
    if(!stackOverflow(q -> s1)) { // 如果输入栈没有空,那么就向输入栈中压入元素
        stackPush(q -> s1, x);
        return true;
    }else if(stackEmpty(q -> s2)) { // 输入栈满,在保证输出栈为空的前提下,才能先将输入栈中的元素全部压入输出栈,不然会失序
        // 若s2满或s1为空则不再转移元素
        while(!(stackEmpty(q -> s1) || stackOverflow(q -> s2))) {
            stackPush(q -> s2, stackTop(q -> s1));
            stackPop(q -> s1);
        }
        stackPush(q -> s1, x);
        return true;
    }
    return false; // 输入栈满,且输出栈不空,则没有办法进行入队操作
}

// 出队,将出队元素存储通过x带回
bool de_queue(ElemType *x, _queue q) {
    *x = MAXLIM;
    if(queue_empty(q)) return false; // 队列空,无元素
    if(!stackEmpty(q -> s2)) { // 输出栈不空,输出其中元素即可
        *x = stackTop(q -> s2);
        stackPop(q -> s2);
        return true;
    }else if(!stackEmpty(q -> s1)){ // 输出栈为空,则下个出队元素再输入栈栈底,那么将输入栈中元素转移到输出栈
        while(!(stackEmpty(q -> s1) || stackOverflow(q -> s2))) {
            stackPush(q -> s2, stackTop(q -> s1));
            stackPop(q -> s1);
        }
        if(!stackEmpty(q -> s1)) return false; // 输入栈不空,说明没有完成转移的动作,这说明s2满了,无法转移,所以操作失败
        else { // 转移操作成功
            *x = stackTop(q -> s2);
            stackPop(q -> s2);
            return true;
        }
    }
    return false;
}

int main(void) {
    _queue q;
    init(&q);
    /*test code*/
    printf("--------------test1---------------\n");
    for(int i = 1; i <= 10; i ++) en_queue(i, q);
    while(!queue_empty(q)) {
        ElemType x;
        de_queue(&x, q);
        printf("%d ", x);
    }
    printf("\n--------------test2---------------\n");
    ElemType x;
    de_queue(&x, q);
    printf("%d", x);
    printf("\n--------------test3---------------\n");
    for(int i = 1; i <= 10; i ++) {
        if(i % 3 == 0) {
            int x;
            de_queue(&x, q);
            printf("%d ", x);
        }else en_queue(i, q);
    }
    free(q);
    return 0;
}

/*
--------------test1---------------
1 2 3 4 5 6 7 8 9 10 
--------------test2---------------
2139062143
--------------test3---------------
1 2 4
*/