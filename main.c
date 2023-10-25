#include "library.h"
#include <stdio.h>
#include "string.h"


int main(){
      ListaDeUsuarios lu;

    int opcao;
    do{
        printMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 0:

                break;
            case 1:
                novousuario(&lu);
                break;
            case 2:
                apagarusuario(&lu);
                break;
            case 3:
                listarusuarios(lu);
                break;
            case 4:
                debito(&lu);
                break;
            case 5:
                deposito(&lu);
                break;
            case 6:
                //extrato();
                break;
            case 7:
                transferencia(&lu);
                break;
            default:
                printf("Opcao nao existe\n");
        }

    } while(opcao != 0);
}