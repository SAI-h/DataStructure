/*
03.共享栈的实现：设有两个栈s1和s2都采用顺序栈方式,并共享一个存储区[0, Maxsize-1],
为了尽量利用空间,减少溢出的可能,可采用栈顶相向,迎面增长的存储方式.试设计入栈、出栈操作.
*/

#include <stdio.h>
#include <stdlib.h>

#define bool int 
#define true 1
#define false 0
#define Maxsize 10
#define ElemType int
#define MAXLIM 0x7f7f7f7f

typedef struct sharing_stack {
    ElemType dataSpace[Maxsize]; // 共享存储空间
    int top[2]; // 两个栈顶指针
}*sharing_stack;

// 共享栈的初始化
bool initStack(sharing_stack *s) {
    (*s) = (sharing_stack)malloc(sizeof(struct sharing_stack));
    if((*s) == NULL) return false;
    (*s) -> top[0] = -1;
    (*s) -> top[1] = Maxsize;
    return true;
}

// 号为id的栈的判空
bool stackEmpty(int id, sharing_stack s) {
    if(id == 0) return s -> top[id] == -1;
    return s -> top[id] == Maxsize;
}

// 号为id的栈的入栈
bool stackPush(int id, sharing_stack s, ElemType e) {
    if(s -> top[0] + 1 == s -> top[1]) return false; // 栈满
    if(id == 0) 
        s -> dataSpace[++ (s -> top[id])] = e;
    else 
        s -> dataSpace[-- (s -> top[id])] = e;
    return true;
}

// 号为id的栈的出栈
bool stackPop(int id, sharing_stack s, ElemType *top) { // 带出栈顶元素
    if(stackEmpty(id, s)) { // 栈空
        *top = MAXLIM;
        return false;
    }
    if(id == 0) 
        *top = s -> dataSpace[s -> top[0] --];
    else
        *top = s -> dataSpace[s -> top[1] ++];
    return true;
}

// 可视化栈视图
void stackShow(sharing_stack s) {
    for(int i = 0; i < Maxsize; i ++) {
        if(i > s -> top[0] && i < s -> top[1]) printf(" | NULL");
        else printf(" | %d", s -> dataSpace[i]);
        if(i == s -> top[0]) printf(" (top_0)");
        if(i == s -> top[1]) printf(" (top_1)");
    }
    printf(" |\n");
}

int main(void) {
    sharing_stack s;
    bool result = initStack(&s);
    if(! result) {
        printf("The stack initialization failed!");
        exit(1);
    }else {
        printf("The original stack is:\n");
        stackShow(s);
        char ch[2];
        do {
            printf("Operation list:\n");
            printf("1.Push X into the stack_0.\t\t\t2.Push X into the stack_1.\n");
            printf("3.Remove the top element of the stack_0.\t4.Remove the top element of the stack_1.\n");
            printf("Please enter the operation to be performed:");
            char choice[2];
            scanf("%s", choice);
            switch (choice[0])
            {
                case '1': 
                case '2': {
                    printf("Please enter the element x:");
                    int x;
                    scanf("%d", &x);
                    if(stackPush(choice[0] - '1', s, x))  
                        printf("Execute successfully!\n");
                    else
                        printf("The stack is full!\n");
                    break;
                }
                case '3':
                case '4': {
                    int top;
                    if(stackPop(choice[0] - '3', s, &top))
                        printf("Execute successfully!\n"
                        "The element at the top of the stack that is removed is %d!\n", top);
                    else
                        printf("The stack is empty!\n");
                    break;
                }
            }
            printf("The stack after the operation is:\n");
            stackShow(s);
            printf("Exit? (y or n):");
            scanf("%s", ch);
        }while(ch[0] != 'y');
    }
    free(s);
    return 0;
}