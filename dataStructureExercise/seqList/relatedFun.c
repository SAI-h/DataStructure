// 初始化一个顺序表
bool initSqList(seqList *T) {
    T -> length = 0;
    return T -> length == 0;
}

// 填入随机数据,以初始化顺序表 len是填充的长度, range是生成随机数的范围
bool randomSqList(seqList *T, unsigned int len, int range) {
    if(len > Maxsize) return false;
    if(!initSqList(T)) return false;
    while(T -> length < len)
        T -> data[T -> length ++] = rand() % range;
    return T -> length == len;
}

// 按顺序输出顺序表中的元素值
void output(seqList T) {
    for(unsigned int i = 0; i < T.length; i ++) {
        printf("%d ", T.data[i]);
        if((i + 1) % 10 == 0 && i != T.length - 1) printf("\n");
    }
    printf("\n");
}

// 初始化成数据是随机的有序的顺序表, choice:0,序列必须严格递增, 1:序列可以不严格递增
bool createOrderSqlist(seqList *T, unsigned int len, int range, int choice) {
    if(len > Maxsize) return false;
    if(!initSqList(T)) return false;
    int idx = 0, last = -MAXLIM;
    while(T -> length < len) {
        int cur;
        do{
            cur = rand() % range;
            if(range - 1 == cur) range += rand() % 10; // 扩大生成随机数的值域
        }while(cur + choice <= last); // cur < last 非严格递增 等价于 cur + 1 <= last
                                      // cur <= last 严格递增  等价于 cur + 0 <= last
        T -> data[T -> length ++] = cur;
        last = cur;
    }
    return T -> length == len;
}