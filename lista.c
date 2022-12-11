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

lista * insertNext(lista *source, lista *new){
    lista * temp = source->next;
    source->next = new;
    new->previous = source;
    new->next = temp;

    if(temp)
        temp->next = new;

    return new;
}

void * deleteByPointer(void*Vcompar,  void *Vremove){
    lista * compar = (lista *)Vcompar;
    lista * remove = (lista *)Vremove;


    if(compar == remove){
        if(remove->next)
            remove->next->previous = remove->previous;

        if(remove->previous)
            remove->previous->next = remove->next;

        free(remove);
        return remove;//Alright
    }

    return nullptr;
}

void * callbackDelete(lista*compar,  lista *remove){
    return callback(compar, deleteByPointer, remove);
}


//Spec

bool higherThanPlaca(char *A, char *B){
    int x = strcmp(A, B);
    if(x > 0)
      return true;
    return false;
};

void *addPlaca(void *list, void *dataVoid){
    veiculo *dataInsert = (veiculo *)dataVoid;
    veiculo *datacompar = (veiculo *)((lista *)list)->data;

    if(higherThanPlaca(dataInsert->placa, datacompar->placa)){
        lista * nL = newList(dataVoid);
        return insertNext(list, nL);
    }

    return nullptr;

}

void *printVeiculo(void *list, void *nada){
    veiculo * v = (veiculo *)((lista*)list)->data;
    printf("PLACA: %s\n", v->placa);
    printf("MARCA: %s\n", v->marca);
    printf("ANO: %i\n\n\n", v->ano);

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