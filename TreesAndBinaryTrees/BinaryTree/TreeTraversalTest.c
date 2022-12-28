/*
二叉树遍历算法的测试
*/

#include "relatedFun.c"

int main(void) {
    srand((size_t)time(NULL));
    BinTree Tree = NULL;
    generateTree(&Tree, true);

    printf("Level Traversal:\n");
    level_Traversal(Tree);
    printf("\n");

    printf("Pre-Order Recursion:\n");
    preOrder_R(Tree);
    printf("\n");
    printf("Pre-Order Non-Recursion:\n");
    preOrder_N(Tree);
    printf("\n");

    printf("In-Order Recursion:\n");
    inOrder_R(Tree);
    printf("\n");
    printf("In-Order Non-Recursion:\n");
    inOrder_N(Tree);
    printf("\n");

    printf("Post-Order Recursion:\n");
    postOrder_R(Tree);
    printf("\n");
    printf("Post-Order Non-Recursion:\n");
    postOrder_N(Tree);
    printf("\n");
    return 0;
}