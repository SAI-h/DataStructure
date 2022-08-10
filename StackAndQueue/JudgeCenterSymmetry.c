/*
02.判断给定字符是否中心对称,如xyx,xyyx都是中心对称的
*/

#include "relatedFun.c"

// 判断回文串
bool sysmemetryJudge(char seq[]) {
    stack s;
    initStack(&s);
    int length = strlen(seq);
    int i = 0;
    while(i < length / 2) stackPush(s, seq[i ++]); // 前一半的字符全部入栈
    if(length % 2) i ++;
    while(i < length) {
        if(seq[i ++] != stackTop(s)) return false;
        stackPop(s);
    }
    return true;
}

int main(void) {
    char Seq[Maxsize];
    printf("Please enter the test sequence:");
    scanf("%s", Seq);
    if(sysmemetryJudge(Seq)) printf("This sequence is centrally symmetric\n");
    else printf("This sequence is not centrally symmetric\n");
    return 0;
}