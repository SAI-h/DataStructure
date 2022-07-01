/*
12.[2013统考真题]已知一个整数序列A=(a0,a1,...,an-1),其中0<=ai<n(0<=i<n).
若存在ap1=ap2=...=apm=x且m>n/2(0<=pk<n,1<=k<=m),则称x为A的主元素.
例如A=(0,5,5,3,5,7,5,5),则5为主元素;又如:A=(0,5,5,3,5,1,5,7),则A没有主元素.
设计高效的算法,找出主元素并输出,若没有则输出-1
解释:
即找出序列中出现次数大于序列长度一半的元素
*/

#include "relatedFun.c"

// 法一: 空间换时间,序列中元素的值域在[0,n]上,开一个大小为n+1的辅助空间,用来记录下标所对应的元素的个数
// 当下表记录的个数值超过n/2直接返回即可, 因为长度为n的序列中不可能存在两个或两个以上次出现数超过n/2的元素
// 时间复杂度O(n), 空间复杂度O(n)
ElemType findMainItem_1(seqList T, int n) {
    int *record = (int *)malloc(sizeof(int) * (n + 1));
    for(int i = 0; i <= n; i ++) record[i] = 0;
    for(int i = 0; i < T.length; i ++){
        int item = T.data[i];
        record[item] ++;
        if(record[item] > n / 2) return item;
    }
    return -1;
}

// 法二:
// 先说明算法的策略:从前向后依次扫描数组元素,标记出一个可能成为主元素的元素Num,然后重新计数,确定Num是否为主元素
// 算法分为以下两步:
// 1.选择候选的主元素.依次扫描所给的数组中的每个整数,将第一个遇到的整数Num保存到c中,记录Num出现的次数为1;
//    若遇到的下一个整数仍是Num,则计数加一,否则计数减一.当计数减到0时,将遇到的下一个整数保存到c中,计数重新记为1,开始新的计数
//    即从当前位置开始重复上述过程,直到扫描全部数组元素
// 2.判断c中元素是否时真正的主元素.再次扫描该数组,统计c元素出现的次数,若大于n/2,则是主元素;否则不存在主元素.
// 下面是对上述算法的一点理解:
// 若一个元素是主元素,那么他在序列中出现的次数大于n/2,即该元素的出现个数大于其它元素出现的个数之和
// 其实我们可以将元素分为两大类:主元素以M表示,其他元素用O表示,主元素有n/2+1个,那么其它元素有n-n/2-1个.
// 在执行的过程中我们会将我们当前认为是主元素的的价值视为1,会将我们当前认为不是主元素的代价视为-1,
// 但是注意视为主元素的值并不说明这就是主元素,只是我们设置的一个可能值
// 若当前序列的计数等于0,说明在当前阶段其他元素个数恰好能和我们之前选定的主元素个数抵消
// 那么我们从这里进行截断,只观察当前位置的后续值,不会影响主元素的值
// 取元素分布最极端的两种情况:最集中和最分散,会得到序列1和序列2
// 序列1: OOO...OMMMMM...M 序列2:MOMOMO...MOM
// 均能模拟出最终主元素的值为M
ElemType findMainItem_2(seqList T, int n) {
    int cnt = 1; // 计数
    int c = T.data[0]; // 记录预设的主元素
    for(int i = 1; i < n; i ++) {
        if(T.data[i] == c) cnt ++;
        else {
            if(cnt > 0) cnt --;
            else {
                c = T.data[i];
                cnt = 1;
            }
        }
    }
    cnt = 0;
    for(int i = 0; i < n; i ++) cnt += T.data[i] == c;
    if(cnt > n / 2) return c;
    return -1;
}

int main(void) {
    srand((size_t)time(NULL));
    int n = rand() % 100;
    printf("Both the length and the domain are: %d\n", n);
    seqList T;
    randomSqList(&T, n, n);
    printf("The sequence:\n");
    output(T);
    printf("The main item found by findMainItem_1 is: %d\n", findMainItem_1(T, n));
    printf("The main item found by findMainItem_1 is: %d\n", findMainItem_2(T, n));
    return 0;
}