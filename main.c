#include <stdio.h>
#include "lista.h"
#include "arvores.h"
#include <stdlib.h>

void addVehicle(lista **mainList, tree *byYear,
                tree *byLicensePlate, tree *byBrand)
{

  veiculo * nV = malloc(sizeof(veiculo));

  char * placa = malloc(sizeof(char)*100);
  char * marca = malloc(sizeof(char)*100);
  scanf("%s", marca);
  scanf("%s", placa);

  nV->placa = placa;
  nV->marca = marca;
  scanf("%i", &nV->ano);

  *mainList = addList(*mainList, newList(nV), placaOrdem);

}

int main() {
    printf("Hello, World!\n");

    lista *mainList = nullptr;
    tree  *byYear = nullptr;
    tree  *byLicensePlate = nullptr;
    tree  *byBrand = nullptr;

    int x;
    scanf("%i", &x);

    while (x){
      switch (x) {
      case 1: {
        addVehicle(&mainList, byYear, byLicensePlate, byBrand);
        break ;
      }

      case 2:{
        printf("\nDELETE%i\n", x);
        callback(mainList, printVeiculo, nullptr);
       // printVeiculo(mainList->previous, nullptr);
        printf("\nDELETE%i\n", x);
        mainList = callbackDelete(mainList, mainList->next->next->next);
        //printVeiculo(mainList->next->next, nullptr);

        printf("\nPRINTE%i\n", x);
        callback(mainList, printVeiculo, nullptr);
        return 0;
        break ;
      }}
      printf("%i", x);
      scanf("%i", &x);
    }




    return 0;
}
