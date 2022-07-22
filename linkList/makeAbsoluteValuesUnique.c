/*
24.[2015统考真题] 保留带头结点的单链表中第一次出现的结点而删除其余绝对值相等的结点
*/

#include "relatedFun.c"

void RandomNegative(LinkList L) {
    L = L -> next;
    while (L) {
        int tag = rand() % 2 ? 1 : -1;
        L -> data *= tag;
        L = L -> next;
    }
}

int abs(int _x) {
    return _x < 0 ? -_x : _x;
}

// ans 
void makeAbsoluteValuesUnique(LinkList L) {
    bool *vis = (bool *)malloc(sizeof(bool) * Maxsize); // 用来存储相应的绝对值后的值是否出现过
    for(int i = 0; i < Maxsize; i ++) vis[i] = false;
    LNode *op = L;
    while(L -> next) {
        int val = abs(L -> next -> data);
        if(vis[val]) { // 该元素的绝对值之前出现过,则删除该元素
            LNode *tmp = L -> next;
            L -> next = L -> next -> next;
            free(tmp);
        }else {
            L = L -> next;
            vis[val] = true;
        }
    }
    free(vis);
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList L = createRandomLinkList(rand() % Maxsize + 1, rand() % Maxsize, true);
    // 随机使其中的部分数据变为负数,可省去该步骤,也可在创建时将值域扩充到负数
    RandomNegative(L);
    printf("The original linkList is:\n");
    output(L, true);
    makeAbsoluteValuesUnique(L);
    printf("The linkList after the operation:\n");
    output(L, true);
    delLinkList(&L);
    return 0;
}