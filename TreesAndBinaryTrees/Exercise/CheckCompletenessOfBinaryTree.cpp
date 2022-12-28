/*
给定一个二叉树的 root ，确定它是否是一个 完全二叉树 。
在一个 完全二叉树 中，除了最后一个关卡外，所有关卡都是完全被填满的，并且最后一个关卡中的所有节点都是尽可能靠左的。它可以包含 1 到 2h 节点之间的最后一级 h 。

输入：root = [1,2,3,4,5,6]
输出：true
解释：最后一层前的每一层都是满的（即，结点值为 {1} 和 {2,3} 的两层），且最后一层中的所有结点（{4,5,6}）都尽可能地向左。

输入：root = [1,2,3,4,5,null,7]
输出：false
解释：值为 7 的结点没有尽可能靠向左侧。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/check-completeness-of-a-binary-tree
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// 按照层次遍历去依次各个结点, 若一棵二叉树是完全二叉树的话,那么只有最后连续的一段树节点是空结点
// 因此可以如果遇到了空结点则将其先进行标记,若在后序的遍历过程中遇到了非空结点说明该二叉树不是完全二叉树

class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> que;
        que.push(root);
        bool flag = false; // 标记是否出现过空结点
        while(!que.empty()) {
            TreeNode* top = que.front();
            que.pop();
            if(top && flag) return false;
            if(!top) flag = true;
            else {
                que.push(top -> left);
                que.push(top -> right);
            }
        }
        return true;
    }
};