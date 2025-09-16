#include "menuController.h"

void menuPrincipal() {
    // Declara as listas


    // Inicializa as listas
    inicializarListas();

    // Enquanto o usuario n quiser sair, continua no menu
    int escolha;
    while (escolha != 0){
        // Exibe o menu principal
        LimparTela();
        printMenuPrincipal();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        switch (escolha){
            case 1:
                // Gerenciar Clientes
                menuClientes();
                break;
            case 2:
                // Gerenciar Fornecedores e Parceiros
                menuFornecedoresParceiros();
                break;
            case 3:
                // Gerenciar Produtora
                menuProdutora();
                break;
            case 4:
                // Gerenciar Equipe Interna
                menuEquipeInterna();
                break;
            case 5:
                // Gerenciar Recursos e Equipamentos
                menuRecursosEquipamentos();
                break;
            case 6:
                // Gerenciar Operadores do Sistema
                menuOperadoresSistema();
                break;
            case 0:
                // Sair
                printf("\n => Saindo do sistema");
                exit(0);
            default:
                printf("\n => Opcao Invalida");
        }
    }
    
}