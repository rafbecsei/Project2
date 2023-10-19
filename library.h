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

void printMenu();