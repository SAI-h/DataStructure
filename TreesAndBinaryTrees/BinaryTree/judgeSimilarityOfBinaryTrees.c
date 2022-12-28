/*
设计判断两棵二叉树是否相似.所谓相似,是指两棵树都是空的二叉树或者都只有一个根节点;
或两棵树的左子树是相似的,且两棵树的右子树是相似的
*/

#include "relatedFun.c"

int main(void) {
    srand((size_t)time(NULL));
    BinTree T1 = NULL;
    generateTree(&T1, true);
    BinTree T2 = NULL;
    generateTree(&T2, true);

    // describe T1
    printf("T1\nThe pre-Order sequence of the original binary tree T1 is:\n");
    preOrder_R(T1);
    printf("\nThe in-Order sequence of the original binary tree T1 is:\n");
    inOrder_R(T1);

    // describe T2
    printf("\nT2\nThe pre-Order sequence of the original binary tree T2 is:\n");
    preOrder_R(T2);
    printf("\nThe in-Order sequence of the original binary tree T2 is:\n");
    inOrder_R(T2);

    // judge
    if(judgeSimilarity(T1, T2)) printf("\nT1 and T2 are similar!\n");
    else printf("\nT1 and T2 are not similar!\n");

    return 0;
}