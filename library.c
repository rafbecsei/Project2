#include "library.h"
#include "string.h"
#include <stdio.h>

// FUNÇÃO BUSCAR DADOS
int buscadados(ListaDeUsuarios lu, long cpf) {
  // define a posição inicial como 0
  int posicao = 0;
  // procura o cpf dentro da lista enquanto a posição for menor que 1000
  for (posicao; posicao < 1000; posicao++) {
    // se o cpf for encontrado, retorna a posição
    if (lu.u[posicao].cpf == cpf) {
      return posicao;
    }
  }
  // se não for encontrado retorna -1
  return -1;
}

// FUNÇÃO CRIAR CLIENTE
int novousuario(ListaDeUsuarios *lu) {
  printf("\n- Novo Cliente\n");
  // limpa buffer
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
  printf("Nome: ");
  // recebe o nome do cliente e o adiciona a lista
  fgets(lu->u[lu->qtd].nome, 30, stdin);
  lu->u[lu->qtd].nome[strcspn(lu->u[lu->qtd].nome, "\n")] = '\0';
  // variável do CPF
  long cpf;
  printf("CPF: ");
  scanf("%ld", &cpf);
  // cria uma variavel para verificar se o CPF já existe
  int dadosusuario = buscadados(*lu, cpf);
  // verifica se o usuário não existe
  if (dadosusuario == -1) {
    // registra o CPF na struct
    lu->u[lu->qtd].cpf = cpf;
    printf("Tipo de Conta(Comun(0)/Plus(1)): ");
  }
  // recebe o tipo de conta
  scanf("%d", &lu->u[lu->qtd].tipoconta);
  // verifica se o tipo de conta é valido(0 ou 1) ou não
  if (lu->u[lu->qtd].tipoconta != 0 && lu->u[lu->qtd].tipoconta != 1) {
    printf("\nDigite um tipo de conta válido\n");
    return 0;
  }
  printf("Valor Inicial: ");
  // registra o valor inicial a conta do cliente
  scanf("%f", &lu->u[lu->qtd].valor);
  printf("PIN: ");
  // registra o PIN do cliente
  scanf("%d", &lu->u[lu->qtd].senha);
  // adiciona um a quantidade da lista de usuario
  lu->qtd = lu->qtd + 1;
  return 0;
}

// FUNÇÃO APAGAR CLIENTE
int apagarusuario(ListaDeUsuarios *lu) {
  printf("\n- Apagar Cliente\n");
  // variável do CPF
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  int dadosusuario = buscadados(*lu, cpf);
  // Verifica se o usuário existe ou não
  if (dadosusuario == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  // solicita a confirmação do usuário
  int confirmacao;
  printf("\nConfirme para prosseguir com a ação (Sim( 0 ) / Nao ( 1 )): \n");
  scanf("%d", &confirmacao);
  // caso tenha a confirmação, cliente é deletado
  if (confirmacao == 0) {
    for (int i = dadosusuario; i < lu->qtd - 1; i++) {
      // atribui o numero do cliente seguinte ao cliente apagado
      lu->u[i] = lu->u[i + 1];
    }
    // diminui a quantidade de clientes
    lu->qtd--;
    // caso não tenha a confirmação não deleta o cliente
  } else {
    printf("\nCliente não deletado\n");
    return 0;
  }
  // print confirmando que o cliente foi deletado
  printf("\nCliente deletado com sucesso\n");
  return 0;
}

// FUNÇÃO LISTAR CLIENTES
int listarusuarios(ListaDeUsuarios lu) {
  // percorre a lista com os usuários e printa os existentes
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

// FUNÇÃO DÉBITO
int debito(ListaDeUsuarios *lu) {
  printf("\n- Débito\n");
  // variavel CPF
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  int dadosusuario = buscadados(*lu, cpf);
  // verifica se o CPF existe ou não
  if (dadosusuario == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  // variável senha
  int senha;
  printf("Insira seu PIN: ");
  scanf("%d", &senha);
  // verifica se a senha é igual a senha do usuario
  if (lu->u[dadosusuario].senha == senha) {
    // variável valor a ser debitado
    float valor;
    printf("Insira o valor: R$ ");
    scanf("%f", &valor);
    // verificação do tipo de conta comum
    if (lu->u[dadosusuario].tipoconta == 0) {
      // taxa a ser aplicada a conta de tipo comum
      float taxacomum = valor * 1.05;
      // verifica se o valor com taxa é menor que o limite negativo
      if (lu->u[dadosusuario].valor - taxacomum < -1000) {
        printf("\nNão será possível realizar a transação, valor final excede o "
               "limite do tipo da conta\n");
        return 0;
        // caso a conta seja comum e o valor final esteja acima do limite
      } else {
        // atualiza o valor da conta do cliente após o débito
        lu->u[dadosusuario].valor = lu->u[dadosusuario].valor - taxacomum;
        // armazena o historico da transação
        sprintf(lu->u[dadosusuario].e[lu->u[dadosusuario].qtd].historico,
                "Débito | Valor: R$ %.2f | Taxa Comum | Total: R$ %.2f\n",
                valor, taxacomum);
        // atualiza a quantidade do histórico
        lu->u[dadosusuario].qtd = lu->u[dadosusuario].qtd + 1;
        // confirma a transação
        printf(
            "\nR$ %.2f foram debitados de sua conta (inclui taxa de serviço)\n",
            taxacomum);
      }
      // verificação do tipo de conta plus
    } else if (lu->u[dadosusuario].tipoconta == 1) {
      // taxa a ser aplicada a conta de tipo plus
      float taxaplus = valor * 1.03;
      // verifica se o valor com taxa é menor que o limite negativo
      if (lu->u[dadosusuario].valor - taxaplus < -5000) {
        printf("\nNão será possível realizar a transação, valor final excede "
               "limite do tipo da conta\n");
        return 0;

      } else {
        // atualiza o valor da conta do cliente apos o debito
        lu->u[dadosusuario].valor = lu->u[dadosusuario].valor - taxaplus;
        // armazena o historico da transação
        sprintf(lu->u[dadosusuario].e[lu->u[dadosusuario].qtd].historico,
                "Débito | Valor: R$ %.2f | Taxa Plus | Total: R$ %.2f\n", valor,
                taxaplus);
        lu->u[dadosusuario].qtd = lu->u[dadosusuario].qtd + 1;
        // atualiza a quantidade do histórico
        printf(
            "\nR$ %.2f foram debitados de sua conta (inclui taxa de serviço)\n",
            taxaplus);
      }
      // print caso o cliente não tenha saldo suficiente
    } else {
      printf(
          "\nSaldo insuficiente, excedendo o limite de seu tipo de conta \n");
    }
    // caso o PIN esteja incorreto
  } else {
    printf("\nPIN incorreto\n ");
    return 0;
  }
}

// FUNÇÃO DEPÓSITO
int deposito(ListaDeUsuarios *lu) {
  printf("\n- Depósito\n");
  // variavel CPF
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  int dadosusuario = buscadados(*lu, cpf);
  // verifica se o CPF existe ou não
  if (dadosusuario == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  } else {
    // variavel valor
    float valor;
    printf("Insira o valor: R$ ");
    scanf("%f", &valor);
    // atualiza o valor da conta
    lu->u[dadosusuario].valor = lu->u[dadosusuario].valor + valor;
    // adiciona a ação ao histórico
    sprintf(lu->u[dadosusuario].e[lu->u[dadosusuario].qtd].historico,
            "Depósito | Valor: R$ %.2f | Total: R$ %.2f\n", valor, valor);
    // atualiza a quantidade do histórico
    lu->u[dadosusuario].qtd = lu->u[dadosusuario].qtd + 1;
    // confirmação da transação
    printf("\nR$ %.2f foram depositados em sua conta\n", valor);
  }
}

// FUNÇÃO TRANFERÊNCIA
int transferencia(ListaDeUsuarios *lu) {
  printf("\n- Transferência\n");
  // variavel CPF remetente
  long cpfremetente;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpfremetente);
  // busca o cpf do remetente
  int cpfremet = buscadados(*lu, cpfremetente);
  // caso o CPF do remetente não exista
  if (cpfremet == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  // variável senha do remetente
  int senha;
  printf("Insira seu PIN: ");
  scanf("%d", &senha);
  // verifica se a senha é igual a senha do cliente
  if (lu->u[cpfremet].senha == senha) {
    // variável do CPF do destinatário
    long cpfdestinatario;
    printf("Insira o CPF do destinatário: ");
    scanf("%ld", &cpfdestinatario);
    // verifica se o CPF do destinatário existe
    int cpfdest = buscadados(*lu, cpfdestinatario);
    // caso o CPF não exista
    if (cpfdest == -1) {
      printf("\nEsse CPF não consta em nosso sistema\n");
      return 0;
    }
    // variável valor
    float valor;
    printf("Insira o valor: R$ ");
    scanf("%f", &valor);
    // verifica a conta comum e aplica as devidas taxas
    if (lu->u[cpfremet].tipoconta == 0) {
      float taxacomum = valor * 1.05;
      // verifica se é possivel realizar a transação pela quantia de dinheiro
      if (lu->u[cpfremet].valor - taxacomum <= -1000) {
        printf("\nNão será possível realizar a transação, valor final excede o "
               "limite do tipo da conta\n");
        return 0;
        // atualiza o valor da conta do remetente e do destinatário
      } else {
        lu->u[cpfremet].valor = lu->u[cpfremet].valor - taxacomum;
        lu->u[cpfdest].valor = lu->u[cpfdest].valor + valor;
        // adiciona a ação ao histórico do remetente
        sprintf(lu->u[cpfremet].e[lu->u[cpfremet].qtd].historico,
                "Transferência para %s | Valor: R$ %.2f | Taxa Comum | Total: "
                "R$ %.2f\n",
                lu->u[cpfdest].nome, valor, taxacomum);
        // atualiza a quantidade do histórico do  remetente
        lu->u[cpfremet].qtd = lu->u[cpfremet].qtd + 1;
        // adiciona a ação ao histórico do destinatário
        sprintf(lu->u[cpfdest].e[lu->u[cpfdest].qtd].historico,
                "Transferência de %s | Valor: R$ %.2f | Total: R$ %.2f\n",
                lu->u[cpfremet].nome, valor, valor);
        // atualiza a quantidade do histórico do destinatário
        lu->u[cpfdest].qtd = lu->u[cpfdest].qtd + 1;
        printf("\nR$ %.2f foram transferidos de sua conta para %s (inclui taxa "
               "de serviço)\n",
               taxacomum, lu->u[cpfdest].nome);
      }
      // verifica a conta plus e aplica as devidas taxas
    } else if (lu->u[cpfremet].tipoconta == 1) {
      float taxaplus = valor * 1.03;
      // verifica se é possivel realizar a transação pela quantia de dinheiro
      if (lu->u[cpfremet].valor - taxaplus <= -5000) {
        printf("\nNão será possível realizar a transação, valor final excede o "
               "limite do tipo da conta\n");
        return 0;
        // atualiza o valor da conta do remetente e do destinatário

      } else {
        lu->u[cpfremet].valor = lu->u[cpfremet].valor - taxaplus;
        lu->u[cpfdest].valor = lu->u[cpfdest].valor + valor;
        // adiciona a ação ao histórico do remetente
        sprintf(lu->u[cpfremet].e[lu->u[cpfremet].qtd].historico,
                "Transferência para %s | Valor: R$ %.2f | Taxa Plus | Total: "
                "R$ %.2f\n",
                lu->u[cpfdest].nome, valor, taxaplus);
        // atualiza a quantidade do histórico do  remetente
        lu->u[cpfremet].qtd = lu->u[cpfremet].qtd + 1;
        // adiciona a ação ao histórico do destinatário
        sprintf(lu->u[cpfdest].e[lu->u[cpfdest].qtd].historico,
                "Transferência de %s | Valor: R$ %.2f | Total: R$ %.2f\n",
                lu->u[cpfremet].nome, valor, valor);
        // atualiza a quantidade do histórico do destinatário
        lu->u[cpfdest].qtd = lu->u[cpfdest].qtd + 1;
        printf("\nR$ %.2f foram transferidos de sua conta para %s (inclui taxa "
               "de serviço)\n",
               taxaplus, lu->u[cpfdest].nome);
      }
      // aviso caso o saldo seja insuficiente
    } else {
      printf(
          "\nSaldo insuficiente, excedendo o limite de seu tipo de conta \n");
    }
    // aviso caso PIN esteja incorreto
  } else {
    printf("\nPIN incorreto\n ");
    return 0;
  }
}

// FUNÇÃO EXTRATO
int extrato(ListaDeUsuarios *lu) {
  printf("\n- Extrato\n");
  // variável CPF
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  // busca dados e verifica se existem
  int dadosusuario = buscadados(*lu, cpf);
  // caso não exista o CPF
  if (dadosusuario == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  // variável senha
  int senha;
  printf("Insira seu PIN: ");
  scanf("%d", &senha);
  // verifica se a senha está correta
  if (lu->u[dadosusuario].senha == senha) {
    // abre o arquivo
    FILE *f = fopen("extrato.txt", "w");
    // percorre toda a lista do histórico e printa
    for (int i = 0; i <= lu->u[dadosusuario].qtd; i++) {
      fprintf(f, "\n%s", lu->u[dadosusuario].e[i].historico);
    }
    // fecha o arquivo
    fclose(f);
    // caso o PIN esteja incorreto
  } else {
    printf("\nPIN incorreto\n ");
    return 0;
  }
  return 0;
}

// FUNÇÃO PRINT MENU
void printMenu() {
  printf("\n------- Menu -------\n1. Novo Cliente\n2. Apaga Cliente\n3. Listar "
         "Clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência\n0. "
         "Sair\n--------------------\n");
}

// FUNÇÃO QUE SALVA A LISTA DE USUSÁRIO NO ARQUIVO
int salvarLista(ListaDeUsuarios lu, char arquivo[]) {
  // abre arquivo
  FILE *f = fopen(arquivo, "wb");
  // caso não exista arquivo um é criado
  if (f == NULL) {
    return 1;
  }
  // escreve a lista dos usuários no arquivo
  fwrite(&lu, sizeof(ListaDeUsuarios), 1, f);
  // fecha o arquivo
  fclose(f);
  return 0;
}

// FUNÇÃO QUE LÊ A LISTA
int carregarLista(ListaDeUsuarios *lu, char arquivo[]) {
  // abre o arquivo
  FILE *f = fopen(arquivo, "rb");
  // caso não exista arquivo um é criado
  if (f == NULL) {
    return 1;
  }
  // lê o conteudo do arquivo
  fread(lu, sizeof(ListaDeUsuarios), 1, f);
  // fecha o arquivo
  fclose(f);
  return 0;
}