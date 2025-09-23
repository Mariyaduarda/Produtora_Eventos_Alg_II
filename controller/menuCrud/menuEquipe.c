#include "menuEquipe.h"

TipoEquipe menuEquipeRecebe() {
    // Recebe uma nova Equipe Interna do usuario e retorna a equipe preenchida
    TipoEquipe equipe;
    inicializarEquipe(&equipe);

    // Recebe os dados da equipe interna
    equipe.id = 0; // ID sera atribuido automaticamente
    recebeNome(equipe.nome, 100);
    recebeCPF(equipe.cpf);
    recebeFuncao(equipe.funcao, 50);
    recebeValorDiaria(&equipe.valorDiariaHora);

    return equipe;
}

void listarEquipesInternas(ListaEquipe *lista) {
    limparTela();

    // Lista todas as equipes internas cadastradas
    if (lista == NULL) {
        printf("\n => Nenhuma equipe interna cadastrada.\n");
        return;
    }

    printTabelaLinha();
    ListaEquipe *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->equipe.ativo) printItemEquipe(atual->equipe);
        atual = atual->prox;

        // se n for o ultimo, printa a linha horizontal p dividir
        if (atual != NULL) printTabelaLinhaInterior();
    }
    printTabelaLinha();
    printf("\n");
}

void menuEquipe(ListaEquipe **listaEquipe) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Equipe Interna
        printMenuEquipe();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Equipe Interna
                if ( adicionarEquipe(listaEquipe, menuEquipeRecebe()) ) printAdicionarSucesso();
                else printAdicionarFalha();
                esperaEnter();
                break;
            case 2:
                // Remover Equipe Interna
                if ( removerEquipe(listaEquipe, recebeID()) ) printRemoverSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 3:
                // Atualizar Equipe Interna
                if (atualizarEquipe(*listaEquipe, menuEquipeRecebe(), recebeID())) printAtualizarSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 4:
                // Buscar Equipe Interna
                TipoEquipe *equipe = buscarEquipe(*listaEquipe, recebeID());
                if (equipe != NULL) {
                    printTabelaLinha();
                    printItemEquipe(*equipe);   
                    printTabelaLinha();
                }
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 5:
                // Listar Equipes Internas
                listarEquipesInternas(*listaEquipe);
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