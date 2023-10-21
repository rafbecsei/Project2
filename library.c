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
    printf("\n- Novo Cliente\n");
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

int apagarusuario(ListaDeUsuarios *lu){
    printf("\n- Apagar Cliente\n");
    long cpf;
    printf("Insira seu CPF: ");
    scanf("%ld", &cpf);
    int cpfusuario = procuracpf(*lu, cpf);
    if (cpfusuario == -1){
        printf("Seu CPF nao consta em nosso sistema\n");
        return 0;
    }
    int confirmacao;
    printf("Confirme para prosseguir com a acao (Sim( 0 ) / Nao ( 1 )): ");
    scanf("%d", &confirmacao);
    if(confirmacao == 0){
      for(int i = cpfusuario; i < lu->qtd ; i++){
      lu->u[i] = lu->u[i + 1];
      }
    lu->qtd--;
    } else {
      printf("Cliente nao deletado");
      return 0;
    }
    printf("Cliente deletado com sucesso");
    return 0;
}

int listarusuarios(ListaDeUsuarios lu) {
    for(int i = 0; i < lu.qtd ; i++){
        printf("\n----- CLIENTE -----");
        printf("\nNome: %s", lu.u[i].nome);
        printf("\nCPF: %ld", lu.u[i].cpf);
        if(lu.u[i].tipoconta == 0){
          printf("\nTipo de Conta: Comum");
        }
        else if(lu.u[i].tipoconta == 1){
          printf("\nTipo de Conta: Plus");
        }
        printf("\nValor: R$ %.2f\n", lu.u[i].valor);
        printf("-------------------\n");
    }
}

int debito(ListaDeUsuarios *lu){
    printf("\n- Debito\n");
    long cpf;
    printf("Insira seu CPF: ");
    scanf("%ld", &cpf);
    int cpfusuario = procuracpf(*lu, cpf);
    if (cpfusuario == -1){
        printf("Seu CPF nao consta em nosso sistema\n");
        return 0;
    }
    int senha;
    printf("Insira sua senha: ");
    scanf("%d", &senha);

    if (lu->u[cpfusuario].senha == senha) {
        float valor;
        printf("Insira o valor: R$ ");
        scanf("%f", &valor);
        if(lu->u[cpfusuario].tipoconta == 0 && lu->u[cpfusuario].valor > -1000){
            float taxacomum = valor * 1.05;
            lu->u[cpfusuario].valor = lu->u[cpfusuario].valor - taxacomum; 
            printf("\nR$ %.2f foram debitados de sua conta (inclui taxa de serviço)\n", taxacomum);
        }
        else if(lu->u[cpfusuario].tipoconta == 1 && lu->u[cpfusuario].valor > -5000){
            float taxaplus = valor * 1.03;
            lu->u[cpfusuario].valor = lu->u[cpfusuario].valor - taxaplus;
            printf("\nR$ %.2f foram debitados de sua conta (inclui taxa de serviço)\n", taxaplus);
        }
        else{
          printf("\nSaldo insuficiente, excedendo o limite de seu tipo de conta \n");
        }
    }
    else{
        printf("Senha incorreta");
        return 0;
    }

}

int deposito(ListaDeUsuarios *lu){
  printf("\n- Deposito\n");
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  int cpfusuario = procuracpf(*lu, cpf);
  if (cpfusuario == -1){
      printf("Seu CPF nao consta em nosso sistema\n");
      return 0;
  }  
  else{
    float valor;
    printf("Insira o valor: R$ ");
    scanf("%f", &valor);
    lu->u[cpfusuario].valor = lu->u[cpfusuario].valor + valor;
    printf("\nR$ %.2f foram depositados na sua conta\n", valor);
  }
}

void printMenu(){
  printf("\n------- Menu -------\n1. Novo Cliente\n2. Apaga Cliente\n3. Listar Clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência\n0. Sair\n--------------------\n");
}