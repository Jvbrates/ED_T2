//
// Created by jvbrates on 12/9/22.
//

#include "arvores.h"
#include <stdlib.h>
#include "lista.h"
#include <string.h>

//General
tree * createTree(void *data){

    tree * nT = malloc(sizeof (tree));

    nT->data = data;
    nT->esq = nullptr;
    nT->dir = nullptr;

    return nT;
}

tree *addSample(tree *root, void *data, ordem (*f_lessthan)(void *, void *)){
    if(root){
      //printf("Antes de F_lessthan\n");
        if((*f_lessthan)(data, root->data) == HIGHER){
            //printf("Erro em F_lessthan\n");
            root->dir = addSample(root->dir, data, f_lessthan);
        } else{
            //printf("Indo à esquerda\n");
            root->esq = addSample(root->esq, data, f_lessthan);

        }


    } else {
        tree * nNode = createTree(data);
        return nNode;
    }

    return root;
}

tree *moreLeft(tree *T, tree **father){
  if(T->esq){
    *father = T;
    return moreLeft(T->esq, father);
  }
  return T;
}


tree *search(tree *root, void *data, ordem (*f_search)(void *, void *), tree **father){
    if(root){
      ordem result = f_search(root->data, data);
      if(result == EQUAL){
        //printf("Igual\n");
        return root;
      } else if (result == LESS){
        *father = root;//Buffer
        return search(root->dir, data, f_search, father);
      } else {
        *father = root;
        return search(root->esq, data, f_search, father);
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

void * emordemDelete(tree *root, void *data){
  if(!root)
    return nullptr;

  if(root->data == data){
    if(root->esq && root->dir){
      tree  * T  = moreLeft(root->dir, nullptr);
      root->data = T->data;
      root->dir = emordemDelete(root->dir, T);

      return root;
    } else if (!root->esq){
      tree  * T = root->dir;
      free(root);
      return T;
    } else {
      tree  * T = root->esq;
      free(root);
      return T;
    }
  }


    root->esq = emordemDelete(root->esq, data);
    root->dir = emordemDelete(root->dir, data);

  return root;
}

void destroy(tree *root){
  if(root){
    destroy(root->esq);
    destroy(root->dir);

    free(root);
  }
}

//Spec

ordem placa_Ordem(void *data1, void *data2){
  veiculo *v1 = (veiculo *)((lista *)data1)->data;
  veiculo *v2 = (veiculo *)((lista *)data2)->data;
  int x =  strcmp(v1->placa, v2->placa);

  if(x == 0 )
    return  EQUAL;
  if(x>0)
    return HIGHER;
  return LESS;
}

ordem marca_Ordem(void *data1, void *data2){
  veiculo *v1 = (veiculo *)((lista *)data1)->data;
  veiculo *v2 = (veiculo *)((lista *)data2)->data;
  int x =  strcmp(v1->marca, v2->marca);

  if(x == 0 )
    return  EQUAL;
  if(x>0)
    return HIGHER;
  return LESS;
}

//Ano
ordem ano_Ordem(void *data1, void *data2){
  int year1 =  ((veiculo *)((lista *)data1)->data)->ano;
  int year2 =  ((veiculo *)((lista *)data2)->data)->ano;

  if(year1 > year2){
    return HIGHER;
  }

  if(year1 < year2){
    return LESS;
  }

  return EQUAL;
}



void * printTree(void *node, void* null){
  printVeiculo(((tree *)node)->data, nullptr);

  return  nullptr;
}