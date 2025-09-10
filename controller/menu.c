#include <stdio.h>
#include "../view/menu.h"

void menuPrincipal() {

    // Exibe o menu principal
    printMenuPrincipal();

    // Recebe a escolha do usuario
    int escolha;
    scanf("%d", &escolha);
    switch (escolha){
        case 1:
            // Gerenciar Clientes
            break;
        case 2:
            // Gerenciar Fornecedores e Parceiros
            break;
        case 3:
            // Gerenciar Produtora
            break;
        case 4:
            // Gerenciar Equipe Interna
            break;
        case 5:
            // Gerenciar Recursos e Equipamentos
            break;
        case 6:
            // Gerenciar Operadores do Sistema
            break;
        case 0:
            // Sair
            printf("Saindo do sistema...\n");
            exit(0);
        default:
            printf("Opcao invalida! Tente novamente.\n");
    }

}

void menuClientes() {
    // Exibe o menu de clientes
    printMenuClientes();
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