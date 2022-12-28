#include "relatedStr.h"

// 求二者的最大值
int max(int _a, int _b) {
    return _a > _b ? _a : _b;
}

// 求二者的最小值
int min(int _a, int _b) {
    return _a < _b ? _a : _b;
}

// 栈的初始化
bool initStack(stack *s) {
    *s = (stack)malloc(sizeof(stackNode));
    if(*s == NULL) return false;
    (*s) -> data = (ElemType)malloc(sizeof(struct BinTree));
    if((*s) -> data == NULL) return false;
    (*s) -> data -> val = MAXLIM;
    (*s) -> data -> left = (*s) -> data -> right = NULL;
    (*s) -> next = NULL;
    return true;
}

// 栈的判空
bool stackEmpty(stack s) {
    return s -> next == NULL;
}

// 进栈
bool stackPush(stack s, ElemType e) {
    stackNode *sItem = (stackNode *)malloc(sizeof(stackNode));
    if(sItem == NULL) return false;
    sItem -> data = e;
    sItem -> next = s -> next;
    s -> next = sItem;
    return true;
}

// 出栈
bool stackPop(stack s) {
    if(stackEmpty(s)) return false;
    stackNode *tmp = s -> next;
    s -> next = s -> next -> next;
    free(tmp);
    return true;
}

// 读取栈顶元素
ElemType stackTop(stack s) {
    // if(stackEmpty(s)) return MAXLIM;
    return s -> next -> data;
}

// 队列的初始化
bool initQueue(queue *q) {
    (*q) = (queue)malloc(sizeof(struct queue));
    if(q == NULL) return false;
    (*q) -> front = (*q) -> rear = 0;
    (*q) -> capacity = Maxsize;
    (*q) -> data = (ElemType *)malloc(sizeof(ElemType) * ((*q) -> capacity));
    if((*q) -> data == NULL) return false;
    return true;
}

// 队列判空
bool queueEmpty(queue q) {
    return q -> front == q -> rear;
}

// 入队
bool queuePush(queue q, ElemType e) {
    if((q -> rear + 1) % q -> capacity == q -> front) return false;
    q -> data[q -> rear] = e;
    q -> rear = (q -> rear + 1) % q -> capacity;
    return true;
}

// 出队
bool queuePop(queue q) {
    if(queueEmpty(q)) return false;
    q -> front = (q -> front + 1) % q -> capacity;
}

// 读取队头元素
ElemType queueTop(queue q) {
    // if(queueEmpty(q)) return MAXLIM;
    return q -> data[q -> front];
}

// 输出并清空栈中的元素
void outputAndclearStack(stack s) {
    while(!stackEmpty(s)) {
        printf("%d ", stackTop(s));
        stackPop(s);
    }
    printf("\n");
}

// 输出并清空队列中的元素
void outputAndclearQueue(queue q) {
    while(!queueEmpty(q)) {
        printf("%d ", queueTop(q));
        queuePop(q);
    }
    printf("\n");
}

// 随机生成一棵二叉树
void generateTree(BinTree *Tree, bool is_root) {
    if(is_root) {
        *Tree = (BinTree)malloc(sizeof(TreeNode));
        (*Tree) -> val = rand() % Maxsize;
        (*Tree) -> left = (*Tree) -> right = NULL;
        generateTree(&((*Tree) -> left), false);
        generateTree(&((*Tree) -> right), false);
    }
    else {
        int val = rand() % Maxsize;
        if(val >  Maxsize / 2) {
            *Tree = (BinTree)malloc(sizeof(TreeNode));
            (*Tree) -> val = val;
            (*Tree) -> left = (*Tree) -> right = NULL;
            generateTree(&((*Tree) -> left), false);
            generateTree(&((*Tree) -> right), false);
        }
    }
}

// 递归实现二叉树的先序遍历
void preOrder_R(BinTree Tree) {
    if(Tree == NULL) return;
    printf("%d ", Tree -> val);
    preOrder_R(Tree -> left);
    preOrder_R(Tree -> right);
}

// 递归实现二叉树的中序遍历
void inOrder_R(BinTree Tree) {
    if(Tree == NULL) return;
    inOrder_R(Tree -> left);
    printf("%d ", Tree -> val);
    inOrder_R(Tree -> right);
}

// 递归实现二叉树的后序遍历
void postOrder_R(BinTree Tree) {
    if(Tree == NULL) return;
    postOrder_R(Tree -> left);
    postOrder_R(Tree -> right);
    printf("%d ", Tree -> val);
}

// 非递归实现二叉树的先序遍历
void preOrder_N(BinTree Tree) {
    stack sta;
    initStack(&sta);
    BinTree op = Tree;
    while(op || !stackEmpty(sta)) {
        if(op) {
            printf("%d ", op -> val);
            stackPush(sta, op);
            op = op -> left;
        }
        else {
            op = stackTop(sta) -> right;
            stackPop(sta);
        }
    }
}

// 非递归实现二叉树的中序遍历
void inOrder_N(BinTree Tree) {
    stack sta;
    initStack(&sta);
    BinTree op = Tree;
    while(op || !stackEmpty(sta)) {
        if(op) {
            stackPush(sta, op);
            op = op -> left;
        }
        else {
            printf("%d ", stackTop(sta) -> val);
            op = stackTop(sta) -> right;
            stackPop(sta);
        }
    }
}

// 非递归实现二叉树的后序遍历
void postOrder_N(BinTree Tree) {
    stack sta;
    initStack(&sta);
    BinTree op = Tree;
    TreeNode *tag = NULL; // 标记上一个完成访问的结点
    while(op || !stackEmpty(sta)) {
        if(op) {
            stackPush(sta, op);
            op = op -> left;
        }
        else {
            op = stackTop(sta);
            if(op -> right && tag != op -> right) { // 存在没有被访问过的右子树
                op = op -> right;
            }
            else { // 当前结点没有右子树或者右子树已经完成了访问回到了当前结点,根据后序遍历的原则,当前结点应当现在被访问
                printf("%d ", op -> val);
                tag = op;
                stackPop(sta);
                op = NULL; // 进入该分支时,op为NULL,现在还原op为NULL
            }
        }
    }
}

// 实现二叉树的层次遍历
void level_Traversal(BinTree Tree) {
    if(Tree == NULL) return;
    queue que;
    initQueue(&que);
    printf("%d ", Tree -> val);
    queuePush(que, Tree);
    while(!queueEmpty(que)) {
        TreeNode *top = queueTop(que);
        queuePop(que);
        if(top -> left) {
            printf("%d ", top -> left -> val);
            queuePush(que, top -> left);
        }
        if(top -> right) {
            printf("%d ", top -> right -> val);
            queuePush(que, top -> right);
        }
    }
}

// 递归求解二叉树的高度
int getTreeHeight_R(BinTree Tree) {
    if(!Tree) return 0;
    return max(getTreeHeight_R(Tree -> left), getTreeHeight_R(Tree -> right)) +  1;
}

// 非递归求解二叉树的高度
int getTreeHeight_N(BinTree Tree) { // 层次遍历取求解即可
    int height = 0;
    int size = 0; // 记录当前队列的大小
    queue que;
    initQueue(&que);
    queuePush(que, Tree);
    size ++;
    while(size) {  // while(!queueEmpty(que)) {...}
        int curNum = 0; // 记录新的一层的结点个数
        for(int i = 0; i < size; i ++) { // 将一层的结点全部依次弹出队列,将对应结点的子节点依次纳入队列,保证每次while循环处理的是二叉树的不同层
            TreeNode* top = queueTop(que);
            queuePop(que);
            if(top -> left) {
                queuePush(que, top -> left);
                curNum ++;
            }
            if(top -> right) {
                queuePush(que, top -> right);
                curNum ++;
            }
        }
        size = curNum; // 因为上一层的结点全部弹出了队列,所以当前队列的大小即为curNUm
        height ++;
    }
    return height;
}

// 获取拥有双分支的结点个数
int getNumOfDBranch(BinTree Tree) {
    if(!Tree) return 0;
    return getNumOfDBranch(Tree -> left) + getNumOfDBranch(Tree -> right) + (Tree -> left && Tree -> right);
}

// 交换二叉树中所有结点的左右子树
void swapL_R(BinTree *Tree) {
    if(!(*Tree)) return;
    swapL_R(&((*Tree) -> left));
    swapL_R(&((*Tree) -> right));
    TreeNode* tmp = (*Tree) -> left;
    (*Tree) -> left = (*Tree) -> right;
    (*Tree) -> right = tmp;
}

// 查找二叉树中第k个结点的值 k: 要查找的是第几个结点(1序)
int searchKthTreeNode(BinTree Tree, int k) {
    if(!Tree) return NotFound;
    static int cnt = 0; // 只进行一次初始化
    if(++ cnt == k) return Tree -> val;
    int find_L = searchKthTreeNode(Tree -> left, k);
    if(find_L != NotFound) return find_L;
    int find_R = searchKthTreeNode(Tree -> right, k);
    if(find_R != NotFound) return find_R;
    return NotFound;
}

// 释放二叉树的内存空间
void relaseSpace(BinTree *Tree) {
    if((*Tree) -> left) { // 释放左子树所有结点的空间
        relaseSpace(&((*Tree) -> left));
        (*Tree) -> left = NULL;
    }
    if((*Tree) -> right) { // 释放右子树所有结点的空间
        relaseSpace(&((*Tree) -> right));
        (*Tree) -> right = NULL;
    }
    if((*Tree) -> left == NULL && (*Tree) -> right == NULL) { // 释放根节点的空间
        free(*Tree); 
    }
}

// 删除二叉树中以X为根的子树
void deletedRootEqualsX(BinTree *Tree, int X) {
    if(*(Tree) == NULL) return;
    if((*Tree) -> val == X) { // 如果二叉树本身根结点就是X则将其整体全部删除,因为后续判断左右子树的值是否为X的条件,因此该语句事实上只有第一次递归(主函数调用)有用
        relaseSpace(Tree);
        (*Tree) = NULL;
    }
    else {
        if((*Tree) -> left) {
            if((*Tree) -> left -> val == X) { // 若左子树值为X,则将该子树全部删除,右子树同理
                relaseSpace(&((*Tree) -> left));
                (*Tree) -> left = NULL;
            }
            else deletedRootEqualsX(&((*Tree) -> left), X); // 否则就说明左子树的根不为X,那么就去删除左子树中符合删除条件的子树,右子树同理
        }
        if((*Tree) -> right) {
            if((*Tree) -> right -> val == X) {
                relaseSpace(&((*Tree) -> right));
                (*Tree) -> right = NULL;
            }
            else deletedRootEqualsX(&((*Tree) -> right), X);
        }
    }
}


// 随机返回输入二叉树中的一个结点
TreeNode* getRandomNode(BinTree Tree) {
    if(!Tree) return NULL;
    TreeNode *select = NULL;
    TreeNode* op = Tree;
    while(!select) {
        int choice = rand() % Maxsize;
        if(choice < Maxsize / 7 * 3) {// 小于值域的七分之三,走左子树;若左子树为空,则这一轮轮空
            if(op -> left) op = op -> left;
        }
        else if(choice < Maxsize / 7 * 6) {// 介于七分之三到七分之六之间,走右子树;若右子树为空,则这一轮轮空
            if(op -> right) op = op -> right;
        }
        else { // 大于七分之六,则选择该节点作为输出
            select = op;
        }
        if(op -> left == NULL && op -> right == NULL) op = Tree; // 如果走到了叶子结点,则重置
    }
    return select;
}

// 查找该被选定结点select的所有祖先结点
void getAllAncestors(BinTree Tree, TreeNode* select) {
    if(!Tree) return;
    static bool tag = false; // 观测有没有查找到相应的结点
    if(Tree == select) {
        tag = true;
        return;
    }
    // 这里的条件判断不能合并,因为进入递归前后tag的值可能会发生变化
    if(!tag) getAllAncestors(Tree -> left, select); // 未查找到则继续找左子树
    if(!tag) getAllAncestors(Tree -> right, select); // 未查找到则继续找右子树
    if(tag) printf("%d ", Tree -> val); // 后序遍历,则当前保存在系统栈中的结点就是代求结点,之后执行的任务就是将系统栈中的元素依次出栈打印即可
}

// 获取二叉树的带权路径长度(WPL)值
int calWPL(BinTree Tree, int depth) {
    if(Tree == NULL) return 0;
    int res = 0;
    if(Tree -> left == NULL && Tree -> right == NULL) res += depth * (Tree -> val); // 叶节点才算入带权路径长度
    return res + calWPL(Tree -> left, depth + 1) + calWPL(Tree -> right, depth + 1);
}

// 判断两棵二叉树的相似性
bool judgeSimilarity(BinTree T1, BinTree T2) {
    if(!T1 && !T2) return true;
    if(T1 && !T2 || !T1 && T2) return false;
    return judgeSimilarity(T1 -> left, T2 -> left) && judgeSimilarity(T1 -> right, T2 -> right);
}

// 将二叉树的叶子结点从左向右链接成一个单链表
TreeNode* leavesLink(BinTree T) {
    static TreeNode* head = NULL;
    static TreeNode* op = NULL;
    if(T == NULL) return head;
    if(T -> left == NULL && T -> right == NULL) { // 是叶子结点,将其连接到链表中
        if(head == NULL) {
            head = T;
            op = head;
        }
        else {
            op -> right = T;
            op = T;
        }
    } 
    leavesLink(T -> left);
    leavesLink(T -> right);
    return head;
}

// 获取二叉树的宽度(即具有结点最多的那一层的结点个数)
int getWidthOfBTree(BinTree Tree) { // 层次遍历的应用
    if(Tree == NULL) return 0;
    queue que;
    initQueue(&que);
    queuePush(que, Tree);
    int res = 1;
    int cnt = 1; // 记录每层的结点数目
    int lastDepth = -1; // 上一层的层号
    while(!queueEmpty(que)) {
        TreeNode* top = queueTop(que);
        queuePop(que);
        int depth = top -> val / Maxsize; // 将层号和结点原本的数据都存放在了结点val域中,原本结点的值域为0~99,
                                          // 将层数乘以100加入原来的数据,则val对100取模得到原本数据,对100整除得到层数
        if(depth != lastDepth) { // 新的一层
            if(depth) printf("\n");
            printf("depth_%d: %d ", depth, top -> val % Maxsize);
            lastDepth = depth;
            res = max(res, cnt);
            cnt = 1;
        }
        else { // 该层有了新的结点
            printf("%d ", top -> val % Maxsize);
            cnt ++;
        }
        if(top -> left) {
            top -> left -> val += (depth + 1) * Maxsize;
            queuePush(que, top -> left);
        }
        if(top -> right) {
            top -> right -> val += (depth + 1) * Maxsize;
            queuePush(que, top -> right);
        }
    }
    return res;
}

// 得到一个具有值为随机的树节点
TreeNode* randomTreeNode() {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node -> left = node -> right = NULL;
    node -> val = rand() % Maxsize;
    return node;
}

// 给定满二叉树的层数,生成一棵满二叉树
void generateFullBtree(BinTree *Tree, int depth) {
    int nodesNum = (1 << depth) - 1;
    int cnt = 0;
    queue que;
    initQueue(&que);
    while(nodesNum != cnt) {
        if(*Tree == NULL) {
            *Tree = randomTreeNode();
            queuePush(que, *Tree);
            cnt ++;
        }
        else {
            TreeNode *top = queueTop(que);
            queuePop(que);
            top -> left = randomTreeNode();
            top -> right = randomTreeNode();
            queuePush(que, top -> left);
            queuePush(que, top -> right);
            cnt += 2;
        }
    }
}

// 获取二叉树的先序遍历序列
void getPreOrderSeq(BinTree Tree, int preSeq[]) {
    if(Tree == NULL) return;
    static int poi = 0;
    preSeq[poi ++] = Tree -> val;
    getPreOrderSeq(Tree -> left, preSeq);
    getPreOrderSeq(Tree -> right, preSeq);
}

// 满二叉树:根据先序遍历序列构造后序遍历序列
void createPostSequence(int seq[], int l1, int r1, int postSeq[], int l2, int r2) {;
    if(r1 >= l1) {
        int subTreeLen = (r1 - l1 + 1) / 2;
        postSeq[r2] = seq[l1]; // 后序的最后一个是根的位置,即是先序的第一个位置
        createPostSequence(seq, l1 + 1, l1 + subTreeLen, postSeq, l2, l2 + subTreeLen - 1); // 重排左子树
        createPostSequence(seq, l1 + subTreeLen + 1 , r1, postSeq, l2 + subTreeLen, r2 - 1); // 重排右子树
    }
}