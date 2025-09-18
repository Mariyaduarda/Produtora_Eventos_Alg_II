#include "menuEquipeInterna.h"

void menuEquipeInterna(ListaEquipeInterna **listaEquipeInterna) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu de Equipe Interna
        printMenuEquipeInterna();

        // Recebe a escolha do usuario
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