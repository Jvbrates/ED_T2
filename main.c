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
  *byBrand = addSample(*byBrand, nL, marca_Ordem);
  printf("Adding to LicensePlate\n");
  *byLicensePlate = addSample(*byLicensePlate, nL, placa_Ordem);
  printf("Adding to byYear\n");
  *byYear = addSample(*byYear, nL, ano_Ordem);

}

void listBy(lista *mainList, tree *byYear, tree *byBrand){
  int x = 0;
  printf("0 - Sort by \"Placa\"\n"
         "1 - Sort by Year\n"
         "2 - Sort by \"Marca\"\n");

  scanf("%i", &x);

  switch (x) {
    case 0: {
      callback(mainList, printVeiculo, nullptr);
      break;
    }
    case 1: {
      emordem(byYear, nullptr, printTree);
      break;
    }
    case 2: {
      emordem(byBrand, nullptr, printTree);
      break;
    }
  default:
    break ;
  }
}

void *searchBy(tree *byLicensePlate){
  char *query = malloc(sizeof(char)*100);

  printf("PLACA: ");
  veiculo queryWrapper;
  scanf("%s", query);
  lista wrapper;
  wrapper.data = &queryWrapper;
  queryWrapper.placa = query;
  printf("%s", query);
  tree *result = search(byLicensePlate, &wrapper, placa_Ordem);
  if (result) {
    printTree(result, nullptr);
    return result;
  }

  printf("Placa not found\n");
  return result;
}

int main() {
    printf("Hello, World!\n");

    lista *mainList = nullptr;
    tree  *byYear = nullptr;
    tree  *byLicensePlate = nullptr;
    tree  *byBrand = nullptr;

    int x;
/*    scanf("%i", &x);

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
        //return 0;
        break ;
      }}
      printf("%i", x);
      scanf("%i", &x);
    }

    printf("Em ordem por ano \n");
    emordem(byYear, nullptr, printTree);

    printf("Em ordem por marca \n");
    emordem(byBrand, nullptr, printTree);

    printf("Em ordem por Placa \n");
    emordem(byLicensePlate, nullptr, printTree);

    printf("A propria Lista\n");
    callback(mainList, printVeiculo, nullptr);*/

    do {
      printf("0 -- Exit\n"
             "1 -- Add\n"
             "2 -- List\n"
             "3 -- Search by \"Placa\"\n"
             );
      scanf("%i", &x);
      printf("___%i___", x);



      switch (x) {
        case 1:{
          addVehicle(&mainList, &byYear,
                     &byLicensePlate, &byBrand);
          break ;
        }
        case 2:{
          listBy(mainList, byYear, byBrand);
          break ;
        }
        case 3:{
          if(searchBy(byLicensePlate)){
            printf("Deletar:\n"
                   "0 -- Não\n"
                   "1 -- Sim\n");

            scanf("%i", &x);

            if(x){
              printf("Deletando\n");
            }

            x = 1;
          };
          break ;
        }
        default:{
          break;
        }
      }
    }while (x);
    return 0;
}
