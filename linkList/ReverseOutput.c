/*
03.实现从尾到头(反向)输出一个带头结点的单链表中元素的值
*/

#include "relatedFun.c"

// 递归
void reverseOutput(LinkList L, LinkList Head) {
    if(L == NULL) return;
    reverseOutput(L -> next, Head);
    printf("%d", L -> data); 
    if(L != Head) printf("->");
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList L = createRandomLinkList(rand() % Maxsize, rand() % Maxsize, true);
    printf("The original linkList is:\n");
    output(L, true);
    printf("Reverse Output:\n");
    reverseOutput(L -> next, L -> next);
    delLinkList(&L);
    return 0;
}