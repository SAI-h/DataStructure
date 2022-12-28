/*
题源:https://www.acwing.com/problem/content/description/1625/
[2017统考真题]请设计一个算法,将给定的表达式树(二叉树)转换为等价的中缀表达式(通过括号反映操作符的计算次序)并输出.
[PAT甲级真题1130]
给定一个句法二叉树，请你输出相应的中缀表达式，并利用括号反映运算符的优先级。
输入格式
第一行包含整数 N 表示二叉树的总结点个数。
接下来 N 行，每行以下列格式给出一个结点的信息（第 i 行对应于第 i 个结点）：
data left_child right_child
其中 data 是一个长度不超过 10 的字符串，left_child 和 right_child 分别是该结点的左右子结点编号。
所有结点编号从 1 到 N，NULL 用 -1 表示。
输入样例：
8
* 8 7
a -1 -1
* 4 1
+ 2 5
b -1 -1
d -1 -1
- -1 6
c -1 -1
输出样例：
(a+b)*(c*(-d))
*/

#include <stdio.h>

typedef struct TreeNode{
    char val[10];
    int l_idx; // 左孩子存放的下标值
    int r_idx; // 右子树存放的下标值
    int fa;
}TreeNode;

TreeNode Nodes[25];
int n;
int root;

void createExp(int u) { // 表达式的最外层(对应根节点)和操作数(对应叶节点)不需要加上括号
    if(u == -1) return;
    if(Nodes[u].l_idx == -1 && Nodes[u].r_idx == -1) {
        printf("%s", Nodes[u].val);
    }
    else {
        if(u != root) printf("(");
        createExp(Nodes[u].l_idx);
        printf("%s", Nodes[u].val);
        createExp(Nodes[u].r_idx);
        if(u != root) printf(")");
    }
}

int main(void) {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        scanf("%s%d%d", Nodes[i].val, &(Nodes[i].l_idx), &(Nodes[i].r_idx));
        Nodes[Nodes[i].l_idx].fa = i, Nodes[Nodes[i].r_idx].fa = i;
    }
    
    // 找到根节点,即fa为0的结点
    for(int i = 1; i <= n; i ++) 
        if(Nodes[i].fa == 0) {
            root = i;
            break;
        }
    createExp(root);
    return 0;
}