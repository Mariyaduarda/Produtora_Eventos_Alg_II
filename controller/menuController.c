#include "menuController.h"

void menuPrincipal(ListaCliente **listaCliente, ListaFornecedorParceiro **listaFornecedoresParceiros, ListaProdutora **listaProdutoras, ListaEquipeInterna **listaEquipeInterna, ListaRecursoEquipamento **listaRecursosEquipamentos, ListaOperadorSistema **listaOperadoresSistema) {
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
                // Gerenciar TipoCliente
                menuCliente(*listaCliente);
                break;
            case 2:
                // Gerenciar Fornecedores e Parceiros
                menuFornecedorParceiro();
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
                menuRecursoEquipamento();
                break;
            case 6:
                // Gerenciar Operadores do Sistema
                menuOperadorSistema();
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