//
// Created by jvbrates on 12/9/22.
//
#include <stdbool.h>

#ifndef T2__ARVORES_H
#define T2__ARVORES_H

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
tree *addSample(tree *root, void *data, bool (*f_lessthan)(void *, void *));


/* This function search in the tree using two argument functions one that verify
 * they equality and ohter than set if less than the comparative node*/
tree *search(tree *root, void *data, bool (*f_find)(void *, void *), bool (*f_lessthan)(void *, void *));
#endif//T2__ARVORES_H

//Specific

bool placa_lessthan(void *data1, void *data2);

bool marca_lessthan(void *data1, void *data2);

bool placa_find(void *rootV, void *dataV);

bool marca_find(void *rootV, void *dataV);

bool ano_lessthan(void *data1, void *data2);

bool ano_find(void *rootV, void *dataV);

