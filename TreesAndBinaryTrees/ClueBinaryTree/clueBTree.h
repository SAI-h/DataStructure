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
#define ElemTye int

/**
 * @brief (中序)线索二叉树的结构体定义
 * 对于含有n个结点的二叉树而言含有n+1个空指针,若能将其利用起来,就可以加快结点查找前驱和后继的速度
 * 有一下的规定:
 * 1.若无左子树,令left指向其前驱节点;其中的ltag域标记为true,意思是指向前驱;
 * 2.若无右子树,令right指向其后继节点;其中的rtag域标记为true,意思是指向后继;
 * 3.对于线索化后的ltag域或rtag域为0的结点,指的是结点的left或right指向其左子树或右子树.
 */
typedef struct clueBTreeNode {
    ElemTye val;
    struct clueBTreeNode *left, *right;
    bool ltag, rtag;
}*clueBTree, clueBTNode;


// 初始化一棵(线索)二叉树
void generateRandBTree(clueBTree *TreeNode, bool is_root);
// 二叉树的中序线索化
void createClues(clueBTree Tree);
// 查找在中序二叉树下的最左下位置的结点,即被遍历的时候会被首先访问到的结点
clueBTNode* getFirstNode(clueBTree Tree);
// 查找当前结点的后继结点
clueBTNode* getNxtNode(clueBTree Tree);
// 实现中序线索二叉树的中序遍历
void inOrderClues(clueBTree Tree);