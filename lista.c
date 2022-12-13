//
// Created by jvbrates on 12/8/22.
//

#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef  void * f(void *, void *);

//General


void * callback(lista  *list, void* f(void *, void *), void *data){
    for (lista * item = list; item != nullptr ; item=item->next) {
        void * retorno =  f(item, data);
        if(retorno != nullptr) {
            return retorno;
        }
    }

    return nullptr;
}

//criaLista
lista * newList(void *data){
    lista * nL = malloc(sizeof(lista));
    nL->next = nullptr;
    nL->previous = nullptr;
    nL->data = data;

    return nL;
}



void * deleteList(lista *remove){


  printVeiculo(remove, nullptr);
  if(remove->next) {
    remove->next->previous = remove->previous;
  }

  if(remove->previous) {

    printVeiculo(remove->previous, nullptr);
    remove->previous->next = remove->next;
    }

    //free(remove);
    return remove->next;
}

void * callbackDelete(lista*compar,  lista *remove){

  if(!compar || !remove){
    return compar;
  }
  if(compar == remove){
    deleteList(remove);
    return compar->next;
  }

  compar->next = callbackDelete(compar->next, remove);

  return compar;
}

void *addList(lista * list, lista* nList, ordem (*order_function)(void *, void *)){
  if(list){
    ordem r = order_function(list->data, nList->data);
    if(r == LESS){
      list->next = addList(list->next, nList, order_function);
      printf("LESS\n");
      return list;
    } else if (r == HIGHER){
      printf("HIGHER\n");
      lista  * T = nList;
      T->next = list;
      T->previous = list->previous;

      if(list->previous){
        list->previous->next = T;
      }

      //T->previous = list;

      return  T;
    } else {
      printf("IGUAL??\n");
    }

    return list;

  }

  return nList;
}

//Spec

bool higherThanPlaca(char *A, char *B){
    int x = strcmp(A, B);
    if(x > 0)
      return true;
    return false;
};


ordem placaOrdem(void *A, void *B){

  int x =  strcmp(((veiculo *)A)->placa, ((veiculo *)B)->placa);

  if(x == 0 )
    return  EQUAL;
  if(x>0)
    return HIGHER;
  return LESS;
}

void *printVeiculo(void *list, void *nada){

  if(list) {
    veiculo *v = (veiculo *)((lista *)list)->data;
    printf("PLACA: %s\n", v->placa);
    printf("MARCA: %s\n", v->marca);
    printf("ANO: %i\n\n\n", v->ano);
  }
  return nullptr;
}

bool comparString(char *a, char*b){
    return !strcmp(a, b);
};

void *searchByPlaca(void *Vlist, void *Vplaca){
    lista * list = (lista *)Vlist;
    char * placa = (char *)Vplaca;

    if(comparString(placa, ((veiculo *)list->data)->placa))
        return list;

    return nullptr;
}