#include "menuController.h"

void menuPrincipal(ListaCliente **listaCliente, ListaFornecedor **listaFornecedor, ListaProdutora **listaProdutora, ListaEquipe **listaEquipe, ListaRecurso **listaRecurso, ListaOperador **listaOperador) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu principal
        printMenuPrincipal();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado
        switch (escolha){
            case 1:
                // Gerenciar TipoCliente
                menuCliente(listaCliente);
                break;
            case 2:
                // Gerenciar Fornecedores e Parceiros
                menuFornecedor(listaFornecedor);
                break;
            case 3:
                // Gerenciar Produtora
                menuProdutora(listaProdutora);
                break;
            case 4:
                // Gerenciar Equipe Interna
                menuEquipe(listaEquipe);
                break;
            case 5:
                // Gerenciar Recursos e Equipamentos
                menuRecurso(listaRecurso);
                break;
            case 6:
                // Gerenciar Operadores do Sistema
                menuOperador(listaOperador);
                break;
            case 0:
                // Sair
                printf("\n => Saindo do sistema");
                exit(0);
            default:
                // Opcao invalida
                opcaoInvalida();
        }
    }
    
}