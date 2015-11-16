#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _node_s {
    int val;
    struct _node_s *parent;
    struct _node_s *left;
    struct _node_s *right;
} node_t;

node_t *build_binarytree() {
    node_t *root = (node_t *)malloc(sizeof(node_t) * 9);
    memset(root, 0, sizeof(node_t) * 9);
    root[0].val = 5;
    root[0].left = &root[1];
    root[0].right = &root[2];

    root[1].val = 4;
    root[1].parent = &root[0];
    root[1].left = &root[3];

    root[2].val = 8;
    root[2].parent = &root[0];
    root[2].left = &root[4];
    root[2].right = &root[5];

    root[3].val = 11;
    root[3].parent = &root[1];
    root[3].left = &root[6];
    root[3].right = &root[7];

    root[4].val = 13;
    root[4].parent = &root[2];

    root[5].val = 4;
    root[5].parent = &root[2];
    root[5].right = &root[8];

    root[6].val = 7;
    root[6].parent = &root[3];

    root[7].val = 2;
    root[7].parent = &root[3];

    root[8].val = 1;
    root[8].parent = &root[5];
    return root;
}

node_t *preorder_iterator(node_t *node) {
    if (node == NULL)
        return NULL;

    if (node->left != NULL) {
        return node->left;
    } else if (node->right != NULL) {
        return node->right;
    } else {
        node_t *parent;
        while (node != NULL) {
            parent = node->parent;
            if (parent == NULL)
                break;
            if (parent->right != NULL && parent->right != node)
                return parent->right;
            node = parent;
        }
        return NULL;
    }
    return NULL;
}

void preorder_printer(node_t *root) {
    node_t *node;
    for (node = root; node != NULL; node = preorder_iterator(node)) {
        fprintf(stdout, "%d ", node->val);
    }
    fprintf(stdout, "\n");
}

node_t *preorder_calc(node_t *node, int *sum) {
    if (node == NULL)
        return NULL;

    if (node->left != NULL) {
        return node->left;
    } else if (node->right != NULL) {
        return node->right;
    } else {
        node_t *parent;
        while (node != NULL) {
            parent = node->parent;
            *sum -= node->val;
            if (parent == NULL)
                break;
            if (parent->right != NULL && parent->right != node)
                return parent->right;
            node = parent;
        }
        return NULL;
    }
    return NULL;
}

void preorder_judge(node_t *root) {
    node_t *node;
    int sum = 0;
    for (node = root; node != NULL; node = preorder_calc(node, &sum)) {
        sum += node->val;
        if (node->left == NULL && node->right == NULL)
            fprintf(stdout, "leaf node: %d, path sum: %d\n", node->val, sum);
    }
}

int main(int argc, char **argv) {
    node_t *root;
    root = build_binarytree();
    preorder_printer(root);
    preorder_judge(root);
    free(root);
    return 0;
}
