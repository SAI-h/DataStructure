#include <stdio.h>
#include <stdlib.h>

#define bool int 
#define true 1
#define false 0
#define Maxsize 100
#define ElemType int
#define MAXLIM 0x7f7f7f7f

// 静态分配的顺序表
typedef struct {
    ElemType data[Maxsize];
    unsigned int length;
}seqList;

// bool initSqList(seqList *T);
// bool randomSqList(seqList *T, unsigned int len);