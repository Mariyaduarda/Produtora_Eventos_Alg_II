#include <stdio.h>
#include "../view/menuView.h"
#include "../view/menuView.c"
#include "../utils/utils_tela.c"

void menuClientes() {
    LimparTela();
    printMenuClientes();

    // Recebe a escolha do usuario
    int escolha;
    scanf("%d", &escolha);
    switch (escolha){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 0:
            return;
        default:
            printf("\n => Opcao Invalida");
    }
}

void menuFornecedoresParceiros() {
    // Exibe o menu de fornecedores e parceiros
    printMenuFornecedoresParceiros();
}

void menuProdutora() {
    // Exibe o menu de produtora
    printMenuProdutora();
}

void menuEquipeInterna() {
    // Exibe o menu de equipe interna
    printMenuEquipeInterna();
}

void menuRecursosEquipamentos() {
    // Exibe o menu de recursos e equipamentos
    printMenuRecursosEquipamentos();
}

void menuOperadoresSistema() {
    // Exibe o menu de operadores do sistema
    printMenuOperadoresSistema();
}

void menuPrincipal() {
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