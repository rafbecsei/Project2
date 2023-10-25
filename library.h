typedef struct extrato {
  char historico[300];
} Extrato;

typedef struct usuario {
  char nome[100];
  long cpf;
  int tipoconta;
  float valor;
  int senha;
  Extrato e[100];
  int qtd;
} Usuario;

typedef struct {
  Usuario u[3];
  int qtd;
} ListaDeUsuarios;

int novousuario(ListaDeUsuarios *lu);
int apagarusuario(ListaDeUsuarios *lu);
int listarusuarios(ListaDeUsuarios lu);
int debito(ListaDeUsuarios *lu);
int deposito(ListaDeUsuarios *lu);
int extrato(ListaDeUsuarios *lu);
int transferencia(ListaDeUsuarios *lu);

void printMenu();

