#include "library.h"
#include "string.h"
#include <stdio.h>

int main() {
  int cod;
  char arquivo[] = "ListaDeUsuarios";
  // criando uma variavel do tipo lista de usuarios
  ListaDeUsuarios lu;
  // carrega a lista do arquivo
  cod = carregarLista(&lu, arquivo);
  // caso o arquivo nao exista inicia a criação de um
  if (cod == 1)
    lu.qtd = 0;
  // cria uma variavel das opções
  int opcao;
  // loop principal do programa
  do {
    // função que printa o menu
    printMenu();
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    // Switch case para escolher a opção do menu
    switch (opcao) {
    // encerrar o programa
    case 0:
      break;
    // criar cliente
    case 1:
      novousuario(&lu);
      break;
    // apagar o cliente
    case 2:
      apagarusuario(&lu);
      break;
    // listar os clientes
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
    // opção inválida
    default:
      printf("Opção não existe\n");
    }

  } while (opcao != 0);
  // Salva a lista de usuários no arquivo binario
  cod = salvarLista(lu, arquivo);
  // mensagem de erro caso a lista não seja salva
  if (cod != 0) {
    printf("Erro ao salvar clientes");
  }
}