/*
输入某二叉树的前序遍历和中序遍历的结果，请构建该二叉树并返回其根节点。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

Input: preorder = [-1], inorder = [-1]
Output: [-1]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/zhong-jian-er-cha-shu-lcof
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
class Solution {
public:
    unordered_map<int, int> save; // 存储中序结点中对应值所在的位置

    // 通过先序遍历序列的pl到pr号元素和中序遍历序列的il到ir号元素构建二叉树
    TreeNode* buildFun(vector<int>& preorder, int pl, int pr, vector<int>& inorder, int il, int ir) {
        TreeNode* root = new TreeNode(preorder[pl], NULL, NULL); // 先序遍历按照根左右的次序遍历,因此首个元素为当前的根节点
        int rootOfInorder = save[root -> val];                   // 找到根节点在中序结点的位置
        int len_L = rootOfInorder - il;                          // 其对应左子树的结点个数
        int len_R = ir - rootOfInorder;                          // 其对应右子树的结点个数
        if(len_L > 0)       // 左子树不空, 依据相应位置生成左子树, 右子树同理
            root -> left = buildFun(preorder, pl + 1, pl + len_L, inorder, il, rootOfInorder - 1);
        if(len_R > 0)
            root -> right = buildFun(preorder, pl + len_L + 1, pr, inorder, rootOfInorder + 1, ir);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() == 0) return NULL;
        for(int i = 0; i < inorder.size(); i ++) save[inorder[i]] = i;
        return buildFun(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
};