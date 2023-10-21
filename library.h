typedef struct usuario{
    char nome[100];
    long cpf;
    int tipoconta;
    float valor;
    int senha;
} Usuario;

typedef struct{
    Usuario u[3];
    int qtd;
} ListaDeUsuarios;


int novousuario(ListaDeUsuarios *lu);
int apagarusuario(ListaDeUsuarios *lu);
int listarusuarios(ListaDeUsuarios lu);
int debito(ListaDeUsuarios *lu);
int deposito();
// int extrato();
int transferencia();

void printMenu();