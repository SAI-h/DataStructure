/*
06.从有序顺序表中删除所有重复的元素,使得表中所有的元素值各不相同
*/

#include "seqList.h"
#include "relatedFun.c"
#include <time.h>

// 实现时间复杂度在O(n)
void delDuplicateItem(seqList *T) {
    unsigned int p = 0, q = 0, last = -MAXLIM;
    while(p < T -> length) {
        if(T -> data[p] != last) {
            T -> data[q ++] = T -> data[p];
            last = T -> data[p];
        }
        p ++;
    }
    T -> length = q;
}

int main(void) {
    seqList T;
    srand((size_t)time(NULL)); // 设置随机数种子
    createOrderSqlist(&T, rand() % Maxsize + 1, 100, 1);
    printf("Original sequence:\n");
    output(T);
    delDuplicateItem(&T);
    printf("The sequence after the operation:\n");
    output(T);
    return 0;
}