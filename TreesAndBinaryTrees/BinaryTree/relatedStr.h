#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define bool int 
#define true 1
#define false 0
#define Maxsize 100
#define NotFound 0x3f3f3f3f
#define MAXLIM 0x7f7f7f7f
#define ElemType struct BinTree*

// 二叉树的定义
typedef struct BinTree {
    int val;
    struct BinTree *left;
    struct BinTree *right;
}*BinTree, TreeNode;

// 链栈,一个带头结点的单链表,栈顶元素总是头结点的后继(头插法)
typedef struct stackNode {
    ElemType data;
    struct stackNode *next;
}*stack, stackNode;

// (循环)队列
typedef struct queue {
    ElemType *data;
    int front; // 队首
    int rear; // 队尾
    int capacity; // 队列的最大容量(实际最大容量为capacity-1,因为循环队列设计时会牺牲一个存储单元)
}*queue;

// 求二者的最大值
int max(int a, int b);
// 求二者的最小值
int min(int a, int b);

// 栈的初始化
bool initStack(stack *s);
// 栈的判空
bool stackEmpty(stack s);
// 进栈
bool stackPush(stack s, ElemType e);
// 出栈
bool stackPop(stack s);
// 读取栈顶元素
ElemType stackTop(stack s);
// 队列的初始化
bool initQueue(queue *q);
// 队列判空
bool queueEmpty(queue q);
// 入队
bool queuePush(queue q, ElemType e);
// 出队
bool queuePop(queue q);
// 读取队头元素
ElemType queueTop(queue q);
// 输出并清空栈中的元素
void outputAndclearStack(stack s);
// 输出并清空队列中的元素
void outputAndclearQueue(queue q);

// 随机生成一棵二叉树
void generateTree(BinTree *Tree, bool is_root);
// 递归实现二叉树的先序遍历
void preOrder_R(BinTree Tree);
// 递归实现二叉树的中序遍历
void inOrder_R(BinTree Tree);
// 递归实现二叉树的后序遍历
void postOrder_R(BinTree Tree);
// 非递归实现二叉树的先序遍历
void preOrder_N(BinTree Tree);
// 非递归实现二叉树的中序遍历
void inOrder_N(BinTree Tree);
// 非递归实现二叉树的后序遍历
void postOrder_N(BinTree Tree);
// 实现二叉树的层次遍历
void level_Traversal(BinTree Tree);
// 递归求解二叉树的高度
int getTreeHeight_R(BinTree Tree);
// 非递归求解二叉树的高度
int getTreeHeight_N(BinTree Tree);
// 获取拥有双分支的结点个数
int getNumOfDBranch(BinTree Tree);
// 交换二叉树中所有结点的左右子树
void swapL_R(BinTree *Tree);
// 查找二叉树中第k个结点的值 k: 要查找的是第几个(1序)
int searchKthTreeNode(BinTree Tree, int k);
// 释放二叉树的内存空间
void relaseSpace(BinTree *Tree);
// 删除二叉树中以X为根的子树
void deletedRootEqualsX(BinTree *Tree, int X);
// 随机返回输入二叉树中的一个结点
TreeNode* getRandomNode(BinTree Tree);
// 查找该被选定结点select的所有祖先结点
void getAllAncestors(BinTree Tree, TreeNode* select);
// 获取二叉树的带权路径长度(WPL)值
int calWPL(BinTree Tree, int depth);
// 判断两棵二叉树的相似性
bool judgeSimilarity(BinTree T1, BinTree T2);
// 将二叉树的叶子结点从左向右链接成一个单链表
TreeNode* leavesLink(BinTree T);
// 获取二叉树的宽度(即具有结点最多的那一层的结点个数)
int getWidthOfBTree(BinTree Tree);
// 得到一个具有值为随机的树节点
TreeNode* randomTreeNode();
// 给定满二叉树的层数,生成一棵满二叉树
void generateFullBtree(BinTree *Tree, int depth);
// 获取二叉树的先序遍历序列
void getPreOrderSeq(BinTree Tree, int preSeq[]);
// 满二叉树:根据先序遍历序列构造后序遍历序列
void createPostSequence(int seq[], int l1, int r1, int postSeq[], int l2, int r2);