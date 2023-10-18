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
    printf("\nNovo Usuario\n");
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
    

  printf("\nCLIENTE");
  printf("\nNome. %s", lu->u[lu->qtd].nome);
  printf("\nCPF. %ld", lu->u[lu->qtd].cpf);
  printf("\nTC. %d", lu->u[lu->qtd].tipoconta);
  printf("\nValor. %.2f", lu->u[lu->qtd].valor);
  printf("\nSenha. %d\n", lu->u[lu->qtd].senha);
  lu->qtd = lu->qtd + 1;
  return 0;
}


void printMenu(){
    printf("\n======= Menu =======\n1. Novo Cliente\n2. Apaga Cliente\n3. Listar Clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência\n0. Sair\n====================\n");
}