#include "menuRecurso.h"

TipoRecurso menuRecursoRecebe() {
    // Recebe um novo Recurso/Equipamento do usuario e retorna o recurso/equipamento preenchido
    TipoRecurso recurso;
    inicializarRecurso(&recurso);

    // Recebe os dados do recurso/equipamento
    recurso.id = 0; // ID sera atribuido automaticamente
    
    recebeString(recurso.descricao, 150, "Digite a Descricao","Max. 150");
    recebeString(recurso.categoria, 50, "Digite a Categoria","Max. 50");
    recurso.qtdEstoque = recebeInt(0, 1000000, "Digite a Qtd no Estoque", "Entre 0 e 1m");
    recurso.precoCusto = recebeFloat(0, 1000000, "Digite o Preco Custo", "Entre 0 e 1m");
    recurso.valorLocacao = recebeFloat(0, 1000000, "Digite o Valor de Locacao", "Entre 0 e 1m");

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
    int escolha=0;
    do{
        // Exibe o menu de Recurso/Equipamento
        printMenuRecurso();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado
        TipoRecurso *recurso; // Para guardar resultado de busca

        switch (escolha){
            case 1:
                // Adicionar Recurso/Equipamento
                if ( adicionarRecurso(listaRecurso, menuRecursoRecebe()) ) printAdicionarSucesso();
                else printAdicionarFalha();
                esperaEnter();
                break;
            case 2:
                // Remover Recurso/Equipamento
                if ( removerRecurso(listaRecurso, recebeInt(1, 1000000, "Digite o ID", "Min. 1")) ) printRemoverSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 3:
                // Atualizar Recurso/Equipamento
                if ( atualizarRecurso(*listaRecurso, menuRecursoRecebe(), recebeInt(1, 1000000, "Digite o ID", "Min. 1")) ) printAtualizarSucesso();
                else printNaoEncontrado();
                esperaEnter();
                break;
            case 4:
                // Buscar Recurso
                recurso = buscarRecurso(*listaRecurso, recebeInt(1, 1000000, "Digite o ID", "Min. 1"));
                if (recurso != NULL) {
                    printItemRecurso(*recurso);
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