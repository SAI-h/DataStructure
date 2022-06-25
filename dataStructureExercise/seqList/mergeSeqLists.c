/*
07.将两个有序的顺序表合并为一个有序的顺序表,并由作为函数返回值返回
*/

#include "seqList.h"
#include "relatedFun.c"
#include <time.h>

seqList mergeSeqLists(seqList *T, seqList *Q) {
    seqList res;
    initSqList(&res);
    unsigned int i = 0, j = 0;
    while(i < T -> length && j < Q -> length) {
        if(T -> data[i] < Q -> data[j])
            res.data[res.length ++] = T -> data[i ++];
        else
            res.data[res.length ++] = Q -> data[j ++];
    }
    // 两个while至多仅会执行其中一个
    while(i < T -> length) res.data[res.length ++] = T -> data[i ++];
    while(j < Q -> length) res.data[res.length ++] = Q -> data[j ++];
    return res;
}

int main(void) {
    seqList T, Q;
    srand((size_t)time(NULL));
    printf("Original sequence1:\n");
    createOrderSqlist(&T, rand() % Maxsize + 1, 100, 1);
    output(T);
    printf("Original sequence2:\n");
    createOrderSqlist(&Q, rand() % Maxsize + 1, 100, 1);
    output(Q);
    seqList P = mergeSeqLists(&T, &Q);
    printf("The sequence after the opreation:\n");
    output(P);
    return 0;
}