/*
09.给定一个带头结点的单链表,按递增的次序输出单链表中各节点的数据元素,并释放结点所占的存储空间
*/

#include "relatedFun.c"

void outputAndDelete(LinkList L) {
    while(L -> next) { // 每次循环从单链表中找出最小值(的前驱位置),并将其(通过前驱指向其后继)删除释放
        LNode *op = L, *pre = NULL;
        ElemType minv = MAXLIM;
        while(op -> next) {
            if(op -> next -> data < minv) {
                minv = op -> next -> data;
                pre = op;
            }
            op = op -> next;
        }
        printf("%d", minv);
        LNode *tmp = pre -> next;
        pre -> next = pre -> next -> next;
        free(tmp);
        if(L -> next) printf("->");
    }
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList L = createRandomLinkList(rand() % Maxsize + 1, rand() % Maxsize, true);
    printf("The original linkList is:\n");
    output(L, true);
    printf("The result is:\n");
    outputAndDelete(L);
    free(L); // 释放头结点空间(空表)
    return 0;
}