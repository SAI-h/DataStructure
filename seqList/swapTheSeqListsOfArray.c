/*
08.已知在一个数组A[m+n]中依次存放着两个线性表(a1,a2,...,am)和(b1,b2,...,bn).
编写一个函数,将数组中的两个顺序表的位置互换,即将(b1,b2,...,bn)放在(a1,a2,...,am)的前面
*/

#include "seqList.h"
#include "relatedFun.c"
#include <time.h>

void outputArray(ElemType A[], int len) {
    for(unsigned int i = 0; i < len; i ++) {
        printf("%d ", A[i]);
        if((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}

// 将数组l位置到r位置上的数进行逆置
void reverse(ElemType A[], int l, int r) {
    for(int i = 0; i < (r - l + 1) / 2; i ++) {
        ElemType tmp = A[l + i];
        A[l + i] = A[r - i];
        A[r - i] = tmp;
    }
}

// 法一: 在开个数组做临时中间数组, 将A中[m~m+n-1]的元素先拷贝到B[0~n-1],再将A[0~m-1]的元素拷贝到B[m~m+n-1]
// 然后再把A中元素用B中元素替换掉
// 时间复杂度:O(m+n), 空间复杂度O(m+n)
void swapTheLists_1(ElemType A[], unsigned int m, unsigned int n) {
    ElemType B[m + n];
    unsigned int k = 0;
    for(unsigned int i = m; i < m + n; i ++) B[k ++] = A[i];
    for(unsigned int i = 0; i < m; i ++) B[k ++] = A[i];
    for(unsigned int i = 0; i < n + m; i ++) A[i] = B[i];
}

// 法二: 找性质,无需额外辅助空间,
// 先将数组中的全部元素(a1,a2,...,am,b1,b2,...,bn)原地逆置为(bn,bn-1,bn-2,...,am,am-1,...,a1);
// 在对前n个元素和后m个元素分别使用逆置算法,即可得到(b1,b2,...,bn,a1,a2,...am)
// 这是先整体逆置再局部逆置的做法;当然先局部逆置再整体逆置也是可行的
// 时间复杂度:O(m+n), 空间复杂度O(1)
void swapTheLists_2(ElemType A[], unsigned int m, unsigned int n) {
    reverse(A, 0, m + n - 1);
    reverse(A, 0, n - 1);
    reverse(A, n, m + n - 1);
    /*
    也可以是:
    reverse(A, 0, m - 1);
    reverse(A, m, m + n - 1);
    reverse(A, 0, n + m - 1);
    */
}

int main(void) {
    seqList a, b;
    srand((size_t)time(NULL)); // 设置随机数种子

    printf("The values of the sequence list a are:\n");
    randomSqList(&a, rand() % Maxsize, 100);
    output(a);
    unsigned int m = a.length;
    printf("The length m of a is: %d\n", m);

    printf("The values of the sequence list b are:\n");
    randomSqList(&b, rand() % Maxsize, 100);
    output(b);
    unsigned int n = b.length;
    printf("The length n of b is: %d\n", n);

    ElemType A[m + n];
    for(unsigned int i = 0; i < m; i ++) A[i] = a.data[i];
    for(unsigned int j = 0, i = m; i < m + n; i ++, j ++) A[i] = b.data[j];
    printf("Original Array:\n");
    outputArray(A, m + n);
    swapTheLists_2(A, m, n);
    printf("The array after the operation:\n");
    outputArray(A, n + m);
    return 0;
}