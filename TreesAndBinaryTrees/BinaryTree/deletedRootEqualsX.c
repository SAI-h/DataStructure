/*
对于二叉树树中每个元素为x的结点,删去以它为根的子树,并释放空间
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

    // set up the deleted item
    int X = rand() % Maxsize;
    printf("\nThe item which should to be deleted is: %d\n", X);

    // operate
    deletedRootEqualsX(&Tree, X);

    // describe
    printf("The pre-Order sequence of the new binary tree is:\n");
    preOrder_R(Tree);
    printf("\nThe in-Order sequence of the new binary tree is:\n");
    inOrder_R(Tree);
    return 0;
}

/*
The pre-Order sequence of the original binary tree is:
7 7 6 9 7 8 8 9 7 8 6 8 7 9 6 7 9 8 6 9 9 9 7 7 9 7 6 6 7 6 9 6 8 8 9 8 6 7 6 7 9 7 9 7 6 
The in-Order sequence of the original binary tree is:
7 6 7 9 7 8 8 8 9 6 7 6 8 7 9 9 6 9 9 8 7 7 9 6 6 7 7 9 7 9 8 9 6 8 8 6 7 7 6 6 9 7 7 6 9
The item which should to be deleted is: 9
The pre-Order sequence of the new binary tree is:
7 7 6
The in-Order sequence of the new binary tree is:
7 6 7

The pre-Order sequence of the original binary tree is:
26 99 94 76 98 92 57 66 88 96 89 84 53 73 51 58 51 77 57 
The in-Order sequence of the original binary tree is:
92 98 76 94 57 66 96 88 99 53 51 73 51 58 84 77 89 26 57
The item which should to be deleted is: 66
The pre-Order sequence of the new binary tree is:
26 99 94 76 98 92 57 89 84 53 73 51 58 51 77 57
The in-Order sequence of the new binary tree is:
92 98 76 94 57 99 53 51 73 51 58 84 77 89 26 57
*/