#include "menuProdutora.h"

TipoProdutora menuProdutoraRecebe() {
    // Recebe uma nova Produtora do usuario e retorna a produtora preenchida
    TipoProdutora produtora;
    inicializarProdutora(&produtora);

    // Recebe os dados da produtora
    produtora.id = 0; // ID sera atribuido automaticamente
    recebeString(produtora.nomeFantasia, 100, "Digite o Nome Fantasia","Max. 100");
    recebeString(produtora.razaoSocial, 100, "Digite a Razao Social","Max. 100");
    recebeString(produtora.inscricaoEstadual, 20, "Digite a Razao Social","9 Digitos");
    recebeString(produtora.cnpj, 20, "Digite o CPF","14 Digitos");
    recebeString(produtora.endereco, 100, "Digite o Endereco","Max. 100");
    recebeString(produtora.telefone, 20, "Digite o Telefone","10 ou 11 Digitos");
    recebeString(produtora.email, 100, "Digite o Email","Max. 100");
    recebeString(produtora.nomeDoResponsavel, 100, "Digite o Nome do Responsavel","Max. 100");
    recebeString(produtora.telefoneDoResponsavel, 11, "Digite o Telefone do Responsavel","10 ou 11 Digitos");
    produtora.margemDeLucro = recebeFloat(0, 1000000, "Digite a Margem de Lucro", "Entre 0 e 1m");

    return produtora;
}

void listarProdutoras(ListaProdutora *lista) {
    limparTela();

    // Lista todas as produtoras cadastradas
    if (lista == NULL) {
        printf("\n => Nenhuma produtora cadastrada.\n");
        return;
    }

    printTabelaLinha();
    ListaProdutora *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->produtora.ativo) printItemProdutora(atual->produtora);
        atual = atual->prox;

        // se n for o ultimo, printa a linha horizontal p dividir
        if (atual != NULL) printTabelaLinhaInterior();
    }
    printTabelaLinha();
    printf("\n");
}

void menuProdutora(ListaProdutora **listaProdutora) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Produtora
        printMenuProdutora();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado
        TipoProdutora *produtora; // Para guardar resultado de busca

        switch (escolha){
            case 1:
                // Adicionar Produtora
                if ( adicionarProdutora(listaProdutora, menuProdutoraRecebe()) ) printAdicionarSucesso();
                else printAdicionarFalha();
                esperaEnter();
                break;
            case 2:
                // Remover Produtora
                if ( removerProdutora(listaProdutora, recebeInt(1, 1000000, "Digite o ID", "Min. 1")) ) printRemoverSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 3:
                // Atualizar Produtora
                if ( atualizarProdutora(*listaProdutora, menuProdutoraRecebe(), recebeInt(1, 1000000, "Digite o ID", "Min. 1")) ) printAtualizarSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 4:
                // Buscar Produtora
                produtora = buscarProdutora(*listaProdutora, recebeInt(1, 1000000, "Digite o ID", "Min. 1"));
                if (produtora != NULL) {
                    printTabelaLinha();
                    printItemProdutora(*produtora);
                    printTabelaLinha();
                }
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 5:
                // Listar Produtoras
                listarProdutoras(*listaProdutora);
                esperaEnter();
                break;
            case 0:
                // Voltar ao menu principal
                printf("\n => Voltando ao menu principal...\n");
                break;
            default:
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }
    }while (escolha != 0);
}