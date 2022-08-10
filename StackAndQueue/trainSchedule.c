/*
09.火车调度站的入口处有n节硬座和软座车厢(分别用H和S表示),H和S是混杂在一起的,试着编写算法,
输出对n节车厢进行调度的操作(即入栈或出栈操作),使得所有的软座车厢都被调度到硬座车厢之前.
*/

#include "relatedFun.c"

void initTrain(char train[], int len) {
    for(int i = 0; i < len; i ++) {
        int choice = rand() % 2;
        if(choice) train[i] = 'H';
        else train[i] = 'S';
    }
    train[len] = '\0';
}

void trainSchedule(char train[]) {
    stack s;
    initStack(&s);
    int i = 0, k = 0, step = 0;
    while(train[i]) {
        if(train[i] == 'H') { // 硬座入栈
            stackPush(s, train[i]);
            printf("Step %d:Put the hard seat on the stack!\n", ++ step);
        }else { // 软座直接接入原序列即可,k值一定小于等于i,不会有信息丢失
            train[k ++] = train[i];
            printf("Step %d:Put the soft seat on the sequence!\n", ++ step);
        }
        i ++;
    }
    while(!stackEmpty(s)) {
        train[k ++] = stackTop(s);
        stackPop(s);
        printf("Step %d:Put the hard seat on the sequence!\n", ++ step);
    }
}

int main(void) {
    srand((size_t)time(NULL));
    char train[Maxsize];
    int len = rand() % Maxsize + 1;
    initTrain(train, len);
    printf("The original sequence is:\n%s\n", train);
    trainSchedule(train);
    printf("The sequence after the operation is:\n%s\n", train);
    return 0;
}