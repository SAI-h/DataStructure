/*
17.判断带头结点的双循环链表是否对称(即从头部遍历到中间位置和从尾部遍历到中间位置得到的元素序列是否一样)
*/

#include "relatedFun.c"

bool SymmetryJudgment(DLinkList L) {
    DNode *op1 = L -> next, *op2 = L -> prior;
    // op1从头扫描至中间位置, op2从尾部扫描至中间位置
    // 当存在奇数个元素时,二者会最终重合;偶数个元素时,二者停下来的条件是op2移动到了op1之前
    while(op1 != op2 && op2 -> next != op1){ // 第二个判断条件不能写为op1->next!=op2,因为当op1->next==op2成立时会停止判断，
                                             // 但此时op1->data和op2->data可能并不等(偶数个元素),遗漏了一组判断
        if(op1 -> data != op2 -> data) return false;
        op1 = op1 -> next;
        op2 = op2 -> prior;
    }
    return true;
}

int main(void) {
    srand((size_t)time(NULL));
    // 构建循环双链表
    DLinkList L = createCircularDLinkList(rand() % Maxsize + 1, rand() % Maxsize, true);
    printf("Forward output of DLinkList L is:\n"); // 头至尾输出
    outputDList(L, true, true);
    printf("Reverse output of DLinkList L is:\n"); // 尾至头输出
    outputDList(L, true, false);
    if(SymmetryJudgment(L))
        printf("This circular double-linked list is symmetric!\n");
    else
        printf("This circular double-linked list is not symmetric!\n");
    delDLinkList(&L);
    return 0;
}