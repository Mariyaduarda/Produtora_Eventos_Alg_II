#include "menuController.h"

void menuPrincipal(TipoProdutora *produtora, ListaCliente **listaCliente, 
    ListaFornecedor **listaFornecedor, ListaEquipe **listaEquipe, 
    ListaRecurso **listaRecurso, ListaOperador **listaOperador) 
{
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu principal
        printMenuPrincipal();

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 6, "Digite uma opcao", "#");
        
        switch (escolha){
            case 1:
                // Gerenciar Produtora
                menuProdutora(produtora);
                break;
            case 2:
                // Gerenciar TipoCliente
                menuCliente(listaCliente);
                break;
            case 3:
                // Gerenciar Equipe Interna
                menuEquipe(listaEquipe);
                break;
            case 4:
                // Gerenciar Fornecedores e Parceiros
                menuFornecedor(listaFornecedor);
                break;
            case 5:
                // Gerenciar Operadores do Sistema
                menuOperador(listaOperador);
                break;
            case 6:
                // Gerenciar Recursos e Equipamentos
                menuRecurso(listaRecurso);
                break;
            case 0:
                // Sair
                return;
            default:
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }
    }
    
}