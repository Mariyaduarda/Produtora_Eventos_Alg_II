#include "menuController.h"

void menuPrincipal(ListaCliente **listaCliente, ListaFornecedorParceiro **listaFornecedorParceiro, ListaProdutora **listaProdutora, ListaEquipeInterna **listaEquipeInterna, ListaRecursoEquipamento **listaRecursoEquipamento, ListaOperadorSistema **listaOperadorSistema) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu principal
        printMenuPrincipal();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        switch (escolha){
            case 1:
                // Gerenciar TipoCliente
                menuCliente(listaCliente);
                break;
            case 2:
                // Gerenciar Fornecedores e Parceiros
                menuFornecedorParceiro(listaFornecedorParceiro);
                break;
            case 3:
                // Gerenciar Produtora
                menuProdutora(listaProdutora);
                break;
            case 4:
                // Gerenciar Equipe Interna
                menuEquipeInterna(listaEquipeInterna);
                break;
            case 5:
                // Gerenciar Recursos e Equipamentos
                menuRecursoEquipamento(listaRecursoEquipamento);
                break;
            case 6:
                // Gerenciar Operadores do Sistema
                menuOperadorSistema(listaOperadorSistema);
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