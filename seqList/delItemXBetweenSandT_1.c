/*
04.从有序的顺序表中,删除给定值在s和t之间的所有元素,若s和t的值不合法或顺序表为空则输出错误信息并返回
*/

#include "seqList.h"
#include "relatedFun.c"
#include <time.h>

// 因为序列是有序的,因此依次遍历判断各个值即可
void delItemXBetweenSandT(seqList *T, int s, int t) {
    if(s >= t) {
        printf("Invalid input algorithms!\n");
        exit(1);
    }
    if(T -> length == 0) {
        printf("The sequence list is empty!\n");
        exit(2);
    }
    unsigned int q = 0;
    for(unsigned int p = 0; p < T -> length; p ++) {
        if(T -> data[p] < s || T -> data[p] > t) T -> data[q ++] = T -> data[p];
        else{ // 分支只会进入一次
            while(p < T -> length && T -> data[p] <= t) p ++;
            if(p != T -> length) p --;
        }
    }
    T -> length = q;
}

int main(void) {
    seqList T;
    srand((size_t)time(NULL)); // 设置随机数种子
    createOrderSqlist(&T, rand() % Maxsize + 1, 100, 1);
    printf("Original sequence:\n");
    output(T);
    // 随机生成左右边界
    int s = rand() % (T.data[T.length - 1] + 10);
    int t = rand() % (T.data[T.length - 1] + 10);
    printf("The value of item between %d and %d will be deleted!\n", s, t);
    delItemXBetweenSandT(&T, s, t);
    printf("The sequence after the operation:\n");
    output(T);
    return 0;
}