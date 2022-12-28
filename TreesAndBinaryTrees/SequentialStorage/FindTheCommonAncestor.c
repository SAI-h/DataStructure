/*
若有一棵二叉树以顺序方式进行存储,其中每个结点的值的范围为1~range,且不重复;
若随机给定该范围内的两个值,试求出二者最近的公共祖先节点的值
*/

#include "relatedFun.c"

int main(void) {
    binTree Tree;
    initBinTree(&Tree, Maxsize);
    srand((size_t)time(NULL));
    int depth = rand() % log_2(Tree -> capacity); // 给定的树的最大深度
    int range = generateTree(&Tree, depth); // 构造树,并获取到结点个个数,即结点的值域
    if(range == 0) {
        printf("The binary tree is empty!\n");
        freeSpace(Tree);
        return 0;
    }
    printf("The mapping relationship of the indexs and the tree nodes is:\n");
    show(Tree, (1 << depth) - 1);
    ElemType Node_1 = rand() % range + 1;
    ElemType Node_2 = rand() % range + 1;
    int Index_1 = findNodeInTree(Tree, Node_1, 1);
    int Index_2 = findNodeInTree(Tree, Node_2, 1);
    printf("The nodes that given are: [%d]%d and [%d]%d.\n", Index_1, Node_1, Index_2, Node_2);
    int val;
    int AncestorIndex = findTheCommonAncestor(Tree, Index_1, Index_2, &val);
    printf("The nearest common ancestor node is: [%d]%d.\n", AncestorIndex, val);
    freeSpace(&Tree);
    return 0;
}