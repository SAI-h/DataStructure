/*
08.假设一个算术表达式中包含圆括号、方括号和花括号三种类型的括号(半角),编写一个算法来
判别表达式中的括号是否匹配,以字符'\0'作为算术表达式的结束符.
*/

#include "relatedFun.c"

bool parenthesesMatching(char str[]) {
    stack s;
    initStack(&s);
    int i = 0;
    while(str[i]) {
        if(str[i] == '(' || str[i] == '[' || str[i] == '{') {
            stackPush(s, str[i]);
        }
        else if(str[i] == ')') {
            if(stackTop(s) == '(') stackPop(s);
            else return false;
        }
        else if(str[i] == ']') {
            if(stackTop(s) == '[') stackPop(s);
            else return false;
        }
        else if(str[i] == '}') {
            if(stackTop(s) == '{') stackPop(s);
            else return false;
        }
        i ++;
    }
    return stackEmpty(s);
}

int main(void) {
    char str[Maxsize];
    printf("Please enter an arithmetic expression with parentheses:");
    fgets(str, Maxsize, stdin); // 读入一行
    bool result = parenthesesMatching(str);
    if(result) printf("Parentheses match successfully!\n");
    else printf("Parentheses match failed!\n");
    return 0;
}