#include "relatedFun.c"

int main(void) {
    // 初始化一棵(线索)二叉树(随机)
    srand((size_t)time(NULL));
    clueBTree Tree;
    generateRandBTree(&Tree, true);
    // 实现中序线索化
    createClues(Tree);
    // 实现中序线索二叉树的中序遍历
    inOrderClues(Tree);
    return 0;
}