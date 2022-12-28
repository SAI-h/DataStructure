/*
给定一棵满二叉树的先序序列,设计算法获取其后序遍历序列.
*/

#include "relatedFun.c"

/*
对于满二叉树而言,对于以当前结点的为根的树,其左子树和右子树的结点个数是一样的,对于先序遍历的序列而言一定形如:
N LLLL..L RRRR..R 其中N为根结点,L标记该树的左子树,R标记该树的右子树,改造成后序整体形如:
LLLL..L RRRR..R N 即将变换后的左子树和右子树放到根的左侧
这里有两种看法,第一种是将根、左子树和右子树看作三个独立的整体,若要构造后序遍历序列,则对其整体进行重排
第二种则是将左子树和右子树看成一个整体,将这个整体内和根进行左右交换,再去递归处理子树
*/

int main(void) {
    // 构造满二叉树
    srand((size_t)time(NULL));
    BinTree Tree = NULL;
    int depth = rand() % 10;
    generateFullBtree(&Tree, depth);
    // 获取该二叉树的先序遍历序列
    int *Seq = (int *)malloc(sizeof(int) * ((1 << depth) - 1));
    getPreOrderSeq(Tree, Seq);
    // 输出该先序遍历序列
    printf("The pre-order of the binary is:\n");
    for(int i = 0; i < (1 << depth) - 1; i ++) printf("%d ", Seq[i]);
    printf("\n");
    // 根据先序遍历序列构造后序遍历序列
    int *postSeq = (int *)malloc(sizeof(int) * (1 << depth) - 1);
    createPostSequence(Seq, 0, (1 << depth) - 2, postSeq, 0, (1 << depth) - 2);
    printf("The post-order of the binary is:\n");
    for(int i = 0; i < (1 << depth) - 1; i ++) printf("%d ", postSeq[i]);
    printf("\n");
    return 0;
}