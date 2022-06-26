/*
02.实现顺序表的逆置操作,空间复杂度为O(1)
*/

#include "seqList.h"
#include "relatedFun.c"
#include <time.h>

void reverseSeq(seqList *T) {
    for(unsigned int i = 0; i < T -> length / 2; i ++) {
        ElemType tmp = T -> data[i];
        T -> data[i] = T -> data[T -> length - 1 - i];
        T -> data[T -> length - 1 - i] = tmp;
    }
}

int main(void) {
    seqList T;
    srand((size_t)time(NULL)); // 设置随机数种子
    if(!randomSqList(&T, rand() % Maxsize + 1, 100)){
        printf("Program Error!\n");
        return 0;
    }
    printf("Original sequence:\n");
    output(T);
    reverseSeq(&T);
    printf("the sequence after the operation:\n");
    output(T);
    return 0;
}