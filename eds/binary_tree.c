
#include "vector.h"
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
        //bt->root= node_construct(NULL, NULL, NULL, NULL);
        bt->cmp_fn= cmp_fn;
        bt->key_destroy_fn = key_destroy_fn;
        bt->val_destroy_fn = val_destroy_fn;

        return bt;
    }
void binary_tree_add(BinaryTree *bt, void *key, void *value);
int binary_tree_empty(BinaryTree *bt);
void binary_tree_remove(BinaryTree *bt, void *key);
KeyValPair *binary_tree_min(BinaryTree *bt);
KeyValPair *binary_tree_max(BinaryTree *bt);
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);
void *binary_tree_get(BinaryTree *bt, void *key);
void binary_tree_destroy(BinaryTree *bt);

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
// void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);