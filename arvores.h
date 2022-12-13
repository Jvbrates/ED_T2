//
// Created by jvbrates on 12/9/22.
//
#include <stdbool.h>

#ifndef T2__ARVORES_H
#define T2__ARVORES_H
#include "lista.h"
#ifndef nullprt
#define nullptr NULL
#endif

typedef struct arv tree;

struct arv {
  void *data;
  tree * esq;
  tree * dir;
};

/* This function create a tree and set their childs as nullprt
  and set data to passed in argument*/
tree * createTree(void *data);


/* Add a node to tree, the balancete is not implemented*/
tree *addSample(tree *root, void *data, ordem (*f_lessthan)(void *, void *));


/* This function search in the tree using two argument functions one that verify
 * they equality and ohter than set if less than the comparative node*/
tree *search(tree *root, void *data, ordem (*f_search)(void *, void *));


//Specific

ordem placa_Ordem(void *data1, void *data2);

ordem marca_Ordem(void *data1, void *data2);

ordem ano_Ordem(void *data1, void *data2);

void * emordem(tree *root, void *data,void *(* Func)(void *, void *));

void * printTree(void *node, void* null);

#endif//T2__ARVORES_H