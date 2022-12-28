/*
求解二叉树的宽度,即结点个数最多的那一层拥有的结点个数
*/

#include "relatedFun.c"

int main(void) {
    srand((size_t)time(NULL));
    BinTree Tree = NULL;
    generateTree(&Tree, true);
    printf("Leval traversal:\n");
    printf("\nThe width of the binary tree is: %d\n", getWidthOfBTree(Tree));
    return 0;
}