//
// Created by jvbrates on 12/9/22.
//

#include "arvores.h"
#include <stdlib.h>
#include "lista.h"
#include <string.h>
#include <stdio.h>


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
      printf("Antes de F_lessthan\n");
        if((*f_lessthan)(root->data, data)){
            printf("Erro em F_lessthan\n");
            root->dir = addSample(root->dir, data, f_lessthan);
        } else {
            printf("Erro em F_lessthan\n");
            root->esq = addSample(root->esq, data, f_lessthan);
        }


    } else {
        printf("Não deve cair aqui\n");
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

void * preOrdem(tree *root, void *data,void *(* Func)(void *, void *)){
  if(root){
    void * retorno = Func(root, data);
    if(!retorno){
      retorno = preOrdem(root->esq, data, Func);

      if(!retorno) {
        return  preOrdem(root->dir, data, Func);
      }
      return retorno;
    }else{
      return retorno;
    }


  }
  return nullptr;
}


void * emordem(tree *root, void *data,void *(* Func)(void *, void *)){
  if(root){
    void * retorno = emordem(root->esq, data, Func);
    if(retorno){
      return retorno;
    }
    retorno = Func(root, data);

    if(retorno){
      return retorno;
    }

    return emordem(root->dir, data, Func);
  }
  return nullptr;
}
//Spec

bool placa_lessthan(void *data1, void *data2){
  veiculo *v1 = (veiculo *)((lista *)data1)->data;
  veiculo *v2 = (veiculo *)((lista *)data2)->data;

  int x = strcmp(v1->placa, v2->placa);

  if(x < 0)
    return true;
  return false;
}

bool marca_lessthan(void *data1, void *data2){
  veiculo *v1 = (veiculo *)((lista *)data1)->data;
  veiculo *v2 = (veiculo *)((lista *)data2)->data;

  int x = strcmp(v1->marca, v2->marca);

  if(x < 0)
    return true;
  return false;
}

bool placa_find(void *rootV, void *dataV){
  veiculo  * v1 = (veiculo *)((lista *)rootV)->data;
  char  * v2 = (char *)dataV;

  return !strcmp(v1->placa, v2);

}

bool marca_find(void *rootV, void *dataV) {
  veiculo *v1 = (veiculo *)((lista *)rootV)->data;
  char *v2 = (char *)dataV;

  return !strcmp(v1->marca, v2);
}


//Ano
bool ano_lessthan(void *data1, void *data2){
  veiculo *v1 = (veiculo *)((lista *)data1)->data;
  veiculo *v2 = (veiculo *)((lista *)data2)->data;

  return (v1->ano < v2->ano);

}

bool ano_find(void *rootV, void *dataV) {
  veiculo *v1 = (veiculo *)((lista *)rootV)->data;
  int *v2 = (int *)dataV;
  return (v1->ano == *v2);
}

//Print

void * printTree(void *node, void* null){
  printVeiculo(((tree *)node)->data, nullptr);

  return  nullptr;
}