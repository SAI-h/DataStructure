/*
求二叉树先序遍历中的第k个结点的值
*/

#include "relatedFun.c"

int main(void) {
    srand((size_t)time(NULL));
    BinTree Tree = NULL;
    generateTree(&Tree, true);
    printf("The pre-order of the binary tree is:\n");
    preOrder_R(Tree);
    int k = rand() % 10; // 查找二叉树中的第k个结点
    printf("\nThe index of search item in the pre-order is: %d\n", k);
    int Item = searchKthTreeNode(Tree, k);
    if(Item == NotFound) printf("Not Found!\n");
    else printf("The item is: %d\n", Item);
    return 0;
}