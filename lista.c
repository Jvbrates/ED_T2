//
// Created by jvbrates on 12/8/22.
//

#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define nullptr NULL

typedef  void * f(void *, void *);

//General


void * callback(lista  *list, void* f(void *, void *), void *data){
    for (lista * item = list; item != NULL ; item=item->next) {
        void * retorno =  f(item, data);
        if(retorno != NULL) {
            return retorno;
        }
    }

    return NULL;
}

//criaLista
lista * newList(void *data){
    lista * nL = malloc(sizeof(lista));
    nL->next = NULL;
    nL->previous = NULL;
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

    return NULL;
}

void * callbackDelete(lista*compar,  lista *remove){
    return callback(compar, deleteByPointer, remove);
}


//Spec

//bool higherThanPlaca(char *A, char *B);

void *addPlaca(void *list, void *dataVoid){
    veiculo *dataInsert = (veiculo *)dataVoid;
    veiculo *datacompar = (veiculo *)((lista *)list)->data;

    if(higherThanPlaca(dataInsert->placa, datacompar->placa)){
        lista * nL = newList(dataVoid);
        return insertNext(list, nL);
    }

    return NULL;

}

void *printVeiculo(void *list, void *nada){
    veiculo * v = (veiculo *)((lista*)list)->data;
    printf("PLACA: %s\n", v->placa);
    printf("MARCA: %s\n", v->marca);
    printf("ANO: %i\n\n\n", v->ano);

    return nullptr;
}

bool comparString(char *a, char*b);

void *searchByPlaca(void *Vlist, void *Vplaca){
    lista * list = (lista *)Vlist;
    char * placa = (char *)Vplaca;

    if(comparString(placa, ((veiculo *)list->data)->placa))
        return list;

    return nullptr;
}