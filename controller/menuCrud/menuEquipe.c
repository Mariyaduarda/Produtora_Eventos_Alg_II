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

    ListaEquipe *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->equipe.ativo) printItemEquipe(atual->equipe);
        atual = atual->prox;
    }
    printf("\n");
}

void menuEquipe(ListaEquipe **listaEquipe) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu de Equipe Interna
        printMenuEquipe();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Equipe Interna
                adicionarEquipe(listaEquipe, menuEquipeRecebe());
                break;
            case 2:
                // Remover Equipe Interna
                removerEquipe(listaEquipe, recebeID());
                break;
            case 3:
                // Atualizar Equipe Interna
                atualizarEquipe(*listaEquipe, menuEquipeRecebe(), recebeID());
                break;
            case 4:
                // Buscar Equipe Interna
                buscarEquipe(*listaEquipe, recebeID());
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
                printf("\n => Opcao invalida! Tente novamente.\n");
                esperaEnter();
                break;
        }
    }
}