/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，
最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
 
示例 1：
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。

示例 2：
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 采用非递归后序遍历的思想,因为按照左子树、右子树、根节点的次序遍历,当访问到某一结点时,栈中存储的就是该节点的祖先结点了
// 左子树、右子树中的结点都完全了访问出栈了.
// 访问两个不同的结点,一定会存在先后顺序,若第一个结点被访问到了,就把要将其栈先存起来,栈中存储的是第一个结点的祖先,
// 当第二个结点被访问到了,那么也就存储了第二个结点的所有祖先,从栈顶开始,比较两个栈中出现的第一个相同的结点就是所求

class Solution {
public:
    // 将sta中的元素加入que,因为不想改动sta内的值,故使用函数处理;que是引用,可以使得que的值可以被改变
    void copy(stack<TreeNode*> sta, queue<TreeNode*> &que) { 
        while(!sta.empty()) {
            que.push(sta.top());
            sta.pop();
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;
        stack<TreeNode*> sta;
        queue<TreeNode*> que; // 副本,因为最后想要依次对比的是p和q两个祖先栈的栈顶位置,保存副本是需要进行出栈操作,使得原先栈顶位置变为栈底,因此这里使用队列来存储,队头元素即为原先的栈顶元素
        TreeNode* op = root;
        TreeNode* tag = NULL; // 标记上一个被访问过的结点
        int cnt = 0; // 统计p和q中已经有几个结点被访问到了
        while(op || !sta.empty()) {
            if(op) {
                sta.push(op);
                op = op -> left;
            }
            else {
                op = sta.top();
                if(op -> right && op -> right != tag) { // 当前结点尚存在未被访问过的右子树
                    op = op -> right;
                }
                else { // 当前结点应该被访问遍历到,这里只要将结点弹出即可
                    if(op == p || op == q) { // cnt=0时产生当前栈的副本(用队列存),便于后序的比较操作
                        if(cnt == 0) {
                            copy(sta, que);
                            cnt ++;
                        }
                        else break;
                    }
                    sta.pop();
                    tag = op;
                    op = NULL;
                }
            }
        }
        // 二叉树没有环路,所以从根开始到树上的结点的路径是唯一的
        // 所以p、q各自的祖先栈中的栈底到栈最近公共祖先的位置的部分是重合的,因为都是记录到最近公共祖先结点的路径
        // 换句话说,若一个栈保存的元素比另一个栈元素要多,那么这个栈内多出来的元素必定不会是二者的最近公共祖先,因此将这些多余元素全部剔除,再依次从等长的位置比较即可
        int dis = sta.size() - que.size();
        if(dis > 0)  while(dis --) sta.pop();
        else while(dis ++) que.pop();
        while(sta.top() != que.front()) sta.pop(), que.pop();
        return sta.top();
    }
};