/*
01.从顺序表中删除的一个最小值并用函数返回，
空出的位置由最后一个元素填补，若顺序表为空则显示出错信息并退出运行
*/

#include "relatedFun.c"

ElemType findAndDelTheMin(seqList *T) {
    // 若为空表显示出错信息,并退出
    if(T -> length == 0) {
        printf("This is an empty list!\n");
        exit(1);
    }
    // 找到最小值和最小值所在的位置
    ElemType minv = MAXLIM, delIdx = 0;
    for(unsigned int i = 0; i < T -> length; i ++) {
        if(minv > T -> data[i]) {
            minv = T -> data[i];
            delIdx = i;
        }
    }
    // 用末尾值取缔最小值所在位置上的值
    T -> data[delIdx] = T -> data[-- T -> length];
    return minv;
}

int main(void) {
    seqList T;
    srand((size_t)time(NULL)); // 设置随机数种子
    if(!randomSqList(&T, rand() % Maxsize + 1, 100)){
        printf("Program Error!\n");
        return 0;
    }
    // 输出原始的顺序表
    printf("Original sequence:\n");
    output(T);
    ElemType ans = findAndDelTheMin(&T);
    printf("The minimun value in the sequence list is: %d\n", ans);
    printf("The sequence after the operation:\n");
    output(T);
    return 0;
}