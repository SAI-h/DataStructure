#include "clueBTree.h"

// 初始化一棵(线索)二叉树
void generateRandBTree(clueBTree *TreeNode, bool is_root) {
    if(is_root) {
        *TreeNode = (clueBTree)malloc(sizeof(clueBTNode));
        (*TreeNode) -> val = rand() % Maxsize;
        (*TreeNode) -> left = (*TreeNode) -> right = NULL;
        (*TreeNode) -> ltag = (*TreeNode) -> rtag = false;
        generateRandBTree(&((*TreeNode) -> left), false);
        generateRandBTree(&((*TreeNode) -> right), false);
    }
    else {
        int val = rand() % Maxsize;
        if(val > Maxsize / 2) {
            (*TreeNode) = (clueBTree)malloc(sizeof(clueBTNode));
            (*TreeNode) -> val = val;
            (*TreeNode) -> left = (*TreeNode) -> right = NULL;
            (*TreeNode) -> ltag = (*TreeNode) -> rtag = false;
            generateRandBTree(&((*TreeNode) -> left), false);
            generateRandBTree(&((*TreeNode) -> right), false);
        }
    }
}

// 二叉树的中序线索化
void createClues(clueBTree Tree) { // 实质上就是进行了依次中序遍历, 需要序列化的结点是结点左子树或右子树为空的结点
    if(Tree == NULL) return;
    static clueBTNode* pre = NULL;
    createClues(Tree -> left);
    if(Tree -> left == NULL) { // 左子树为空,将其左指针指向该节点的前驱结点,并做好标号
        Tree -> left = pre;
        Tree -> ltag = true;
    }
    if(pre && pre -> right == NULL) { // 不判当前结点的是否右子树为空,而判断前驱结点的右子树是否为空,因为当前结点无法在现阶段得到后继,而前驱结点可以
        pre -> right = Tree;
        pre -> rtag = true;
    }
    pre = Tree;
    createClues(Tree -> right);
}

// 查找在中序二叉树下的最左下位置的结点,即被遍历的时候会被首先访问到的结点
clueBTNode* getFirstNode(clueBTree Tree) {
    if(Tree == NULL) return NULL;
    while(Tree -> ltag == false) Tree = Tree -> left;
    return Tree;
}

// 查找当前结点的后继结点
clueBTNode* getNxtNode(clueBTree Tree) {
    if(Tree -> rtag) // 线索化后,若当前结点rtag为true,说明right域中存放着其后继结点
        return Tree -> right;
    // 否则其后继应当为其右子树中会被首先访问到的结点
    else  return getFirstNode(Tree -> right);
}

// 实现中序线索二叉树的中序遍历
void inOrderClues(clueBTree Tree) {
    for(clueBTree iter = getFirstNode(Tree); iter; iter = getNxtNode(iter)) printf("%d ", iter -> val);
}