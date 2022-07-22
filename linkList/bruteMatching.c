/*
16.判断单链表B中元素依次组成的序列是否为单链表A中元素组成的序列的子序列
*/

#include "relatedFun.c"

// (字符串)暴力匹配算法
bool bruteMactching(LinkList A, LinkList B) {
    while(A) {
        if(A -> data == B -> data) { // 主串的当前位置与模式串的首位置匹配
            LNode *op1 = A, *op2 = B;
            while(op1 && op2) { // 逐个比较即可
                if(op1 -> data != op2 -> data) break;
                op1 = op1 -> next;
                op2 = op2 -> next;
            }
            if(op2 == NULL) return true;
            else if(op1 == NULL) return false; // 模式串已经长于未参与匹配的主串,那么肯定不会匹配成功,也没有继续匹配的意义了
        }
        A = A -> next;
    }
    return false;
}

int main(void) {
    srand((size_t)time(NULL));
    int lenA = rand() % Maxsize + 1;
    int lenB = rand() % lenA + 1;
    LinkList A = createRandomLinkList(lenA, 4, false); // 缩小值域为4,使得取值更集中,更有可能使B为A的子序列
    LinkList B = createRandomLinkList(lenB, 4, false);
    printf("The linkList A is:\n");
    output(A, false);
    printf("The linkList B is:\n");
    output(B, false);
    if(bruteMactching(A, B)) printf("B is A's subsequence!\n");
    else printf("B is not A's subsequence\n");
    delLinkList(&A);
    delLinkList(&B);
    return 0;
}