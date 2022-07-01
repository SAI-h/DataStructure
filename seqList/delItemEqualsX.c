/*
03.删除顺序表中所有值为x的元素,时间复杂度为O(n),空间复杂度为O(1)
分析:
如果采用暴力的办法,即判断当前元素值是否为x;如果是,则依次将后续元素向前挪动一位,则时间复杂度为O(n^2),
因此需要改进算法 ————
这里可以用到快慢指针的想法,我们所知道的顺序表中不等于x的元素个数一定是小于等于整体的元素个数,
且对于任意一个前缀序列都满足该性质,
即：若顺序表表长为len, 当k属于[0, len-1]时, 在[0,k]中均有不等于x的个数小于等于k+1的性质.
因此我们可以设置两个指针i,j; i用来遍历整个序列,j用来记录不等于x的元素个数(也可以视为删除后的新序列的最新位置),
当i指向的位置不为x时,则j指针记录该值且后移;否则j指针不后移,等待i指向不为x的值或i的遍历结束;
这样就保证了j的移动速度慢于i,
在当前线性表上记录到的值不会出现不合理的覆盖情况
*/

#include "relatedFun.c"

// 法一
void delItemX_1(seqList *T, int delItem) {
    unsigned int i = 0, j = 0;
    while(i < T -> length) {
        if(T -> data[i] != delItem)
            T -> data[j ++] = T -> data[i];
        i ++;
    }
    T -> length = j;
}

// 法二: 若j值记录的是等于x的元素个数,那么当i遍历到的数值不为x的时候,j值就显示的是当前元素(i)之前有多少元素会被删除
// 在顺序表上的删除操作时是以后续元素的前移的方式实现的,对于当前i位置前面总共会有j个位置会被删除,那么自己的位置应该要往前挪动j个位置
// 这种想法相较于法一更不容易理解,更反人类
void delItemX_2(seqList *T, int delItem) {
    unsigned int i = 0, j = 0;
    while(i < T -> length) {
        if(T -> data[i] == delItem) j ++;
        else T -> data[i - j] = T -> data[i];
        i ++;
    }
    T -> length -= j;
}

// 法三: 设置两个指针,i指向起始位置,j(永远动态地)指向末尾位置;
// i从起始位置想末尾位置遍历,如果i指向的值是x,则将其与末尾位置j指向的值交换(不用实际实现交换操作),j再自减,这样就实现了对x元素的删除操作
// 当两个指针相遇的时候就停下来了
// 这是个很有趣的做法,只是原序列中元素的相对位置会发生变化
void delItemX_3(seqList *T, int delItem) {
    unsigned int i = 0, j = T -> length - 1;
    while(i < j) {
        if(T -> data[i] == delItem) {
            T -> data[i] = T -> data[j];
            j --;
        }
        i ++;
    }
    T -> length = i;
}

int main(void) {
    seqList T, Q;
    srand((size_t)time(NULL)); // 设置随机数种子
    if(!randomSqList(&T, rand() % Maxsize, 10)){ // 缩小随机数的值域,使值的取值更集中
        printf("Program Error!\n");
        return 0;
    }
    Q = T; // 测试三种方法,需要对T进行恢复
    printf("Original sequence:\n");
    output(T);
    int delItem = rand() % 10;
    printf("The delItem is: %d\n", delItem);
    delItemX_1(&T, delItem);
    printf("The sequence after the operation1:\n");
    output(T);
    T = Q;
    delItemX_2(&T, delItem);
    printf("The sequence after the operation2:\n");
    output(T);
    T = Q;
    delItemX_3(&T, delItem);
    printf("The sequence after the operation3:\n");
    output(T);
    return 0;
}