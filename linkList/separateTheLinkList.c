/*
10.将带有头结点的单链表A分解成两个带头结点的单链表A和B.
使得A中含有原表中序号为奇数的元素,B表中含有原表中序号为偶数的元素.保持相对顺序不变.
*/

#include "relatedFun.c"

// A链表分离后,A链表中未原先奇数项,B链表中为原先偶数项(1序)
LinkList separateTheLinkList(LinkList A) {
    LinkList B = createRandomLinkList(0, 0, true); // 创建空的带头结点的链表
    LinkList p = A -> next, q = B; // 此时p定位到原链表的首个元素所在的位置, q定位到B的头结点位置
    while(p) {
        q -> next = p -> next; // p永远指向原链表的奇数元素位置,p->next则指向偶数位置,而后进行尾插法,将偶数位置插入到B链表的尾部
        q = q -> next; // q可视为B的尾结点,以便于插入操作
        if(p -> next == NULL) break; // 该语句为真一定会先于循环判断为假执行, 若p->next为NULL, 那么p->next->next也没有了意义
        p -> next = p -> next -> next; // 删除偶数结点
        p = p -> next; 
    }
    return B;
}

int main(void) {
    srand((size_t)time(NULL));
    LinkList A = createRandomLinkList(rand() % Maxsize + 1, rand() % Maxsize, true);
    printf("The original linkList is:\n");
    output(A, true);
    // 分离出来的偶数项组成的链表
    LinkList B = separateTheLinkList(A);
    printf("");
    printf("The odd sequence is:\n");
    output(A, true);
    printf("The even sequence is:\n");
    output(B, true);
    delLinkList(&A);
    delLinkList(&B);
    return 0;
}