/*
01.假设以I和O分别表示入栈和出栈操作,栈的初态和终态为空,入栈和出栈可以表示成仅由I和O组成的序列,
可操作的序列称为合法序列,否则称为非法序列.
判定给定序列的合法性.
*/

#include "relatedFun.c"

// 法一:利用栈判断合法性,遇到I将I字符入栈,遇到O将栈顶元素出栈,
// 若遇到栈为空出栈,或序列结束栈不为空的情况,说明序列非法
bool validityJudge(char opSeq[]) {
    stack s;
    initStack(&s);
    for(int i = 0; opSeq[i]; i ++) {
        if(opSeq[i] == 'O') {
            if(stackEmpty(s)) return false;
            stackPop(s);
        }else {
            stackPush(s, opSeq[i]);
        }
    }
    return stackEmpty(s);
}

// 法二:记录一个整形初值为0的变量sum的值,遍历序列,遇到I加1,遇到O减1,
// 若中途出现sum的值小于0直接返回false, 最后判定终值是否为0即可
bool validityJudge_2(char opSeq[]) {
    int sum = 0;
    for(int i = 0; opSeq[i]; i ++) {
        sum += (opSeq[i] == 'I' ? 1 : -1);
        if(sum < 0) return false;
    }
    return sum == 0;
}

int main(void) {
    char choice;
    do{
        char opSeq[Maxsize];
        printf("Please input the operation sequence which only contains I or O:");
        scanf("%s", opSeq);
        if(validityJudge(opSeq)) printf("Method1: This sequence is feasible!\n");
        else printf("Method1: The sequence is infeasible!\n");
        if(validityJudge_2(opSeq)) printf("Method2: This sequence is feasible!\n");
        else printf("Method2: The sequence is infeasible!\n");
        getchar();
        printf("Enter 'n' to exit:");
        choice = getchar();
    }while(choice != 'n');
    return 0;
}

/*
test:
IOIIOIOO
IOOIOIIO
IIIOIOIO
IIIOOIOO
*/