#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// 初始化一个顺序表
bool initSqList(seqList *T);
// 填入随机数据,以初始化顺序表 len是填充的长度, range是生成随机数的范围
bool randomSqList(seqList *T, unsigned int len, int range);
// 按顺序输出顺序表中的元素值
void output(seqList T);
// 初始化成数据是随机的有序的顺序表, choice:0,序列必须严格递增, 1:序列可以不严格递增
bool createOrderSqlist(seqList *T, unsigned int len, int range, int choice);
// 取出两个元素中的较大值
ElemType max(ElemType Item1, ElemType Item2);
// 取出两个元素中的较小值
ElemType min(ElemType Item1, ElemType Item2);