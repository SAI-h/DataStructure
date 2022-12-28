/*
[2014统考真题]二叉树的带权路径长度(WPL)是二叉树中所有叶节点的带权路径长度.给定一棵二叉树求解其WPL值.
*/

#include "relatedFun.c"

int main(void) {
    srand((size_t)time(NULL));
    BinTree Tree = NULL;
    generateTree(&Tree, true);
    
    // describe
    printf("The pre-Order sequence of the original binary tree is:\n");
    preOrder_R(Tree);
    printf("\nThe in-Order sequence of the original binary tree is:\n");
    inOrder_R(Tree);

    // calculate
    printf("\nThe WPL of the binary tree is: %d\n", calWPL(Tree, 0));
    return 0;
}