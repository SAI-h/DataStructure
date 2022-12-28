#include "BinTree.h"

// 初始化二叉树
bool initBinTree(binTree *Tree, int capacity) {
    (*Tree) = (binTree)malloc(sizeof(binTree));
    if((*Tree) == NULL) return false;
    (*Tree) -> capacity = capacity + 1; // 二叉树的顺序存储是1序的
    (*Tree) -> TreeNodes = (ElemType *)malloc(sizeof(ElemType) * (*Tree) -> capacity);
    if((*Tree) -> TreeNodes == NULL) return false;
    for(int i = 0; i < (*Tree) -> capacity; i ++) (*Tree) -> TreeNodes[i] = -1;
    return true;
}

// 计算以2为底数的对数函数值,下取整
int log_2(int num) {
    int res = -1;
    while(num) {
        num /= 2;
        res ++;
    }
    return res;
}

// 构造一棵至多为depth深度的二叉树, 返回树中结点的个数
int generateTree(binTree *Tree, int depth) {
    int size = (1 << depth) - 1;
    int k = 1;
    for(int i = 1; i <= size; i ++) {
        if(i / 2 == 0 || ((*Tree) -> TreeNodes[i / 2] != -1 && (*Tree) -> TreeNodes[i / 2] != 0)) // 查看父节点是否为空或树外的区域
            (*Tree) -> TreeNodes[i] = rand() % 100 > 15 ? (k ++) : -1; // -1表示空结点
        else
            (*Tree) -> TreeNodes[i] = 0; // 0表示树外的区域
    }
    for(int i = size + 1; i < (*Tree) -> capacity; i ++)  // 添加最后一层的空结点,并声明树外地区域
        if((*Tree) -> TreeNodes[i / 2] != -1 && (*Tree) -> TreeNodes[i / 2] != 0) (*Tree) -> TreeNodes[i] = -1;
        else (*Tree) -> TreeNodes[i] = 0;
    return k - 1;
}

// 在二叉树中查找到对应值所在的位置
int findNodeInTree(binTree Tree, ElemType nodeI, int index) {
    if(Tree -> TreeNodes[index] == -1) return 0;
    if(Tree -> TreeNodes[index] == nodeI) return index;
    return findNodeInTree(Tree, nodeI, (index << 1)) | findNodeInTree(Tree, nodeI, (index << 1 | 1));
}

// 找到下标为Index_1和Index_2的两个结点的最近公共祖先结点
int findTheCommonAncestor(binTree Tree, int Index_1, int Index_2, int *val) {
    while(Index_1 != Index_2) {
        if(Index_1 > Index_2) Index_1 /= 2;
        else Index_2 /= 2;
    }
    *val = Tree -> TreeNodes[Index_1];
    return Index_1;
}

// 输出树结点与对应下标的对应关系
void show(binTree Tree, int size) {
    for(int i = 1; i <= size; i ++)
        printf("[%d]%d\n", i, Tree -> TreeNodes[i]);
}

// 释放空间
void freeSpace(binTree *Tree) {
    free((*Tree) -> TreeNodes);
    free(*Tree);
}