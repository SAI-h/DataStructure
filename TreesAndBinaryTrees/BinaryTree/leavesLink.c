/*
设计算法,将二叉树的叶子结点按从左到右的顺序连成一个单链表,表头指针为headm链接时用叶节点的右指针域来存放单链表指针
*/

#include "relatedFun.c"

int main(void) {
    srand((size_t)time(NULL));
    BinTree Tree = NULL;
    generateTree(&Tree, true);

    // describe
    printf("The pre-order of the binary tree is:\n");
    preOrder_R(Tree);
    printf("\nThe in-order of the binary tree is:\n");
    inOrder_R(Tree);
    printf("\nThe lever traversal sequence of the binary tree is:\n");
    level_Traversal(Tree);

    // create
    TreeNode* head = leavesLink(Tree);
    printf("\nThe link list of leaves nodes is:\n");
    while(head) {
        printf("%d ", head -> val);
        head = head -> right;
    }

    return 0;
}