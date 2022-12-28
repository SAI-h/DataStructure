/*
将二叉树中所有的结点的左右子树进行交换
*/

#include "relatedFun.c"

int main(void) {
    srand((size_t)time(NULL));
    BinTree Tree = NULL;
    generateTree(&Tree, true);

    // describe
    printf("Before the swap operation:\n");
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
    printf("\n---------------------\n");
    
    // swap
    swapL_R(&Tree);
    printf("Swap successfully!\n---------------------\n");

    // describe
    printf("After the swap operation:\n");
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
    return 0;
}