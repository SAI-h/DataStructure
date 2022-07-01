/*
11.[2011统考真题]一个长度为L(L>=1)的升序序列S,处在L/2上取整位置的数称为S的中位数.
现给定两个等长的升序序列A和B,设计一个在时间和空间两方面都尽可能高效的算法,找出两个序列整体的中位数.
*/

#include "relatedFun.c"

// 法一:两个长度位len的有序递增序列的构成的总序列长度为2len,
// 那么中位数所在的位置一定是整体的第len个
// 那么只需设置两个指针pa、pb,一个指向序列A,一个指向序列B; A[i]<B[i]时,pa指针后移,否则pb后移
// 每次指针移动都会使得记录值加一,直到记录值到达len值
// 时间复杂度O(len), 空间复杂度O(1)
ElemType findTheMed_1(seqList A, seqList B, unsigned int len) {
    unsigned int pa = 0, pb = 0;
    int record = 0;
    ElemType res = -1;
    while(pa < len && pb < len) {
        record ++;
        if(A.data[pa] < B.data[pb]) {
            if(record == len) {
                res = A.data[pa];
                break;
            }
            pa ++;
        }else {
            if(record == len) {
                res = B.data[pb];
                break;
            }
            pb ++;
        }
    }
    return res;
}

// 法二: 利用好顺序表随机存取的特性
// 拿A序列的中间数和B序列的中间数相比较,若二者相等那么得到的数就是整体的中位数
// 若A序列的中间数小于B序列的中间数,则说明整体的中位数应位于A的右半侧或者B的左半侧,那么A的左半侧和B的右半侧就可以丢弃,形成新的A、B序列
// 同理,若A序列的中间数大于B序列的中间数,则整体的中位数应位于A的左半侧或者B的右半侧,再次得到新的A、B序列
// 每一次操作会剔除一半的不可能的数据,因此时间复杂度为O(loglen),空间复杂度为O(1)
// 因为我们要保证每次都得到的新序列和原序列具有相同的中位数,所以对丢弃的序列长度是有考究的
// 如现在给定一个序列: 1 2 3 4 5 6 7 它的中位数是4
// 那么序列前后剔除相同个数的数,序列的中位数不发生变化
// 如 2 3 4 5 6、3 4 5、4 它们的中位数都是4
// 但是如果前后剔除的数的个数不一致就无法保证中位数还是原来的值了
// 因此我们在对序列进行丢弃和保留的时候需要分类讨论
// 例子: 假设序列A为 1 2 4 6 8 10 (sa指向首位置,ea指向末尾值)
//          序列B为 11 13 15 17 19 20 (sb指向首位置,eb指向末尾值)
// 那么A的中间位置为ma=(0+5)/2=2, B的中间位置为mb=(0+5)/2=2
// 因为A[2] < B[2], 因此需要丢弃A的左半侧以及B的右半侧, 
// B的中间数的右边有三个数,A的中间数左边有两个数,根据定义这些数都是不可能称为中位数的数,故B右侧的三个数必定是会被丢弃掉的
// 因为要保证中位数仍是原来的中位数,那么根据对称性A的左侧三个数也要被丢弃,也就是说这里无法保留A原先的中间数
// 即：执行的会是:sa = ma + 1, eb = mb的操作,这样就保证了整体序列两侧都丢弃掉了同样数目的值,中位数不发生变化
// 一言以蔽之:对A、B序列进行删除一半的操作时,删除的数目要保证最大且一致,这样也同时保证了我们每次操作时的A、B序列长度一致
ElemType findTheMed_2(seqList A, seqList B, unsigned int len) {
    int sa = 0, ea = len - 1, sb = 0, eb = len - 1;
    while(sa < ea || sb < eb) {
        int ma = (sa + ea) / 2, mb = (sb + eb) / 2;
        if(A.data[ma] < B.data[mb]) {
            if((ea - sa + 1) % 2) // 序列的长度为奇数(奇数时中间数的左右两侧数据数目一致,令相应指针等于中间数的位置值即可剔除一半元素)
                sa = ma, eb = mb;
            else                  // 序列的长度为偶数(偶数时中间数左侧数据数目比右侧数目少一,为保证剔除数目一致,需让较小的一方指针挪至中间数位置的后一个位置)
                sa = ma + 1, eb = mb;
        }else if(A.data[ma] > B.data[mb]) { // 与上分支同理
            if((eb - sb + 1) % 2)
                sb = mb, ea = ma;
            else
                sb = mb + 1, ea = ma;
        }
        else return A.data[ma];
    }
    return min(A.data[sa], B.data[sb]);
}

int main(void) {
    seqList A, B;
    srand((size_t)time(NULL));
    unsigned int len = rand() % 100;
    printf("The length of the sequence is: %d\n", len);
    createOrderSqlist(&A, len, rand() % 100, 0);
    createOrderSqlist(&B, len, rand() % 100, 0);
    printf("sequence A:\n");
    output(A);
    printf("sequence B:\n");
    output(B);
    printf("The median found by method_1 is %d\n", findTheMed_1(A, B, len));
    printf("The median found by method_2 is %d\n", findTheMed_2(A, B, len));
    return 0;
}