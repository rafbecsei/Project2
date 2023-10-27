#include "library.h"
#include "string.h"
#include <stdio.h>
// função para buscar um dado dentro da lista
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
// função que cria um novo cliente
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
  long cpf;
  printf("CPF: ");
  // recebe o CPF do cliente e o adiciona a lista
  scanf("%ld", &cpf);
  // cria uma variavel para verificar se o CPF já existe
  int dadosusuario = buscadados(*lu, cpf);
  // se o CPF já existir, retorna -1
  if (dadosusuario == -1) {
    // registra o CPF na struct
    lu->u[lu->qtd].cpf = cpf;
    printf("Tipo de Conta(Comun(0)/Plus(1)): ");
    // recebe o tipo de conta
  }
  scanf("%d", &lu->u[lu->qtd].tipoconta);
  // verifica se o tipo de conta é valido(0 ou 1)
  if (lu->u[lu->qtd].tipoconta != 0 && lu->u[lu->qtd].tipoconta != 1) {
    printf("\nDigite um tipo de conta válido\n");
    return 0;
  }
  printf("Valor Inicial: ");
  // recebe o valor inicial
  scanf("%f", &lu->u[lu->qtd].valor);
  printf("PIN: ");
  // recebe o PIN
  scanf("%d", &lu->u[lu->qtd].senha);
  lu->qtd = lu->qtd + 1;
  // adiciona um a mais na quantidade de usuarios
  return 0;
}
// função para apagar clientes
int apagarusuario(ListaDeUsuarios *lu) {
  printf("\n- Apagar Cliente\n");
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  int dadosusuario = buscadados(*lu, cpf);
  if (dadosusuario == -1) {
    // Verifica se o usuário existe
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  // solicita a confirmação do usuario
  int confirmacao;
  printf("Confirme para prosseguir com a ação (Sim( 0 ) / Nao ( 1 )): ");
  scanf("%d", &confirmacao);
  // caso tenha a confirmação deleta o cliente
  if (confirmacao == 0) {
    for (int i = dadosusuario; i < lu->qtd - 1; i++) {
      lu->u[i] = lu->u[i + 1];
    }
    lu->qtd--;
  } else {
    // caso não tenha a confirmação não deleta o cliente
    printf("Cliente não deletado");
    return 0;
  }
  // confirma que o cliente foi deletado
  printf("Cliente deletado com sucesso");
  return 0;
}
// função para listar os clientes
int listarusuarios(ListaDeUsuarios lu) {
  // printa a lista de clientes
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
// função de debito
int debito(ListaDeUsuarios *lu) {
  printf("\n- Débito\n");
  // nova variavel CPF
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  // verifica se o CPF existe
  int dadosusuario = buscadados(*lu, cpf);
  if (dadosusuario == -1) {
    // caso o CPF não exista interrompe a função
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  // nova variavel senha
  int senha;
  printf("Insira seu PIN: ");
  scanf("%d", &senha);
  // verifica se a senha é igual a senha do usuario
  if (lu->u[dadosusuario].senha == senha) {
    float valor;
    printf("Insira o valor: R$ ");
    scanf("%f", &valor);
    // verificação do tipo de conta comum
    if (lu->u[dadosusuario].tipoconta == 0) {
      float taxacomum = valor * 1.05;
      // taxa a ser aplicada a conta de tipo comum
      if (lu->u[dadosusuario].valor - taxacomum < -1000) {
        // verifica se o valor com taxa é menor que o limite negativo
        printf("\nNão será possível realizar a transação, valor final excede o "
               "limite do tipo da conta\n");
        return 0;
      } else {
        // atualiza o valor da conta do cliente apos o debito
        lu->u[dadosusuario].valor = lu->u[dadosusuario].valor - taxacomum;
        // armazena o historico da transação
        sprintf(lu->u[dadosusuario].e[lu->u[dadosusuario].qtd].historico,
                "Débito | Valor: R$ %.2f | Taxa Comum | Total: R$ %.2f\n",
                valor, taxacomum);
        // atualiza a quantidade do historico
        lu->u[dadosusuario].qtd = lu->u[dadosusuario].qtd + 1;
        // confirma a transação
        printf(
            "\nR$ %.2f foram debitados de sua conta (inclui taxa de serviço)\n",
            taxacomum);
      }
      // verificação do tipo de conta plus
    } else if (lu->u[dadosusuario].tipoconta == 1) {
      float taxaplus = valor * 1.03;
      // taxa a ser aplicada a conta de tipo plus
      if (lu->u[dadosusuario].valor - taxaplus < -5000) {
        // verifica se o valor com taxa é menor que o limite negativo
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
        // atualiza a quantidade do historico
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
    printf("PIN incorreto\n ");
    return 0;
  }
}

// função deposito
int deposito(ListaDeUsuarios *lu) {
  printf("\n- Depósito\n");
  // variavel CPF
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  int dadosusuario = buscadados(*lu, cpf);
  // caso não exista interrompe a função
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
    // adiciona a ação ao historico
    sprintf(lu->u[dadosusuario].e[lu->u[dadosusuario].qtd].historico,
            "Depósito | Valor: R$ %.2f | Total: R$ %.2f\n", valor, valor);
    // atualiza a quantidade do historico
    lu->u[dadosusuario].qtd = lu->u[dadosusuario].qtd + 1;
    // confirmação da transação
    printf("\nR$ %.2f foram depositados em sua conta\n", valor);
  }
}

// função transferencia
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
  // variavel senha do remetente
  int senha;
  printf("Insira seu PIN: ");
  scanf("%d", &senha);
  // verifica se a senha é igual a senha do cliente
  if (lu->u[cpfremet].senha == senha) {
    // variavel do CPF do destinatario
    long cpfdestinatario;
    printf("Insira o CPF do destinatário: ");
    scanf("%ld", &cpfdestinatario);
    // verifica se o CPF do destinatario existe
    int cpfdest = buscadados(*lu, cpfdestinatario);
    // caso o CPF nao exista
    if (cpfdest == -1) {
      printf("\nEsse CPF não consta em nosso sistema\n");
      return 0;
    }
    // variavel valor
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
        // atualiza o valor da conta do remetente e do destinatario
      } else {
        lu->u[cpfremet].valor = lu->u[cpfremet].valor - taxacomum;
        lu->u[cpfdest].valor = lu->u[cpfdest].valor + valor;
        // adiciona a ação ao historico do remetente
        sprintf(lu->u[cpfremet].e[lu->u[cpfremet].qtd].historico,
                "Transferência para %s | Valor: R$ %.2f | Taxa Comum | Total: "
                "R$ %.2f\n",
                lu->u[cpfdest].nome, valor, taxacomum);
        // atualiza a quantidade do historico do  remetente
        lu->u[cpfremet].qtd = lu->u[cpfremet].qtd + 1;
        // adiciona a ação ao historico do destinatario
        sprintf(lu->u[cpfdest].e[lu->u[cpfdest].qtd].historico,
                "Transferência de %s | Valor: R$ %.2f | Total: R$ %.2f\n",
                lu->u[cpfremet].nome, valor, valor);
        // atualiza a quantidade do historico do destinatario
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
        // atualiza o valor da conta do remetente e do destinatario

      } else {
        lu->u[cpfremet].valor = lu->u[cpfremet].valor - taxaplus;
        lu->u[cpfdest].valor = lu->u[cpfdest].valor + valor;
        // adiciona a ação ao historico do remetente
        sprintf(lu->u[cpfremet].e[lu->u[cpfremet].qtd].historico,
                "Transferência para %s | Valor: R$ %.2f | Taxa Plus | Total: "
                "R$ %.2f\n",
                lu->u[cpfdest].nome, valor, taxaplus);
        // atualiza a quantidade do historico do  remetente
        lu->u[cpfremet].qtd = lu->u[cpfremet].qtd + 1;
        // adiciona a ação ao historico do destinatario
        sprintf(lu->u[cpfdest].e[lu->u[cpfdest].qtd].historico,
                "Transferência de %s | Valor: R$ %.2f | Total: R$ %.2f\n",
                lu->u[cpfremet].nome, valor, valor);
        // atualiza a quantidade do historico do destinatario
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
    printf("PIN incorreto\n ");
    return 0;
  }
}

// função extrato
int extrato(ListaDeUsuarios *lu) {
  printf("\n- Extrato\n");
  // variavel CPF
  long cpf;
  printf("Insira seu CPF: ");
  scanf("%ld", &cpf);
  // busca dados e verifica se existe
  int dadosusuario = buscadados(*lu, cpf);
  // caso nao exista o CPF
  if (dadosusuario == -1) {
    printf("\nEsse CPF não consta em nosso sistema\n");
    return 0;
  }
  // variavel senha
  int senha;
  printf("Insira seu PIN: ");
  scanf("%d", &senha);
  // verifica se a senha esta correta
  if (lu->u[dadosusuario].senha == senha) {
    // abre o arquivo
    FILE *f = fopen("extrato.txt", "w");
    // percorre toda a lista do historico e printa
    for (int i = 0; i <= lu->u[dadosusuario].qtd; i++) {
      fprintf(f, "\n%s", lu->u[dadosusuario].e[i].historico);
    }
    // fecha o arquivo
    fclose(f);
    // caso o PIN esteja incorreto
  } else {
    printf("PIN incorreto\n ");
    return 0;
  }
  return 0;
}

// função print menu
void printMenu() {
  printf("\n------- Menu -------\n1. Novo Cliente\n2. Apaga Cliente\n3. Listar "
         "Clientes\n4. Débito\n5. Depósito\n6. Extrato\n7. Transferência\n0. "
         "Sair\n--------------------\n");
}

// função que salva a lista de usuarios no aqruivo
int salvarLista(ListaDeUsuarios lu, char arquivo[]) {
  // abre arquivo
  FILE *f = fopen(arquivo, "wb");
  // caso nao exista arquivo um é criado
  if (f == NULL) {
    return 1;
  }
  // escreve a lista dos usuarios no arquivo
  fwrite(&lu, sizeof(ListaDeUsuarios), 1, f);
  // fecha o arquivo
  fclose(f);
  return 0;
}
// função que le a lista
int carregarLista(ListaDeUsuarios *lu, char arquivo[]) {
  // abre o arquivo
  FILE *f = fopen(arquivo, "rb");
  // caso nao exista arquivo um é criado
  if (f == NULL) {
    return 1;
  }
  // le o conteudo do arquivo
  fread(lu, sizeof(ListaDeUsuarios), 1, f);
  // fecha o arquivo
  fclose(f);
  return 0;
}