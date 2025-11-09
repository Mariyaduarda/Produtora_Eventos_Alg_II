#include "menuProdutora.h"

TipoProdutora menuProdutoraRecebe() {
    // Recebe uma nova Produtora do usuario e retorna a produtora preenchida
    TipoProdutora produtora;
    produtoraInit(&produtora);

    // Recebe os dados da produtora
    recebeString(produtora.nomeFantasia, 100, "Digite o Nome Fantasia","Max. 100");
    recebeString(produtora.razaoSocial, 100, "Digite a Razao Social","Max. 100");
    recebeString(produtora.inscricaoEstadual, 20, "Digite a Inscricao Estadual","9 Digitos");
    recebeCNPJ(produtora.cnpj);
    recebeString(produtora.endereco, 100, "Digite o Endereco","Max. 100");
    recebeTelefone(produtora.telefone);
    recebeEmail(produtora.email);
    recebeString(produtora.nomeDoResponsavel, 100, "Digite o Nome do Responsavel","Max. 100");
    recebeString(produtora.telefoneDoResponsavel, 11, "Digite o Telefone do Responsavel","10 ou 11 Digitos");
    produtora.margemDeLucro = recebeFloat(0, 1000000, "Digite a Margem de Lucro", "Entre 0 e 1m");

    return produtora;
}

void menuProdutoraAtualizar(TipoProdutora* produtora) {
    // Atualiza os dados da produtora
    TipoProdutora novoProdutora;
    novoProdutora = menuProdutoraRecebe();
    *produtora = novoProdutora;
}

void menuProdutoraApagar(TipoProdutora* produtora) {
    // Apaga os dados da produtora

    // Pede confirmacao
    if (recebeConfirma()) {
        produtoraInit(produtora);
        printMensagem("Dados apagados com sucesso","#");
    } else{
        printMensagem("Operacao cancelada","#");
    }

}

void menuProdutora(TipoProdutora* produtora) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Produtora
        printMenuProdutora(*produtora);

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 2, "Digite uma opcao", "#");

        switch (escolha){
            case 1:
                // Atualizar dados da produtora
                menuProdutoraAtualizar(produtora);
                esperaEnter();
                break;
            case 2:
                // Apagar dados da produtora
                menuProdutoraApagar(produtora);
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