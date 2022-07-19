/*
13.[2018统考真题]给定一个含n(n>=1)个整数的数组,设计一个在时间上尽可能高效的算法,找出数组中未出现的最小正整数.
*/

#include "relatedFun.c"

ElemType find_max(seqList T) {
    ElemType res = -MAXLIM;
    for(int i = 0; i < T.length; i ++)
        res = max(res, T.data[i]);
    return res;
}

// 空间换时间,开一个Amax+2大的辅助空间,记录对应下标下的数值是否存在,然而从1开始向Amax+1访问,找到第一个不存在的数值即可
// 其中Amax是数组中最大的数
// 时间复杂度O(n), 空间复杂度O((max(i=0~n-1)T[i]) + 2)
ElemType find_leastPositiveInt(seqList T, int len) {
    if(len <= 0) return 1;
    bool *R = (bool *)malloc(sizeof(bool) * (len + 2));
    for(int i = 1; i <= len + 1; i ++) R[i] = false;
    for(int i = 0; i < T.length; i ++) if(T.data[i] > 0) R[T.data[i]] = true;
    for(int i = 1; i <= len + 1; i ++) if(R[i] == false) return i;
    return -1;
}

int main(void) {
    srand((size_t)time(NULL));
    int n = rand() % 100;
    printf("The length of array is: %d\n", n);
    seqList T;
    randomSqList(&T, n, rand() % 100);
    printf("The sequence:\n");
    output(T);
    // 找到数组中元素的上界Amax,分配Amax+2个辅助空间
    ElemType Amax = find_max(T);
    ElemType ans = find_leastPositiveInt(T, Amax);
    printf("The least Positive Integer is: %d\n", ans);
    return 0;
}