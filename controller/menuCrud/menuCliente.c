#include <stdio.h>

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
