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
                printf("\n => Saindo do sistema");
                exit(0);
            default:
                printf("\n => Opcao Invalida");
        }
    }
    
}