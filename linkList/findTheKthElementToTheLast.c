/*
22.[2009统考真题]有一个带有表头结点的单链表,在不改变链表的前提下,设计尽可能高效的算法,查找链表中倒数第k个位置上的结点.
*/

#include "relatedFun.c"

// 设置两个指针,第一个指针比第二个指针先走k步,以此来保证两个指针的间距相差k,再次之后两个指针同步向后走
// 因为保证了两个指针的间距为k,那么当第一个指针指向链表末尾的位置时,第二个指针指向的位置是倒数第k个位置,即所求
bool findTheKthToLast(LinkList L, int k, ElemType *findItem) {
    if(k < 0) return false;
    LNode *p = L, *q = L;
    for(int i = 0; p && i < k; i ++) p = p -> next; // 保证p比q先走k步
    if(p == NULL) return false;
    while(p) {
        p = p -> next;
        q = q -> next;
    }
    *findItem = q -> data;
    return true;
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList L = createRandomLinkList(rand() % Maxsize + 1, rand() % Maxsize, true);
    printf("The linkList L is:\n");
    output(L, true);
    ElemType findItem = MAXLIM;
    int k = rand() % Maxsize + 1;
    bool tag = findTheKthToLast(L, k, &findItem);
    if(!tag) printf("K equals to %d! Could not find!\n", k);
    else printf("Succeed in finding!The %dTH element to the end is %d!", k, findItem);
    delLinkList(&L);
    return 0;
}