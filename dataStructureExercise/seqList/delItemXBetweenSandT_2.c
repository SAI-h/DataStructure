/*
05.从顺序表中,删除给定值在s和t之间的所有元素,若s和t的值不合法或顺序表为空则输出错误信息并返回
*/

#include "seqList.h"
#include "relatedFun.c"
#include <time.h>

// 同03和04, 这里采用快慢指针的思想
void delItemXBetweenSandT(seqList *T, int s, int t) {
    if(s >= t) {
        printf("Invalid input algorithms!\n");
        exit(1);
    }
    if(T -> length == 0) {
        printf("The sequence list is empty!\n");
        exit(2);
    }
    unsigned int p = 0, q = 0;
    while(p < T -> length) {
        if(T -> data[p] < s ||  T -> data[p] > t)
            T -> data[q ++] = T -> data[p];
        p ++;
    }
    T -> length = q;
}

int main(void) {
    seqList T;
    srand((size_t)time(NULL)); // 设置随机数种子
    randomSqList(&T, rand() % Maxsize + 1, 100);
    printf("Original sequence:\n");
    output(T);
    int s = rand() % 100;
    int t = rand() % 100;
    printf("The value of item between %d and %d will be deleted!\n", s, t);
    delItemXBetweenSandT(&T, s, t);
    printf("The sequence after the operation:\n");
    output(T);
    return 0;
}