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
  printf("Marca:\n");
  scanf("%s", marca);
  printf("Placa:\n");
  scanf("%s", placa);
  printf("Ano:\n");
  scanf("%i", &nV->ano);

  nV->placa = placa;
  nV->marca = marca;

  lista * nL = newList(nV);
  printf("Adding to mainList...\n");
  *mainList = addList(*mainList, nL, placaOrdem);
  printf("Adding to byBrand...\n");
  *byBrand = addSample(*byBrand, nL, marca_Ordem);
  printf("Adding to LicensePlate...\n");
  *byLicensePlate = addSample(*byLicensePlate, nL, placa_Ordem);
  printf("Adding to byYear...\n");
  *byYear = addSample(*byYear, nL, ano_Ordem);

}

void listBy(lista *mainList, tree *byYear, tree *byBrand){
  int x = 0;
  printf("\n0 - Sort by \"Placa\"\n"
         "1 - Sort by Year\n"
         "2 - Sort by \"Marca\"\n\n\n");

  scanf("%i", &x);

  switch (x) {
    case 0: {
      printf("Listando por Placa:\n");
      callback(mainList, printVeiculo, nullptr);
      break;
    }
    case 1: {
      printf("Listando por Ano:\n");
      emordem(byYear, nullptr, printTree);
      break;
    }
    case 2: {
      printf("Listando por Marca:\n");
      emordem(byBrand, nullptr, printTree);
      break;
    }
  default:
    break ;
  }

  printf("\n________________-\n");
}

void *searchBy(tree *byLicensePlate){
  char *query = malloc(sizeof(char)*100);

  printf("Placa: ");
  veiculo queryWrapper;
  scanf("%s", query);
  lista wrapper;
  wrapper.data = &queryWrapper;
  queryWrapper.placa = query;
  printf("%s", query);
  tree *no_used = nullptr;
  tree *result = search(byLicensePlate, &wrapper, placa_Ordem, &no_used);

  free(query);
  if (result) {
    printTree(result, nullptr);
    return result;
  }

  printf("Placa not found\n");
  return result;
}

void deleteVehicle(void *list, tree **byYear,
                   tree **byLicensePlate, tree **byBrand){

  printf("Deletando nas árvores...\n");
  *byBrand = emordemDelete(*byBrand, list);
  *byLicensePlate = emordemDelete(*byLicensePlate, list);
  *byYear = emordemDelete(*byYear, list);
}

void valgrindOk(lista **mainList, tree **byYear,
                 tree **byLicensePlate, tree **byBrand){
  while (*mainList){
    deleteDataVehicle(((lista *)*mainList)->data);
    *mainList = callbackDelete(*mainList, (lista *)(*mainList));
  }

  destroy(*byLicensePlate);
  destroy(*byYear);
  destroy(*byBrand);
}

int main() {
    printf("Hello, World!\n");

    lista *mainList = nullptr;
    tree  *byYear = nullptr;
    tree  *byLicensePlate = nullptr;
    tree  *byBrand = nullptr;

    int x;

    do {
      printf("0 -- Exit\n"
             "1 -- Add\n"
             "2 -- List\n"
             "3 -- Search by \"Placa\"\n\n\n"
             );
      scanf("%i", &x);


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
          void * res = searchBy(byLicensePlate);
          if(res){
            printf("Deletar:\n"
                   "0 -- Não\n"
                   "1 -- Sim\n");

            scanf("%i", &x);
            if(x){
              deleteDataVehicle(((lista *)((tree *)res)->data)->data);
              mainList = callbackDelete(mainList, (lista *)((tree *)res)->data);
              deleteVehicle(((tree *)res)->data, &byYear, &byLicensePlate, &byBrand);
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

    valgrindOk(&mainList, &byYear, &byLicensePlate, &byBrand);
    return 0;
}
