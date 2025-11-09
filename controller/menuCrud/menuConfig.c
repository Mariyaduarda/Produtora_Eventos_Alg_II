#include "menuConfig.h"

void menuConfig(TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Configuracoes
        limparTela();
        printMenuConfig(*config);

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 2, "Digite uma opcao", "#");

        switch (escolha){
            case 1:
                // Alterna se salva como txt ou binario
                config->salvar_como_binario = !config->salvar_como_binario;
                break;
            case 2:
                // Liga ou desliga a validacao de dados
                config->validar_dados = !config->validar_dados;
                break;
            case 0:
                // Voltar
                return;
            default:
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }

    }while (escolha != 0);
}
