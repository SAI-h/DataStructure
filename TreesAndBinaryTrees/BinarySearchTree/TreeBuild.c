#include <stdio.h>
#include <stdlib.h>

#define NOT_FOUND -10010

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
}*Tree, TreeNode;

int n;

// find the minimum
int findMin(Tree bst) {
    while(bst -> left) bst = bst -> left;
    return bst -> val;
}

// find the maximum
int findMax(Tree bst) {
    while(bst -> right) bst = bst -> right;
    return bst -> val;
}

void insert(Tree *bst, int data) {
    if(*bst == NULL) {
        *bst = (Tree)malloc(sizeof(struct TreeNode));
        (*bst) -> val = data;
        (*bst) -> left = (*bst) -> right = NULL;
    }
    else {
        if(data < (*bst) -> val) // less than the value of root
            insert(&((*bst) -> left), data);
        else                     // greater than the value of root
            insert(&((*bst) -> right), data);
    }
}

TreeNode* delItem(TreeNode **u, int item) {
    if(*u == NULL) return NULL;
    else if((*u) -> val < item) (*u) -> right = delItem(&((*u) -> right), item);
    else if((*u) -> val > item) (*u) -> left = delItem(&((*u) -> left), item);
    else {
        TreeNode* ret = *u;
        // If the node which we want to delete is the leaf, we can free the space directly.
        if((*u) -> left == NULL && (*u) -> right == NULL) {
            ret = NULL;
            free(*u);
        }
        // If the deleted node only has the one-side subtree, consider the subtree as a node which
        // linked the deleted node. We can do the remove operation the same as removing a node from a linklist.
        else if((*u) -> left == NULL) {
            TreeNode* tmp = *u;
            *u = (*u) -> right;
            free(*u);
        }
        else if((*u) -> right == NULL) {
            TreeNode* tmp = *u;
            *u = (*u) -> left;
            free(*u);
        }
        // If the deleted node has two-sides substree, the improper operation would disorder the sequence of BST.
        // Think about which situation is easy to remove the item. Yep, the one-side subtree!
        // To keep the order of BST, we can replace the value of the deleted node by its immediate successor's.
        // Due to its immediate successor is the smallest node of its right subtree, after the operation, 
        // it would greater than the nodes of its left substree as well as less than the nodes of its right subtree.
        // The immediate successor must be a node that has no subtree or no left subtree.
        // So the question is change to how to delete this successor node.
        else {
            int newItem = findMin((*u) -> right);
            (*u) -> val = newItem;
            (*u) -> right = delItem(&((*u) -> right), newItem);
        }
        return ret;
    }
}

TreeNode* findItem(Tree bst, int data) {
    if(bst == NULL) return bst;
    else if(bst -> val < data) return findItem(bst -> right, data);
    else if(bst -> val > data) return findItem(bst -> left, data);
    else return bst;
}

int findPre(Tree bst, int data) {
    TreeNode* item = findItem(bst, data);
    if(item == NULL) return NOT_FOUND;
    else if(item -> left) return findMax(item -> left);
    else {
        int preItem = bst -> val;
        while(bst != item) {
            if(bst -> val < item -> val) {
                preItem = bst -> val;
                bst = bst -> right;
            }
            else bst = bst -> left;
        }
        return preItem;
    }
}

int findNxt(Tree bst, int data) { // The immediate successor is to the right of the node which valued of 'data'.
    TreeNode* item = findItem(bst, data);
    if(item == NULL) return NOT_FOUND;
    else if(item -> right) return findMin(item -> right); // If the item has the right subtree, the smallest node of its right subtree is the answer.
    else { // Otherwise, the immediate successor is the nearest ancestor node which is right to the item(greater than the item).
        // The ancestor node must be on a path from the root to the item.
        // Generate this path, before reaching the item, each step will be fitted up to the answer node.
        int nxtItem = bst -> val;
        while(bst != item) {
            // Only if a node on the path is greater than the value of the item, then it has the chance to be the immediate successor node.
            if(bst -> val > item -> val) { 
                nxtItem = bst -> val;
                bst = bst -> left;
            }
            else bst = bst -> right;
        }
        return nxtItem;
    }
}

void freeSpace(Tree *bst) {
    if((*bst) -> left) {
        freeSpace(&((*bst) -> left));
        (*bst) -> left = NULL;
    }
    if((*bst) -> right) {
        freeSpace(&((*bst) -> right));
        (*bst) -> right = NULL;
    }
    if((*bst) -> left == NULL && (*bst) -> right == NULL) {
        free(*bst);
    }
}

void show(Tree bst) {
    if(bst == NULL) return;
    show(bst -> left);
    printf("%d ", bst -> val);
    show(bst -> right);
}

int main(void) {
    Tree bst = NULL;
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        int op, x;
        scanf("%d%d", &op, &x);
        if(op == 1) {
            insert(&bst, x);
        }
        else if(op == 2) {
            delItem(&bst, x);
        }
        else if(op == 3){
            printf("%d\n", findPre(bst, x));
        }
        else {
            printf("%d\n", findNxt(bst, x));
        }
        printf("After the opeartion_%d, the inorder traversal sequence of the BST is:\n", i);
        show(bst);
        printf("\n");
    }
    freeSpace(&bst);
    return 0;
}