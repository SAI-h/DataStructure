/*
求二叉树的高度
*/

#include "relatedFun.c"

int main(void) {
    srand((size_t)time(NULL));
    BinTree Tree = NULL;
    generateTree(&Tree, true);

    // 递归求解二叉树的高度
    printf("Recursion:\nThe height of the binary tree is: %d.\n", 
    getTreeHeight_R(Tree));

    // 非递归求解二叉树的高度
    printf("Non-Recursion:\nThe height of the binary tree is: %d.\n", 
    getTreeHeight_N(Tree));

    return 0;
}