#include <stdio.h>
#include "library.h"

int main(){
    int opcao;
    do{
        printMenu();
        printf("Escolha uma opcao: ");
        scanf("%d" &opcao);

        switch(opcao){
            case 0:
                break;
            case 1:

                break;
            case 2:

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