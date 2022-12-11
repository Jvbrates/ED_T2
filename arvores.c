//
// Created by jvbrates on 12/9/22.
//

#include "arvores.h"
#include <stdlib.h>
#include <stdbool.h>
#ifndef nullprt
#define nullptr NULL
#endif
typedef struct arv tree;

struct arv {
    void *data;
    tree * esq;
    tree * dir;
};

//General
tree * createTree(void *data){

    tree * nT = malloc(sizeof (tree));

    nT->data = data;
    nT->esq = nullptr;
    nT->dir = nullptr;

    return nT;
}

tree *addSample(tree *root, void *data, bool (*f_lessthan)(void *, void *)){
    if(root){
        if((*f_lessthan)(root, data)){
            root->dir = addSample(root->dir, data, f_lessthan);
        } else {
            root->esq = addSample(root->esq, data, f_lessthan);
        }
    } else {
        tree * nNode = createTree(data);
        return nNode;
    }

    return root;
}

tree *search(tree *root, void *data, bool (*f_find)(void *, void *), bool (*f_lessthan)(void *, void *)){
    if(root && !(*f_find)((void *)root, data)){
        if((*f_lessthan)(root->data, data)){
            return search(root->dir, data, f_find, f_lessthan);
        } else {
            return search(root->esq, data, f_find, f_lessthan);
        }
    }
    return root;
}

//Spec