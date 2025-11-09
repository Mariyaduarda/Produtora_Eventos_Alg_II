#include "menuProdutora.h"

TipoProdutora menuProdutoraRecebe(TipoConfig *config) {
    // Recebe uma nova Produtora do usuario e retorna a produtora preenchida
    TipoProdutora produtora;
    produtoraInit(&produtora);

    // Recebe os dados da produtora
    recebeString(produtora.nomeFantasia, 100, "Digite o Nome Fantasia","Max. 100", config->validar_dados);
    recebeString(produtora.razaoSocial, 100, "Digite a Razao Social","Max. 100", config->validar_dados);
    recebeString(produtora.inscricaoEstadual, 20, "Digite a Inscricao Estadual","9 Digitos", config->validar_dados);
    recebeCNPJ(produtora.cnpj, config->validar_dados);
    recebeString(produtora.endereco, 100, "Digite o Endereco","Max. 100", config->validar_dados);
    recebeTelefone(produtora.telefone, config->validar_dados);
    recebeEmail(produtora.email, config->validar_dados);
    recebeString(produtora.nomeDoResponsavel, 100, "Digite o Nome do Responsavel","Max. 100", config->validar_dados);
    recebeString(produtora.telefoneDoResponsavel, 11, "Digite o Telefone do Responsavel","10 ou 11 Digitos", config->validar_dados);
    produtora.margemDeLucro = recebeFloat(0, 1000000, "Digite a Margem de Lucro", "Entre 0 e 1m", config->validar_dados);

    return produtora;
}

void menuProdutoraAtualizar(TipoProdutora* produtora, TipoConfig *config) {
    // Atualiza os dados da produtora
    TipoProdutora novoProdutora;
    novoProdutora = menuProdutoraRecebe(config);
    *produtora = novoProdutora;
}

void menuProdutoraApagar(TipoProdutora* produtora, TipoConfig *config) {
    // Apaga os dados da produtora

    // Pede confirmacao
    if (recebeConfirma()) {
        produtoraInit(produtora);
        printMensagem("Dados apagados com sucesso","#");
    } else{
        printMensagem("Operacao cancelada","#");
    }

}

void menuProdutora(TipoProdutora* produtora, TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Produtora
        printMenuProdutora(*produtora);

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 2, "Digite uma opcao", "#", config->validar_dados);

        switch (escolha){
            case 1:
                // Atualizar dados da produtora
                menuProdutoraAtualizar(produtora, config);
                esperaEnter();
                break;
            case 2:
                // Apagar dados da produtora
                menuProdutoraApagar(produtora, config);
                esperaEnter();
                break;
            case 0:
                // Voltar ao menu principal
                break;
            default:
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }
    }while (escolha != 0);
    
}