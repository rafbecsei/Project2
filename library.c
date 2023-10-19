#include "library.h"
#include <stdio.h>
#include "string.h"

int procuracpf(ListaDeUsuarios lu, long cpf){
    int posicao = 0;
    for(posicao; posicao < 3; posicao++){
        if(lu.u[posicao].cpf == cpf){
            return posicao;
        }
    }
    return -1;    
}

int novousuario(ListaDeUsuarios *lu) {
    printf("\nNovo Cliente\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    printf("Nome: ");
    fgets(lu->u[lu->qtd].nome, 30, stdin);
    lu->u[lu->qtd].nome[strcspn(lu->u[lu->qtd].nome, "\n")] = '\0';
    long cpf;
    printf("CPF: ");
    scanf("%ld", &cpf);
    int cpfusuario = procuracpf(*lu, cpf);
    if (cpfusuario == -1){
        lu->u[lu->qtd].cpf = cpf;
        printf("Tipo de Conta(Comun(0)/Plus(1)): ");
    }
    scanf("%d", &lu->u[lu->qtd].tipoconta);
    if(lu->u[lu->qtd].tipoconta != 0 && lu->u[lu->qtd].tipoconta != 1){
        printf("\nDigite um tipo de conta válido\n");
        return 0;
    }
    printf("Valor Inicial: ");
    scanf("%f", &lu->u[lu->qtd].valor);
    printf("PIN: ");
    scanf("%d", &lu->u[lu->qtd].senha);
    lu->qtd = lu->qtd + 1;
    return 0;
}

// int apagarusuario(ListaDeUsuarios *lu){
//     printf("\nApagar Usuario\n");
//     if(lu->qtd == 0){
//         printf("Seu CPF nao consta em nosso sistema, ");
//     }
//     int procuracpf(ListaDeUsuarios lu, long cpf){
//     int posicao = 0;
//     for(posicao; posicao < 3; posicao++){
//         if(lu.u[posicao].cpf == cpf){
//             return posicao;
//         }
//     }
//     return -1;    
//     }
// }

int apagarusuario(ListaDeUsuarios *lu){
    printf("\nApagar Cliente\n");
    printf("Insira seu CPF: ");
    scanf("%ld", &cpf);
    int cpfusuario = procuracpf(*lu, cpf);
    if (cpfusuario == -1){
        printf("Seu CPF nao consta em nosso sistema");
    }
    int confirmacao;
    else if(lu->u[lu->qtd].cpf == cpf){
        printf("Confirme para prosseguir com a acao (Sim( 0 ) / Nao ( 1 )): ");
        scanf("%c", &confirmacao);
        if(confirmacao == 0){
            printf("Cliente deletado com sucesso")
            for(int i = lu->u[lu->qtd].cpf; lu->qtd < 0 ; i++){
            lu->u[i] = lu->u[i + 1];
            }
            lu->qtd--;
        } else {
            printf("Cliente nao deletado")
        }
    }
    return 0;
}

// int deletarLembrete(ListaDeLembretes *ll){
//     printf("\nDeletar Lembrete\n");
//     if(ll->qtd == 0){
//         printf("Nao ha lembretes, crie um");
//     }
//     int numerodolembrete;
//     printf("\nNumero do lembrete: ");
//     scanf("%d", &numerodolembrete);
//     if(numerodolembrete < 1 || numerodolembrete > ll->qtd){
//         printf("Esse lembrete nao existe");
//     }
//     else{
//         for(int i = numerodolembrete; i < ll->qtd; i++){
//             ll->l[i] = ll->l[i + 1];
//         }
//         ll->qtd--;
//         printf("\nLembrete %d deletado", numerodolembrete);
//     }
//     return 0;
// }
    

//   printf("\nCLIENTE");
//   printf("\nNome. %s", lu->u[lu->qtd].nome);
//   printf("\nCPF. %ld", lu->u[lu->qtd].cpf);
//   printf("\nTC. %d", lu->u[lu->qtd].tipoconta);
//   printf("\nValor. %.2f", lu->u[lu->qtd].valor);
//   printf("\nSenha. %d\n", lu->u[lu->qtd].senha);
  


void printMenu(){
    printf("\n======= Menu =======\n1. Novo Cliente\n2. Apaga Cliente\n3. Listar Clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência\n0. Sair\n====================\n");
}