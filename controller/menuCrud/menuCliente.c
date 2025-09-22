#include "menuCliente.h"

TipoCliente menuClienteRecebe() {
    // Recebe um novo Cliente do usuario e retorna o cliente preenchido
    TipoCliente cliente;
    inicializarCliente(&cliente);
    
    //Recebe os dados do cliente
    cliente.id = 0; // ID sera atribuido automaticamente
    recebeNome(cliente.nome, 100);
    recebeCPF(cliente.cpf_cnpj);
    recebeTelefone(cliente.telefone);
    recebeEmail(cliente.email, 100);

    return cliente;
}

void menuCliente(ListaCliente **listaCliente) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu de Cliente
        printMenuCliente();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        switch (escolha){
            case 1:
                // Adicionar Cliente
                adicionarCliente(listaCliente, menuClienteRecebe());
                break;
            case 2:
                // Remover Cliente
                removerCliente(listaCliente, recebeID());
                break;
            case 3:
                // Atualizar Cliente
                atualizarCliente(*listaCliente, menuClienteRecebe(), recebeID());
                break;
            case 4:
                // Buscar Cliente
                buscaCliente(*listaCliente, recebeID());
                break;
            case 5:
                // Listar Clientes
                listarClientes(*listaCliente);
                break;
            case 0:
                // Voltar ao menu principal
                printf("\n => Voltando ao menu principal");
                break;
            default:
                // Opcao invalida
                opcaoInvalida();
        }
    }
    
}