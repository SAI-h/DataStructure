/*
09. 给定一个有序递增的顺序表。要求高效查找值为x的元素,
若查找到了,(如果有后继元素的话)则将其与后继元素交换;
若找不到,则将其插入表中,且表中依旧有序
*/

#include "seqList.h"
#include "relatedFun.c"
#include <time.h>

// 二分查找
unsigned int BinSearch(seqList T, ElemType findItem) {
    unsigned int l = 0, r = T.length - 1;
    while(l < r) {
        unsigned mid = (l + r) / 2;
        if(T.data[mid] == findItem) return mid;
        else if(T.data[mid] < findItem) l = mid + 1;
        else r = mid - 1;
    }
    return r;
}

// 顺序表的插入操作
bool insert(seqList *T, ElemType insertItem) {
    if(T -> length + 1 > Maxsize) return false;
    /* 这样写有bug
    for(unsigned int i = T -> length; i > poi; i --)
        T -> data[i] = T -> data[i - 1];
    T -> data[poi] = insertItem;
    */
    // 索性直接按元素大小好了
    int i = T -> length;
    for(; i - 1 >= 0 && T -> data[i - 1] > insertItem; i --)
         T -> data[i] = T -> data[i - 1];
    T -> data[i] = insertItem;
    T -> length ++;
    return true;
}

int main(void) {
    seqList T;
    srand((size_t)time(NULL)); // 设置随机数种子
    createOrderSqlist(&T, rand() % Maxsize + 1, 100, 0);
    printf("Original sequence:\n");
    output(T);
    ElemType findItem = rand() % (T.data[T.length - 1] + 10);
    printf("The element looking for is: %d\n", findItem);
    int res = BinSearch(T, findItem);
    if(T.data[res] == findItem) {
        printf("The element is in the sequence!\n");
        if(res < T.length - 1) {
            T.data[res] = T.data[res + 1];
            T.data[res + 1] = findItem;
        }
    }else {
        printf("The element is not in the sequence!\n");
        if(!insert(&T, findItem)) {
            printf("The list is full!\n");
            return 0;
        }
    }
    printf("The sequence after the operation:\n");
    output(T);
    return 0;
}