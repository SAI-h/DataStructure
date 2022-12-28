/*
统计二叉树中双分支结点的个数
*/

#include "relatedFun.c"

int main(void) {
    srand((size_t)time(NULL));
    BinTree Tree = NULL;
    generateTree(&Tree, true);

    // describe
    printf("Level Traversal:\n");
    level_Traversal(Tree);
    printf("\n");

    printf("Pre-Order:\n");
    preOrder_R(Tree);
    printf("\n");

    printf("In-Order:\n");
    inOrder_R(Tree);
    printf("\n");

    printf("Post-Order:\n");
    postOrder_R(Tree);
    printf("\n");

    // count
    printf("The number of the node which has double branch is: %d.", getNumOfDBranch(Tree));

    return 0;
}