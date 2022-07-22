/*
25.[2019统考真题] 设线性表L=(a1,a2,a3...,an)采用带头结点的单链表保存,请设计一个空间复杂度为O(1)且时间上尽可能高效的算法,
重新排列L中的各节点,得到线性表L'=(a1,an,a2,an-1,...)
*/

#include "relatedFun.c"

// 如果现在给定了两个链表, L1=(1,3,5,7), L2=(2,4,6,8). 
// 将其合并为一个元素交错的单链表L=(1,2,3,4,5,6,7,8)的做法是: 以L1为基,将L2的元素插入至L1中
// 设定两个指向L1和L2链表的操作指针p和q, 每次在L1中的p和p->next所指向的元素之间插入q指向的元素即可
// 观察题目所给定后重排的序列L', 会发现其实可以看作是两个链表L1=(a1,a2,a3,...an/2+1),L2=(an,an-1,...an/2+2)采取上述模式合并的结果
// 因此需要从L中分离出这两个链表，再将二者合并即可,其中L1的分离是容易的,因为它就是原链表的前一半的部分
// 但是L2的分离并不是简单的截取后半部分就可以了,它还需要进行逆置操作
void rearrangeTheLinkList(LinkList L) {
    // 获取链表长度
    int length = 0;
    LNode *op = L -> next;
    while(op) op = op -> next, length ++; 
    // 前后分割
    LNode *q = L;
    for(int i = 0; i < length / 2; i ++) q = q -> next;
    if(length % 2) q = q -> next; // 注意此时q指向的是前半段的最后一个元素的位置,
                                  // 我们(视为先不断链)将该点视为后半段的头结点,借助该结点,以头插法的方式完成对后半段的逆置
    // 后半段逆置
    op = q -> next;
    q -> next = NULL;
    while(op) {
        LNode *tmp = op -> next;
        op -> next = q -> next;
        q -> next = op;
        op = tmp;
    }
    // 断链
    LNode *p = q -> next;
    q -> next = NULL;
    q = p;              // q指向后半段的首个元素的位置
    p = L -> next;      // p指向前半段的首个元素的位置
    // 逐一插入
    while(q) { // 前面的操作保证了后半段的元素个数小于等于前半段
        LNode *tmp = q -> next; // 暂存
        q -> next = p -> next;  // 插入
        p -> next = q;
        q = tmp;                // 移动
        p = p -> next -> next;
    }
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList L = createRandomLinkList(rand() % Maxsize + 1, rand() % Maxsize, true);
    printf("The original linkList is:\n");
    output(L, true);
    rearrangeTheLinkList(L);
    printf("The linkList after the operation:\n");
    output(L, true);
    delLinkList(&L);
    return 0;
}