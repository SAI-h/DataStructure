#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define bool int 
#define true 1
#define false 0
#define Maxsize 100
#define ElemType int
#define MAXLIM 0x7f7f7f7f

typedef struct binTree {
    int capacity;
    ElemType *TreeNodes;
}*binTree;

// 初始化二叉树
bool initBinTree(binTree *Tree, int capacity);
// 计算以2为底数的对数函数值,下取整
int log_2(int num);
// 构造一棵至多为depth深度的二叉树, 返回树中结点的个数
int generateTree(binTree *Tree, int depth);
// 在二叉树中查找到对应值所在的位置
int findNodeInTree(binTree Tree, ElemType nodeI, int index);
// 找到下标为Index_1和Index_2的两个结点的最近公共祖先结点
int findTheCommonAncestor(binTree Tree, int Index_1, int Index_2, int *val);
// 输出树结点与对应下标的对应关系
void show(binTree Tree, int size);
// 释放空间
void freeSpace(binTree *Tree);