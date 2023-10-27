// definindo a extrutura do extrado
typedef struct extrato {
  char historico[300];
} Extrato;
// definindo a extrutura do cliente
typedef struct usuario {
  char nome[100];
  long cpf;
  int tipoconta;
  float valor;
  int senha;
  Extrato e[100];
  int qtd;
} Usuario;
// definindo a estrutura da lista de clientes
typedef struct {
  Usuario u[1000];
  int qtd;
} ListaDeUsuarios;
// função de criar cliente
int novousuario(ListaDeUsuarios *lu);
// função de apagar cliente
int apagarusuario(ListaDeUsuarios *lu);
// função de listar clientes
int listarusuarios(ListaDeUsuarios lu);
// função de debito
int debito(ListaDeUsuarios *lu);
// função de deposito
int deposito(ListaDeUsuarios *lu);
// função de extrato
int extrato(ListaDeUsuarios *lu);
// função de tranferencia
int transferencia(ListaDeUsuarios *lu);
// função para printar o menu
void printMenu();
// função para salvar a lista de usuarios no arquivo
int salvarLista(ListaDeUsuarios lu, char arquivo[]);
// função para carregar a lista de usuarios do arquivo
int carregarLista(ListaDeUsuarios *lu, char arquivo[]);