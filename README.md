# Project2 

Desenvolvimento de um programa para o projeto do novo banco "QuemPoupaTem", através da criação de um sistema bancário que permite o gerenciamento de clientes e suas operações em dois tipos de conta: Comum e Plus. O sistema opera em um loop infinito até que a opção de sair seja escolhida, apresentando um menu de opções. As principais funcionalidades incluem:

1.Novo Cliente: Permite ao usuário adicionar um novo cliente ao banco, coletando informações como nome, CPF, tipo de conta, saldo inicial e PIN.

2.Apagar Cliente: Permite ao usuário remover um cliente existente, excluindo suas informações do sistema.

3.Listar Clientes: Exibe uma lista dos clientes cadastrados, incluindo informações como nome, CPF, tipo de conta e saldo.

4.Débito: Permite que os clientes retirem uma quantia preestabelecida de suas contas, aplicando taxas com base no tipo de conta e atualizando o histórico de operações.

5.Depósito: Permite que os clientes depositem dinheiro em suas contas, atualizando o histórico de operações.

6.Extrato: Gera um arquivo contendo as informações das últimas operações (débito, depósito, transferência) realizadas por um cliente.

7.Transferência Entre Contas: Permite o câmbio de fundos entre contas, aplicando taxas com base no tipo de conta e atualizando o histórico de operações.

8.Sair: Encerra o programa e encerra o loop.

O programa é capaz de armazenar informações de até 1000 clientes e as informações das últimas 100 operações para cada cliente. 