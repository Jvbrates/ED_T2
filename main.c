#include <stdio.h>
#include "lista.h"
int main() {
    printf("Hello, World!\n");


    veiculo v = {
        2022, "Volks", "XXXXXXX"
    };
    veiculo v2= {
        2020, "Volks", "YXXXXXX"
    };
    //lista * main_list = newList(&v);
    lista * main_list = nullptr;

    main_list = addPlaca(main_list, &v);
    //main_list = addPlaca(main_list, &v2);


    callback(main_list, printVeiculo, nullptr);

    printf("_______z\n");

    main_list = callbackDelete(main_list, main_list);

    callback(main_list, printVeiculo, nullptr);


    return 0;
}
