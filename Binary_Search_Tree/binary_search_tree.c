#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* Binary Search Tree is a tree with the following properties
 * A valid BST is defined as follows:
 * The left subtree of a node contains only nodes with keys less than the node's key.
 * The right subtree of a node contains only nodes with keys greater than the node's key.
 * Both the left and right subtrees must also be binary search trees.
 *
 * Insertion :- O(h) Worst case is O(n) in case of skewed tree
 * Inorder is always sorted of a valid BST
 *
 *
 */
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} TreeNode;

TreeNode* create_node(int val) {
    TreeNode * tmp = malloc(sizeof(TreeNode));
    tmp->data = val;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

TreeNode* insert_bst_node(TreeNode *node, int val) {
    if(node==NULL) {
        return create_node(val);
    }

    if(val < node->data)
       node->left = insert_bst_node(node->left, val);
    else
       node->right = insert_bst_node(node->right, val);

    return node;
}
void print_inorder(TreeNode *root) {
    if(root != NULL) {
        print_inorder(root->left);
        printf("%d ", root->data);
        print_inorder(root->right);
    }
}
void print_inorder_tree(TreeNode *root) {
    print_inorder(root);
    printf("\n");
}
bool __validate_bst(TreeNode* root, TreeNode* high, TreeNode *low) {
    if(root == NULL) 
        return true;

    if((high!= NULL && root->data > high->data) ||
       (low != NULL && root->data < low->data))
        return false;

    return __validate_bst(root->left, root, low) &&
           __validate_bst(root->right, high, root);
}

bool validate_bst(TreeNode *root) {
    return __validate_bst(root, NULL, NULL);
}

/*Search a Binary Seacrh Tree */
void search_bst(TreeNode *root, int val, int *count) {
    if(root!= NULL) {
        search_bst(root->left, val, count);
        if(val == root->data)
            (*count)++;
        search_bst(root->right, val, count);
    }
}

/* Given a non-empty binary search
   tree, return the node
   with minimum key value found in
   that tree. Note that the
   entire tree does not need to be searched. */

TreeNode *get_inorder_successor(TreeNode *root) {

    TreeNode *tmp = root;
    while(tmp && tmp->left != NULL)
        tmp = tmp->left;

    return tmp;
}

/*Delete a Node in Binary Search Tree*/

TreeNode *delete_bst(TreeNode *root, int val) {
/* 3 cases are there
 * a) Node to be deleted is leaf : just delete the Node
 * b) Node to be deleted has only one child : Copy the Child's data to the Node and delete the child
 * c) Node to be deleted has two children : Find inorder successor of this node and replace that node and delete the inorder successor
 */

    if(root == NULL) {
        return root;
    }

    if(val < root->data) {
        root->left = delete_bst(root->left, val);
    } 
    else if(val > root->data) {
        root->right = delete_bst(root->right, val);
    } else {
        if(root->left == NULL) {
            TreeNode *tmp = root->right;
            free(root);
            return tmp;
        } else if(root->right == NULL) {
            TreeNode *tmp = root->left;
            free(root);
            return tmp;
        }
        TreeNode *tmp = get_inorder_successor(root->right);
        root->data = tmp->data;
        root->right = delete_bst(root->right, tmp->data);
    }
    return root;
}
int main() {
    TreeNode *root = NULL;
    root=insert_bst_node(root, 50);
    insert_bst_node(root, 10);
    insert_bst_node(root, 20);
    insert_bst_node(root, 40);
    insert_bst_node(root, 50);
    insert_bst_node(root, 60);
    insert_bst_node(root, 30);
    insert_bst_node(root, 40);
    insert_bst_node(root, 20);

    print_inorder_tree(root);

    bool check = validate_bst(root);
    printf("This is a %s binary search tree\n", (check ? "valid" : "invalid"));
    

    int numlist = 0; 
    int val = 20;
    search_bst(root, val, &numlist);

    if(numlist == 0)
        printf("%d is not found\n", val);
    else
        printf("%d is found %d times\n", val, numlist);
/* This is delete bst without optimization */
    for (int i=0; i<numlist; i++) {
        root = delete_bst(root, val);
    }

    print_inorder_tree(root);
    

    TreeNode *root1 = NULL;
    root1 = create_node(12);
    root1->left = create_node(11);

    print_inorder_tree(root1);

    
    check = validate_bst(root1);
    printf("This is a %s binary search tree\n", (check ? "valid" : "invalid"));
    


    return 0;
}

