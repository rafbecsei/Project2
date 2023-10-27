#include "library.h"
#include "string.h"
#include <stdio.h>

int main() {
  int cod;
  char arquivo[] = "ListaDeUsuarios";
  ListaDeUsuarios lu;
  cod = carregarLista(&lu, arquivo);
  if (cod == 1)
    lu.qtd = 0;

  int opcao;
  do {
    printMenu();
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
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
      extrato(&lu);
      break;
    case 7:
      transferencia(&lu);
      break;
    default:
      printf("Opção não existe\n");
    }

  } while (opcao != 0);
  cod = salvarLista(lu, arquivo);
  if (cod != 0) {
    printf("Erro ao salvar clientes");
  }
}