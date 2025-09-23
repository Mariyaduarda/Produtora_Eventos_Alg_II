#include "menuRecurso.h"

TipoRecurso menuRecursoRecebe() {
    // Recebe um novo Recurso/Equipamento do usuario e retorna o recurso/equipamento preenchido
    TipoRecurso recurso;
    inicializarRecurso(&recurso);

    // Recebe os dados do recurso/equipamento
    recurso.id = 0; // ID sera atribuido automaticamente
    
    recebeString(recurso.descricao, 150, "Digite a Descricao","Max. 150");
    recebeString(recurso.categoria, 50, "Digite a Categoria","Max. 50");
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

    printTabelaLinha();
    ListaRecurso *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->recurso.ativo) printItemRecurso(atual->recurso);
        atual = atual->prox;

        // se n for o ultimo, printa a linha horizontal p dividir
        if (atual != NULL) printTabelaLinhaInterior();
    }
    printTabelaLinha();
    printf("\n");
}

void menuRecurso(ListaRecurso **listaRecurso) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Recurso/Equipamento
        printMenuRecurso();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Recurso/Equipamento
                if ( adicionarRecurso(listaRecurso, menuRecursoRecebe()) ) printAdicionarSucesso();
                else printAdicionarFalha();
                esperaEnter();
                break;
            case 2:
                // Remover Recurso/Equipamento
                if ( removerRecurso(listaRecurso, recebeID()) ) printRemoverSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 3:
                // Atualizar Recurso/Equipamento
                if ( atualizarRecurso(*listaRecurso, menuRecursoRecebe(), recebeID()) ) printAtualizarSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 4:
                // Buscar Recurso
                TipoRecurso *recurso = buscarRecurso(*listaRecurso, recebeID());
                if (recurso != NULL) {
                    printTabelaLinha();
                    printItemRecurso(*recurso);
                    printTabelaLinha();
                }
                else printNaoEncontrado();
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
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }
    }while (escolha != 0);
}