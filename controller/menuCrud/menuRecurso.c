#include "menuRecurso.h"

TipoRecurso menuRecursoRecebe() {
    // Recebe um novo Recurso/Equipamento do usuario e retorna o recurso/equipamento preenchido
    TipoRecurso recurso;
    inicializarRecurso(&recurso);

    // Recebe os dados do recurso/equipamento
    recurso.id = 0; // ID sera atribuido automaticamente
    recebeDescricao(recurso.descricao, 150);
    recebeCategoria(recurso.categoria, 50);
    recurso.qtdEstoque = recebeQuantidadeEstoque();
    recurso.precoCusto = recebePrecoCusto();
    recurso.valorLocacao = recebeValorLocacao();

    return recurso;
}

void listarRecurso(ListaRecurso *lista) {
    limparTela();

    // Lista todos os recursos/equipamentos cadastrados
    if (lista == NULL) {
        printf("\n => Nenhum recurso/equipamento cadastrado.\n");
        return;
    }

    ListaRecurso *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->recurso.ativo) printItemRecurso(atual->recurso);
        atual = atual->prox;
    }
    printf("\n");
}

void menuRecurso(ListaRecurso **listaRecurso) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=1;
    while (escolha != 0){
        // Exibe o menu de Recurso/Equipamento
        printMenuRecurso();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Recurso/Equipamento
                adicionarRecurso(listaRecurso, menuRecursoRecebe());
                break;
            case 2:
                // Remover Recurso/Equipamento
                removerRecurso(listaRecurso, recebeID());
                break;
            case 3:
                // Atualizar Recurso/Equipamento
                atualizarRecurso(*listaRecurso, menuRecursoRecebe(), recebeID());
                break;
            case 4:
                // Buscar Recurso/Equipamento
                printItemRecurso(*buscarRecurso(*listaRecurso, recebeID()));
                esperaEnter();
                break;
            case 5:
                // Listar Recursos/Equipamentos
                listarRecurso(*listaRecurso);
                esperaEnter();
                break;
            case 0:
                // Voltar ao menu principal
                printf("\nVoltando ao menu principal...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                esperaEnter();
                break;
        }
    }
}