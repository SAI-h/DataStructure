/*
给定二叉树中的某一结点找到该结点的所有祖先结点
*/

#include "relatedFun.c"

int main(void) {
    srand((size_t)time(NULL));
    BinTree Tree = NULL;
    generateTree(&Tree, true);

    printf("pre-Order:\n");
    preOrder_R(Tree);
    printf("\nin-Order:\n");
    inOrder_R(Tree);
    printf("\n");

    // 从已有的二叉树中随机选定一个结点(地址)
    TreeNode* select = getRandomNode(Tree);
    printf("The value of the selected tree node is: %d.\n", select -> val);

    // 查找该被选定结点的所有祖先结点,向根的方向打印
    printf("The values of the ancestors node are:\n");
    getAllAncestors(Tree, select);
    printf("\nFinished!\n");

    return 0;
}

/*
pre-Order:
62 83 53 81 70 66 53 63 93 73 54 86 81
in-Order:
83 53 81 62 66 53 93 73 54 86 81 63 70
The value of the selected tree node is: 86.
The values of the ancestors node are:
54 73 93 63 53 66 70 62
Finished!
*/