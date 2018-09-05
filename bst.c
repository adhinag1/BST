#include<stdio.h>
#include<stdlib.h>

Node * newNode(Data d, Node * parent) {
    Node *n = malloc(sizeof(Node));

    n->left = n->right = NULL;
    n->parent = parent;
    n->data = d;
    return n;
}

Tree * newTree() {
    Tree * bst = malloc(sizeof(Tree));

    bst->root = NULL;
    bst->insert = insertTree;
    bst->search = searchTree;
    bst->sort = sortTree;
    bst->compare = compareTree;
    bst->clone = cloneTree;
    bst->delete = deleteTree;
    bst->removeData = removeData;
    return bst;
}

// Insert Operation
Data * insertNode(Node * node, Data data)
{
    if (node->data.value == data.value) {
        return NULL;
    }

    if (data.value < node->data.value) {
        if (node->left == NULL) {
            // add leaf
            Node * nl = newNode(data, node);
            node->left = nl;
            return &node->left->data;
        } else {
            insertNode(node->left, data);
        }
    } else if (data.value > node->data.value) {
        if (node->right == NULL) {
            // add leaf
            Node * nr = newNode(data, node);
            node->right = nr;
            return &node->right->data;
        } else {
            insertNode(node->right, data);
        }
    }
}

Data * insertTree(Tree * bst, Data value) {
    if (bst->root == NULL) {
        Node * n = newNode(value, NULL);
        bst->root = n;
        return &bst->root->data;
    } else {
        return insertNode(bst->root, value);
    }
}

// Search Operation
Data * searchData(Node * node, Data data) {
    if (data.value == node->data.value) {
        return &node->data;
    } else if (data.value < node->data.value) {
        if (node->left == NULL) {
            return NULL;
        } else {
            return searchData(node->left, data);
        }
    } else if (data.value > node->data.value) {
        if (node->right == NULL) {
            return NULL;
        } else {
            return searchData(node->right, data);
        }
    }
}

Data * searchTree(Tree * bst, Data value) {
    if (bst->root == NULL) {
        return NULL;
    } else {
        return searchData(bst->root, value);
    }
}

// Remove Data Operation
Node * searchNode(Node * node, Data data) {
    if (data.value == node->data.value) {
        return node;
    } else if (data.value < node->data.value) {
        if (node->left == NULL) {
            return NULL;
        } else {
            return searchNode(node->left, data);
        }
    } else if (data.value > node->data.value) {
        if (node->right == NULL) {
            return NULL;
        } else {
            return searchNode(node->right, data);
        }
    }
}

Node * searchMin(Node* node) {
    Node * current = node;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

Node * searchMax(Node* node) {
    Node * current = node;

    while (current->right != NULL) {
        current = current->right;
    }

    return current;
}


void removeLeaf(Tree * bst, Node * leaf) {
    if (bst->root == leaf) {
        free(leaf);
        leaf = NULL;
        bst->root = NULL;
        return;
    }

    if (leaf->parent->right == leaf) {
        leaf->parent->right = NULL;
    } else {
        leaf->parent->left = NULL;
    }
    // delete node
    free(leaf);
}

void shortCircuit(Tree * bst, Node * node) {

    if(node->parent==NULL)
    {
        if(node->right!=NULL)
        {
            bst->root=node->right;
            node->right->parent=NULL;
            node->right=NULL;
            free(node);
            return;
        }
        else if(node->left!=NULL)
        {
            bst->root=node->left;
            node->left->parent=NULL;
            node->left=NULL;
            free(node);
            return;
        }
    }

    if (bst->root == node)
    {
        free(node);
        node = NULL;
        return;
    }

    if (node->parent->right == node) {
        if (node->right == NULL) {
            node->parent->right = node->left;
            node->left->parent = node->parent;
        } else {
            node->parent->right = node->right;
            node->right->parent = node->parent;
        }
    } else {
        if (node->left == NULL) {
            node->parent->left = node->right;
            node->right->parent = node->parent;
        } else {
            node->parent->left = node->left;
            node->left->parent = node->parent;
        }
    }

    free(node);
    node = NULL;
}

void promotion(Tree * bst, Node * node)
{
    Node * d_node = searchMax(node->left);
    node->data = d_node->data;

    if (d_node->left == NULL && d_node->right == NULL) {
        removeLeaf(bst, d_node);
    }
    else
    {
        shortCircuit(bst, d_node);
    }
}

void removeData(Tree * bst, Data value) {
    if (bst->root == NULL) {
        free(bst);
        bst = NULL;
        return;
    }

    Node * node = searchNode(bst->root, value);
    if (node == NULL)
        return;

    if (node->left == NULL && node->right == NULL) {
        removeLeaf(bst, node);
    } else if ((node->left == NULL && node->right != NULL) || (node->left != NULL && node->right == NULL)) {
        shortCircuit(bst, node);
    } else if (node->left != NULL && node->right != NULL) {
        promotion(bst, node);
    }
}

// Sort Operation
int sortNode(Node * n, Data * value, int index)
{
    if (n->left != NULL)
        index = sortNode(n->left, value, index);

    value[index++] = n->data;

    if (n->right != NULL)
        index = sortNode(n->right, value, index);

    return index;
}

void sortTree(Tree * bst, Data * value) {
    if (bst->root != NULL)
    {
        sortNode(bst->root,value,0);
    }
}

// Compare Operation
int compareNodes(Node * n1, Node * n2)
{
    if(n1==NULL && n2==NULL)
        return 1;
    if (n1 != NULL && n2 != NULL)
    {
        return (n1->data.value == n2->data.value && compareNodes(n1->left, n2->left) && compareNodes(n1->right, n2->right));
    }
}

int compareTree(Tree * bst, Tree * copy_bst) {
    if (bst == NULL || copy_bst == NULL)
        return 0;

    if (bst->root == NULL && copy_bst->root == NULL)
        return 1;

    compareNodes(bst->root, copy_bst->root);
    return 1;
}

// Clone Operation
Node * cloneNodes(Node * node) {
    if(node == NULL) {
        return NULL;
    }

    Node * new_node = newNode(node->data, node);
    new_node->left = cloneNodes(node->left);
    new_node->right = cloneNodes(node->right);
    return new_node;
}

Tree * cloneTree(Tree * bst) {
    if(bst->root == NULL)
        return NULL;

    Tree * new_bst = newTree();
    new_bst->root = cloneNodes(bst->root);

    return new_bst;
}

// Delete Operaion
void deleteLeaf(Tree * bst, Node * node) {
    if (node == NULL)
        return;

    deleteLeaf(bst, node->left);
    deleteLeaf(bst, node->right);

    free(node);
    node = NULL;
    return; 
}

void deleteTree(Tree * bst) {
    if (bst == NULL) {
        return;
    }
    
    if (bst->root == NULL) {
        free(bst);
        bst = NULL;
        return;
    }

    deleteLeaf(bst, bst->root);
    free(bst);
    bst = NULL;
    return;
}