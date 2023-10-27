# Project2 
Desenvolvimento de um programa do sistema bancário do Banco QuemPoupaTem, com as opções de criar um novo cliente, deletar clientes, listar os clientes, além de realizar ações como, débito, depósito, transferência e por fim o extrato de cada conta, operando com até 1000 clientes diferentes. 


A funcionalidade do código para o projeto do novo banco "QuemPoupaTem" é criar um sistema de controle bancário que permite o gerenciamento de clientes e suas operações em dois tipos de conta: Comum e Plus. O sistema opera em um loop infinito até que a opção de sair seja escolhida, apresentando um menu de opções para o operador. As principais funcionalidades incluem:

Novo Cliente: Permite ao operador adicionar um novo cliente ao banco, coletando informações como nome, CPF, tipo de conta, saldo inicial e PIN.

Apaga Cliente: Permite ao operador remover um cliente existente após confirmação, excluindo suas informações da lista de clientes.

Listar Clientes: Exibe uma lista dos clientes cadastrados, incluindo informações como nome, CPF, tipo de conta e saldo.

Débito: Permite que os clientes façam retiradas de suas contas, aplicando taxas com base no tipo de conta e atualizando o histórico de operações.

Depósito: Permite que os clientes realizem depósitos em suas contas e atualiza o histórico de operações.

Extrato: Gera um extrato contendo as informações das últimas operações (depósito, saque, transferência) realizadas por um cliente e armazena-o em um arquivo.

Transferência Entre Contas: Permite a transferência de fundos entre contas, aplicando taxas com base no tipo de conta e atualizando o histórico de operações.

Sair: Encerra o programa e sai do loop infinito.

O programa é capaz de armazenar informações de até 1000 clientes e as informações das últimas 100 operações para cada cliente. Ele oferece um conjunto de funções que implementam essas funcionalidades, garantindo o controle de contas bancárias, a geração de extratos e a execução de operações financeiras. É importante ressaltar que, em um ambiente real, medidas de segurança e robustez adicionais seriam necessárias para proteger os dados e as operações financeiras dos clientes.