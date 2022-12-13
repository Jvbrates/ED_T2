#include <stdio.h>
#include "lista.h"
#include "arvores.h"
#include <stdlib.h>

void addVehicle(lista **mainList, tree **byYear,
                tree **byLicensePlate, tree **byBrand)
{

  veiculo * nV = malloc(sizeof(veiculo));

  char * placa = malloc(sizeof(char)*100);
  char * marca = malloc(sizeof(char)*100);

  scanf("%s", marca);
  scanf("%s", placa);
  scanf("%i", &nV->ano);

  nV->placa = placa;
  nV->marca = marca;

  lista * nL = newList(nV);
  printf("Adding to mainList\n");
  *mainList = addList(*mainList, nL, placaOrdem);
  printf("Adding to byBrand\n");
  *byBrand = addSample(*byBrand, nL, marca_lessthan);
  printf("Adding to LicensePlate\n");
  *byLicensePlate = addSample(*byLicensePlate, nL, placa_lessthan);
  printf("Adding to byYear\n");
  *byYear = addSample(*byYear, nL, ano_lessthan);

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
        addVehicle(&mainList, &byYear,
                   &byLicensePlate, &byBrand);
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

    printf("Em ordem por ano \n");
    emordem(byYear, nullptr, printTree);



    return 0;
}
