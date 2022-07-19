/*
10.[2010统考真题]设将n(n>1)个整数存放到一维数组R中,设计一个在时间和空间两方面都尽可能高效的算法.
将R中保存的序列循环左移p(0<p<n)个位置,即将R中的数据由(X0,X1,...,Xn-1)变换为(Xp,Xp+1,...,Xn-1,X0,X1,...,Xp-1).
本题和08题的思想是一样的,只是换了题目表述而已.
即先将(X0,X1,...,Xn-1)进行整体逆置成为(Xn-1,Xn-2,...,X0);
再将前n-p个元素和后p个元素分别各自逆置成为(Xp,Xp+1,...,Xn-1,X0,X1,...,Xp-1)
或者先将前p个元素和后n-p个元素进行逆置,再对整体进行逆置
本题直接采用数组进行操作,不使用封装的顺序表
*/

#include "relatedFun.c"

void initArray(ElemType R[], int len) {
    for(int i = 0; i < len; i ++) R[i] = rand() % 100;
}

void Aoutput(ElemType R[], int len) {
    for(int i = 0; i < len; i ++) {
        printf("%d ", R[i]);
        if((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}

// ansFun1
void reverseArray(ElemType R[], int len) {
    for(int i = 0; i < len / 2; i ++) {
        ElemType tmp = R[i];
        R[i] = R[len - 1 - i];
        R[len - 1 - i] = tmp;
    }
}

// ansFun2
void moveItem(ElemType R[], int n, int p) {
    if(p > n) {
        printf("programme error\n");
        exit(1);
    }
    reverseArray(R, n);
    reverseArray(R, n - p);
    reverseArray(R + n - p, p);
}

int main(void) {
    srand((size_t)time(NULL));
    int n = rand() % 100;
    ElemType R[n];
    initArray(R, n);
    printf("Original array:\n");
    Aoutput(R, n);
    int p = rand() % n;
    printf("The distance moved p is %d\n", p);
    moveItem(R, n, p);
    printf("The array after the operation:\n");
    Aoutput(R, n);
    return 0;
}