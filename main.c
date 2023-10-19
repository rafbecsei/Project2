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
                apagarusuario(&lu)
                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            case 7:

                break;
            default:
                printf("Opcao nao existe\n");
        }

    } while(opcao != 0);
}