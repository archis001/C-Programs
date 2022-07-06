#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

    if((high!= NULL && root->data >= high->data) ||
       (low != NULL && root->data < low->data))
        return false;

    return __validate_bst(root->left, root, low) &&
           __validate_bst(root->right, high, root);
}

bool validate_bst(TreeNode *root) {
    return __validate_bst(root, NULL, NULL);
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
    
    TreeNode *root1 = NULL;
    root1 = create_node(12);
    root1->left = create_node(11);

    print_inorder_tree(root1);

    check = validate_bst(root1);
    printf("This is a %s binary search tree\n", (check ? "valid" : "invalid"));
    


    return 0;
}

