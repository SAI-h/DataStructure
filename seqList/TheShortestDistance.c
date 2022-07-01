/*
14.[2022统考真题]定义三元组(a,b,c)的距离D=|a-b|+|b-c|+|c-a|.给定三个非空集合S1、S2和S3,按升序分别存储在3个数组中.
请设计一个尽可能高效的算法,计算并输出所有可能的三元组(a,b,c)(a∈S1,b∈S2,c∈S3)中的最小距离.
例如:S1={-1,0,9}, S2={-25,-10,10,11}, S3={2,9,17,30,41}的最小距离是2,对应的三元组是(9,10,9).
 */

#include "relatedFun.c"

// 暴力解法的时间复杂度在O(|S1|*|S2|*|S3|),这不是高效的解法
// 因此对题目进行分析:
// 若我们获取到的三元组为(a,b,c)
// 不妨设a<=b<=c, 那么D=|a-b|+|b-c|+|c-a|=(b-a)+(c-b)+(c-a)=2*(c-a) 
// 也就是是我们得到的距离D只与三元组中的最大值和最小值相关
// 若想要最小化D,就得最小化三元组内最大值和最小值之间差,
// 贪心地想,最大值和最小值如果是相邻近的,那么差值也会越小
// 而S1,S2,S3是升序排列的,因此很容易就可以获得由邻近元素组成的三元组
// 设置三个指针,pa指向S1首位、pb指向S2首位、pc指向S3首位
// 取出pa、pb、pc所指向的最大值和最小值,用二者的差对D进行更新
// 向后移动pa、pb、pc中指向最小元素的指针,以获取下一个由邻近元素组成的三元组
// 时间复杂度为O(|S1|+|S2|+|S3|),空间复杂度为O(1)
int findTheShortestDistance(seqList S1, seqList S2, seqList S3) {
    int res = MAXLIM;
    int l1 = S1.length, l2 = S2.length, l3 = S3.length;
    int pa = 0, pb = 0, pc = 0;
    while(pa < l1 && pb < l2 && pc < l3) {
        int maxv = max(max(S1.data[pa], S2.data[pb]), S3.data[pc]);
        int minv = min(min(S1.data[pa], S2.data[pb]), S3.data[pc]);
        res = min(res, 2 * (maxv - minv));
        if(minv == S1.data[pa]) pa ++;
        else if(minv == S2.data[pb]) pb ++;
        else pc ++;
    }
    return res;
}

int main(void) {
    seqList S1, S2, S3;
    srand((size_t)time(NULL));
    createOrderSqlist(&S1, rand() % Maxsize, rand() % 100, 0);
    createOrderSqlist(&S2, rand() % Maxsize, rand() % 100, 0);
    createOrderSqlist(&S3, rand() % Maxsize, rand() % 100, 0);
    printf("The sequence S1:\n");
    output(S1);
    printf("The sequence S2:\n");
    output(S2);
    printf("The sequence S3:\n");
    output(S3);
    printf("The shortest distance is %d\n", findTheShortestDistance(S1, S2, S3));
    return 0;
}