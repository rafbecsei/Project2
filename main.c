#include "library.h"
#include "string.h"
#include <stdio.h>

int main() {
  int cod;
  char arquivo[] = "ListaDeUsuarios";
  // criando uma variavel do tipo lista de usuarios
  ListaDeUsuarios lu;
  // chamando a função que carrega o arquivo com a lista de clientes 
  cod = carregarLista(&lu, arquivo);
  // caso o arquivo nao exista é criado um
  if (cod == 1)
    lu.qtd = 0;
  //variavel das opções do menu
  int opcao;
  // loop principal do programa
  do {
    // função que printa o menu
    printMenu();
    printf("Escolha uma opção: ");
    //recebe e armazena a opção escolhida
    scanf("%d", &opcao);

    //opções do menu e respectivos números
    switch (opcao) {
    // encerrar o programa
    case 0:
      break;
    // criar cliente
    case 1:
      novousuario(&lu);
      break;
    // apagar cliente
    case 2:
      apagarusuario(&lu);
      break;
    // listar clientes
    case 3:
      listarusuarios(lu);
      break;
    // opção de debito
    case 4:
      debito(&lu);
      break;
    // opção de depósito
    case 5:
      deposito(&lu);
      break;
    // opção de extrato
    case 6:
      extrato(&lu);
      break;
    // opção de transferência
    case 7:
      transferencia(&lu);
      break;
    // caso um número além de 0-7 seja precionado
    default:
      printf("Opção não existe\n");
    }
  } while (opcao != 0);
  // chamando a função salvar para salvar a lista com clientes
  cod = salvarLista(lu, arquivo);
  // mensagem de erro caso a lista não seja salva
  if (cod != 0) {
    printf("Erro ao salvar clientes");
  }
}