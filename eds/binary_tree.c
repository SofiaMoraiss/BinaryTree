
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

typedef int (*CmpFn)(void *, void *);
typedef void (*KeyDestroyFn)(void *);
typedef void (*ValDestroyFn)(void *);

KeyValPair *key_val_pair_construct(void *key, void *val)
{
    KeyValPair *kvp = calloc(1, sizeof(KeyValPair));
    kvp->key= key;
    kvp->value= val;

    return kvp;

}
void key_val_pair_destroy(KeyValPair *kvp)
{
    if (kvp){
        free(kvp);
    }
    else {
        exit("KVP NULL!\n");
    }
}

Node *node_construct(void *key, void *value, Node *left, Node *right)
{
    Node *n = calloc(1, sizeof(Node));
    n->kvp = key_val_pair_construct(key, value);
    n->left = left;
    n->right = right;

    return n;
    
}

void node_destroy(Node *node)
{
    if (node){
        key_val_pair_destroy(node->kvp);
        free(node);
    }
    else {
        exit("TRIED TO DESTROY NULL NODE!\n");
    }
}

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn)
    {
        BinaryTree * bt = calloc(1, sizeof(BinaryTree));
        bt->root= NULL;
        bt->cmp_fn= cmp_fn;
        bt->key_destroy_fn = key_destroy_fn;
        bt->val_destroy_fn = val_destroy_fn;

        return bt;
    }


void binary_tree_add(BinaryTree *bt, void *key, void *value)
{
    Node *newNode = node_construct(key, value, NULL, NULL);
    if (binary_tree_empty(bt)){
        bt->root=newNode;
        return;
    }
    Node * currentNode = bt->root;
    int cmp=0;
    while(1)
    {
        if (!currentNode){
            printf("ERROR: Got to null node at insertion!\n");
        }
        cmp=bt->cmp_fn(key,currentNode->kvp->key);
        if (!cmp){
            currentNode->kvp->value=value;
            return;
        }
        else if(cmp<0){
            if(currentNode->left){
                currentNode=currentNode->left;
                continue;
            }
            else {
                currentNode->left=newNode;
                return;
            }
        }
        else if(cmp>0){
            if(currentNode->right){
                currentNode=currentNode->right;
                continue;
            }
            else {
                currentNode->right=newNode;
                return;
            }
        }
    }
}

int binary_tree_empty(BinaryTree *bt){
    if (bt->root==NULL){
        return 1;
    }
    return 0;
}
void binary_tree_remove(BinaryTree *bt, void *key)
{

}
KeyValPair *binary_tree_min(BinaryTree *bt)
{
    if (binary_tree_empty(bt)){
        return NULL;
    }
    Node * currentNode = bt->root;

    while(currentNode->left)
    {
        currentNode=currentNode->left;
    }
    return currentNode->kvp;
}
KeyValPair *binary_tree_max(BinaryTree *bt)
{
    if (binary_tree_empty(bt)){
        return NULL;
    }
    Node * currentNode = bt->root;

    while(currentNode->right)
    {
        currentNode=currentNode->right;
    }
    return currentNode->kvp;
}
KeyValPair *binary_tree_pop_min(BinaryTree *bt){
    if (binary_tree_empty(bt)){
        return NULL;
    }
    Node * currentNode = bt->root;
    Node * previousNode = NULL;

    while(currentNode->left)
    {
        previousNode=currentNode;
        currentNode=currentNode->left;
    }
    previousNode->left=NULL;
    return currentNode->kvp;
}
KeyValPair *binary_tree_pop_max(BinaryTree *bt)
{
    if (binary_tree_empty(bt)){
        return NULL;
    }
    Node * currentNode = bt->root;
    Node * previousNode = NULL;

    while(currentNode->right)
    {
        previousNode=currentNode;
        currentNode=currentNode->right;
    }
    previousNode->right=NULL;
    return currentNode->kvp;
}
void *binary_tree_get(BinaryTree *bt, void *key)
{
    Node * currentNode = bt->root;
    int cmp=0;
    while(currentNode)
    {
        cmp=bt->cmp_fn(key,currentNode->kvp->key);
        if (!cmp){
            return currentNode->kvp->value;
        }
        else if(cmp<0){
            currentNode=currentNode->left;
            continue;
        }
        else if(cmp>0){
            currentNode=currentNode->right;
            continue;
        }
    }
    return NULL;
}

void binary_tree_node_free(Node *n){
    if (n==NULL){
        return;
    }
    binary_tree_node_free(n->left);
    binary_tree_node_free(n->right);
    node_destroy(n);
    
}
void binary_tree_destroy(BinaryTree *bt)
{
    if (binary_tree_empty(bt)){
        return;
    }
    binary_tree_node_free(bt->root);
    bt->root=NULL;
    free(bt);
}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);