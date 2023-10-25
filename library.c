#include "library.h"
#include "string.h"
#include <stdio.h>

int buscadados(ListaDeUsuarios lu, long cpf) {
  int posicao = 0;
  for (posicao; posicao < 3; posicao++) {
    if (lu.u[posicao].cpf == cpf) {
      return posicao;
    }
  }
  return -1;
}

int novousuario(ListaDeUsuarios *lu) {
  printf("\n- Novo Cliente\n");
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
  printf("Nome: ");
  fgets(lu->u[lu->qtd].nome, 30, stdin);
  lu->u[lu->qtd].nome[strcspn(lu->u[lu->qtd].nome, "\n")] = '\0';
  long cpf;
  printf("CPF: ");
  scanf("%ld", &cpf);
  int dadosusuario = buscadados(*lu, cpf);
  if (dadosusuario == -1) {
    lu->u[lu->qtd].cpf = cpf;
    printf("Tipo de Conta(Comun(0)/Plus(1)): ");
  }
  scanf("%d", &lu->u[lu->qtd].tipoconta);
  if (lu->u[lu->qtd].tipoconta != 0 && lu->u[lu->qtd].tipoconta != 1) {
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

int apagarusuario(ListaDeUsuarios *lu) {
  printf("\n- Apagar Cliente\n");
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  int dadosusuario = buscadados(*lu, cpf);
  if (dadosusuario == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  int confirmacao;
  printf("Confirme para prosseguir com a acao (Sim( 0 ) / Nao ( 1 )): ");
  scanf("%d", &confirmacao);
  if (confirmacao == 0) {
    for (int i = dadosusuario; i < lu->qtd; i++) {
      lu->u[i] = lu->u[i + 1];
    }
    lu->qtd--;
  } else {
    printf("Cliente não deletado");
    return 0;
  }
  printf("Cliente deletado com sucesso");
  return 0;
}

int listarusuarios(ListaDeUsuarios lu) {
  for (int i = 0; i < lu.qtd; i++) {
    printf("\n----- CLIENTE -----");
    printf("\nNome: %s", lu.u[i].nome);
    printf("\nCPF: %ld", lu.u[i].cpf);
    if (lu.u[i].tipoconta == 0) {
      printf("\nTipo de Conta: Comum");
    } else if (lu.u[i].tipoconta == 1) {
      printf("\nTipo de Conta: Plus");
    }
    printf("\nValor: R$ %.2f\n", lu.u[i].valor);
    printf("-------------------\n");
  }
}

int debito(ListaDeUsuarios *lu) {
  printf("\n- Debito\n");
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  int dadosusuario = buscadados(*lu, cpf);
  if (dadosusuario == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  int senha;
  printf("Insira seu PIN: ");
  scanf("%d", &senha);

  if (lu->u[dadosusuario].senha == senha) {
    float valor;
    printf("Insira o valor: R$ ");
    scanf("%f", &valor);
    if (lu->u[dadosusuario].tipoconta == 0) {
      float taxacomum = valor * 1.05;
      if (lu->u[dadosusuario].valor - taxacomum < -1000) {
        printf("\nNao sera possivel realizar a transacao, valor final excede o "
               "limite do tipo da conta\n");
        return 0;
      } else {
        lu->u[dadosusuario].valor = lu->u[dadosusuario].valor - taxacomum;
        sprintf(lu->u[dadosusuario].e[lu->u[dadosusuario].qtd].historico,
                "Débito | Valor: R$ %.2f | Taxa Comum: 5% | Total: R$ %.2f\n", valor,
                taxacomum);
        lu->u[dadosusuario].qtd = lu->u[dadosusuario].qtd + 1;
        printf(
            "\nR$ %.2f foram debitados de sua conta (inclui taxa de serviço)\n",
            taxacomum);
      }
    } else if (lu->u[dadosusuario].tipoconta == 1) {
      float taxaplus = valor * 1.03;
      if (lu->u[dadosusuario].valor - taxaplus < -5000) {
        printf("\nNao sera possivel realizar a transacao, valor final excede "
               "limite do tipo da conta\n");
        return 0;

      } else {
        lu->u[dadosusuario].valor = lu->u[dadosusuario].valor - taxaplus;
        sprintf(lu->u[dadosusuario].e[lu->u[dadosusuario].qtd].historico,
                "Débito | Valor: R$ %.2f | Taxa Comum: 3% | Total: R$ %.2f\n", valor,
                taxaplus);
        lu->u[dadosusuario].qtd = lu->u[dadosusuario].qtd + 1;
        printf(
            "\nR$ %.2f foram debitados de sua conta (inclui taxa de serviço)\n",
            taxaplus);
      }
    } else {
      printf(
          "\nSaldo insuficiente, excedendo o limite de seu tipo de conta \n");
    }
  } else {
    printf("PIN incorreto\n ");
    return 0;
  }
  return 0;
}

int deposito(ListaDeUsuarios *lu) {
  printf("\n- Deposito\n");
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  int dadosusuario = buscadados(*lu, cpf);
  if (dadosusuario == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  } else {
    float valor;
    printf("Insira o valor: R$ ");
    scanf("%f", &valor);
    lu->u[dadosusuario].valor = lu->u[dadosusuario].valor + valor;
    sprintf(lu->u[dadosusuario].e[lu->u[dadosusuario].qtd].historico,
            "Deposito | Valor: R$ %.2f | Total: R$ %.2f\n", valor, valor);
    lu->u[dadosusuario].qtd = lu->u[dadosusuario].qtd + 1;
    printf("\nR$ %.2f foram depositados em sua conta\n", valor);
  }
}

int transferencia(ListaDeUsuarios *lu) {
  printf("\n- Transferencia\n");
  long cpfremetente;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpfremetente);
  int cpfremet = buscadados(*lu, cpfremetente);
  if (cpfremet == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  int senha;
  printf("Insira seu PIN: ");
  scanf("%d", &senha);
  if (lu->u[cpfremet].senha == senha) {
    long cpfdestinatario;
    printf("Insira o CPF do destinatário: ");
    scanf("%ld", &cpfdestinatario);
    int cpfdest = buscadados(*lu, cpfdestinatario);
    if (cpfdest == -1) {
      printf("\nEsse CPF não consta em nosso sistema\n");
      return 0;
    }
    float valor;
    printf("Insira o valor: R$ ");
    scanf("%f", &valor);
    if (lu->u[cpfremet].tipoconta == 0) {
      float taxacomum = valor * 1.05;
      if (lu->u[cpfremet].valor - taxacomum <= -1000) {
        printf("\nNao sera possivel realizar a transacao, valor final excede o "
               "limite do tipo da conta\n");
        return 0;
      } else {
        lu->u[cpfremet].valor = lu->u[cpfremet].valor - taxacomum;
        lu->u[cpfdest].valor = lu->u[cpfdest].valor + valor;
        sprintf(lu->u[cpfremet].e[lu->u[cpfremet].qtd].historico,
                "Transferencia para %s | Valor: R$ %.2f | Taxa Comum: 3% | Total: "
                "R$ %.2f\n",
                lu->u[cpfdest].nome, valor, taxacomum);
        lu->u[cpfremet].qtd = lu->u[cpfremet].qtd + 1;
        sprintf(lu->u[cpfdest].e[lu->u[cpfdest].qtd].historico,
                "Transferencia de %s | Valor: R$ %.2f | Total: R$ %.2f\n",
                lu->u[cpfremet].nome, valor, valor);
        lu->u[cpfdest].qtd = lu->u[cpfdest].qtd + 1;
        printf("\nR$ %.2f foram transferidos de sua conta para %s (inclui taxa "
               "de serviço)\n",
               taxacomum, lu->u[cpfdest].nome);
      }
    } else if (lu->u[cpfremet].tipoconta == 1) {
      float taxaplus = valor * 1.03;
      if (lu->u[cpfremet].valor - taxaplus <= -5000) {
        printf("\nNao sera possivel realizar a transacao, valor final excede o "
               "limite do tipo da conta\n");
        return 0;
      } else {
        lu->u[cpfremet].valor = lu->u[cpfremet].valor - taxaplus;
        lu->u[cpfdest].valor = lu->u[cpfdest].valor + valor;
        sprintf(lu->u[cpfremet].e[lu->u[cpfremet].qtd].historico,
                "Transferência para %s | Valor: R$ %.2f | Taxa Comum: 5% | Total: "
                "R$ %.2f\n",
                lu->u[cpfdest].nome, valor, taxaplus);
        lu->u[cpfremet].qtd = lu->u[cpfremet].qtd + 1;
        sprintf(lu->u[cpfdest].e[lu->u[cpfdest].qtd].historico,
                "Transferência de %s | Valor: R$ %.2f | Total: R$ %.2f\n",
                lu->u[cpfremet].nome, valor, valor);
        lu->u[cpfdest].qtd = lu->u[cpfdest].qtd + 1;
        printf("\nR$ %.2f foram transferidos de sua conta para %s (inclui taxa "
               "de serviço)\n",
               taxaplus, lu->u[cpfdest].nome);
      }
    } else {
      printf(
          "\nSaldo insuficiente, excedendo o limite de seu tipo de conta \n");
    }
  } else {
    printf("PIN incorreto\n ");
    return 0;
  }
  return 0;
}

int extrato(ListaDeUsuarios *lu) {
  printf("\n- Extrato\n");
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  int dadosusuario = buscadados(*lu, cpf);
  if (dadosusuario == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  int senha;
  printf("Insira seu PIN: ");
  scanf("%d", &senha);
  if (lu->u[dadosusuario].senha == senha) {
    for(int i = 0; i <= lu->u[dadosusuario].qtd; i++) {
      printf("\n%s", lu->u[dadosusuario].e[i].historico);
    }
  } else {
    printf("PIN incorreto\n ");
    return 0;
  }
  return 0;
}

void printMenu() {
  printf("\n------- Menu -------\n1. Novo Cliente\n2. Apaga Cliente\n3. Listar "
         "Clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência\n0. "
         "Sair\n--------------------\n");
}

