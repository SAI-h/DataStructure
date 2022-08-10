/*
10.利用一个栈实现以下递归函数的非递归计算
if n = 0:
    Pn(x) = 1
if n = 1:
    Pn(x) = 2x
if n > 1:
    Pn(x) = 2xPn-1(x) - 2(n-1)Pn-2(x)
*/

#include "relatedFun.c"

int P(int n, int x) {
    if(n == 0) return 1;
    if(n == 1) return 2 * x;
    stack s;
    initStack(&s);
    stackPush(s, 1);
    stackPush(s, 2 * x);
    n --; // 还需要计算n次才能得到最终结果
    int k = 1;
    while(n --) { // 由递推关系式可以得出当前项是由上一项和上上一项共同决定的
        int Pn_1 = stackTop(s); // 获取上一项
        stackPop(s);            // 由于栈每次都只能获取到栈顶元素,即对于当前位置而言无法直接获取到其上上一项的内容,所以这里选择先出栈
        int Pn_2 = stackTop(s); // 出栈后获取上上一项的内容
        stackPush(s, Pn_1);     // 由于当前项的后一项同样需要使用到当前项的前一项,因此需要重新将这一项入栈
                                // 其实可以采用临时变量存储上上一项的值,这样可以省去一些对栈的操作
        int Pn = 2 * x * Pn_1 - 2 * k * Pn_2;
        printf("P_%d = 2 * %d * P_%d - 2 * %d * P_%d = %d\n", k + 1, x, k, k, k - 1, Pn);
        k ++;
        stackPush(s, Pn);
    }
    return stackTop(s);
}

int main(void) {
    srand((size_t)time(NULL));
    int x = rand() % 10;
    int n = rand() % 8; // 过大会溢出
    x = 9, n = 7;
    printf("n = %d, x = %d\n", n, x);
    printf("P_%d(%d) = %d", n, x, P(n, x));
    return 0;
}