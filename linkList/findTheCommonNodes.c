/*
08和23题在实现上无太大出入,差异只在是23题中存储的是元素字符、存储的链表带头结点

08.给定两个单链表,找出两个链表的公共结点

23.[2012统考真题]假定采用带头结点的单链表保存单词,当两个单词有相同的后缀时,可以共享相同的后缀空间,
例如:"loading"和"being"中"ing"是共享的.设str1和str2分别指向两个单词所在单链表的头结点,找出str1和str2所指向的
两个链表的共同后缀的起始位置.

分析:L1和L2是两个单链表,对于单链表中的每个结点仅有一个next域,即每个结点只能存在一个直接的后继
若L1和L2在某一结点处交汇,又该节点仅含一个直接后继,后继结点都仅含一个直接后继,那么从该结点开始两条链表之后的结点全部重合
就像是是两条河流汇聚成一条河流,形似"Y",而不可能是"X"
*/

#include "relatedFun.c"

int getLenth(LinkList L) {
    int len = 0;
    while(L) L = L -> next, len ++;
    return len;
}

// 假设L1的长度为len1,L2的长度为len2,p指向L1,q指向L2;不妨设len1>len2
// 若二者存在公共结点,一定是双方的末尾段存在重合
// 那么让p先行遍历(len1-len2)个结点,然后p和q齐头并进直至找到二者指向相同的结点位置为止
LinkList findTheComNodes(LinkList L1, LinkList L2) {
    LinkList p = L1, q = L2;
    int len1 = getLenth(L1), len2 = getLenth(L2);
    if(len1 < len2) { // 保证L1的长度长于L2,使代码简洁些
        LinkList tmp = p;
        p = q;
        q = tmp;
    }
    int dis = len1 - len2;
    if(dis < 0) dis = - dis;
    while(dis --) p = p -> next; // 使二者同步
    while(p) {
        if(p == q) return p;
        p = p -> next, q = q -> next;
    }
    return NULL;
}

int main(void) {
    srand((size_t)time(NULL));
    int range = rand() % Maxsize;
    LinkList ComPart = createRandomLinkList(rand() % Maxsize + 1, range, false); // 公共结点部分,即代求部分
    LinkList L1 = createRandomLinkList(rand() % Maxsize + 1, range, false);
    LinkList L2 = createRandomLinkList(rand() % Maxsize + 1, range, false);
    L1 = joinTogether(L1, ComPart);
    L2 = joinTogether(L2, ComPart);
    printf("The linkList L1 is:\n");
    output(L1, false);
    printf("The linkList L2 is:\n");
    output(L2, false);
    printf("The common part is:\n");
    output(findTheComNodes(L1, L2), false);
    delLinkList(&L1);
    delLinkList(&L2);
    return 0;
}