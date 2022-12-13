//
// Created by jvbrates on 12/8/22.
//

#ifndef T2__LISTA_H
#define T2__LISTA_H

#ifndef nullprt
#define nullptr NULL
#endif
#include <string.h>
#include <stdbool.h>
//Struct
typedef struct L lista;
struct L {
    void *data;
    lista* next;
    lista* previous;
    //lista * father;
};

typedef
enum ordem{
  EQUAL = 0,
  HIGHER = 1,
  LESS = -1
} ordem;
//Generic

/* Gets the list pointer then execute f(list, data), next execute recursively for the list->next
  It'll be make while the f return a non null pointer or list->next not is null, and return that
  occurs first*/
void * callback(lista  *list, void* f(void *, void *), void *data);

/* Sample function that create a list and se the next end previous as null and this->data = data argument,
   then return it*/
lista * newList(void *data);


/* This function is designed to used by callback, for this the arguments is write as void,
  but it would be lista* type. The function get two pointers, if they pointer from the same value,
  then the item is removed from the jail of lists and deleted, the pointer from previous and next
  is correctly organized from this function
  Return the previous list from the list that is removed
  OBS: This function not delete the data restrained by the lista */
void * deleteList(lista *remove);

/* This function execute the deletebypointer using the callback function*/
void * callbackDelete(lista*compar,  lista *remove);

void *addList(lista * list, lista *nList, ordem (*order_function)(void *, void *));


ordem placaOrdem(void *A, void *B);

//Specific

typedef struct {
    int ano;
    char* marca;
    char* placa;
} veiculo;


/* This function print the struct veiculo that is in the list->data, this is designed
 * to use soo as callback, for this need of the void* nada argument even though it's useless*/
void *printVeiculo(void *list, void *nada);
/* This func dealloc the struct veiculo and their dynamic variables*/
void deleteDataVehicle(void *dataV);

#endif//T2__LISTA_H
