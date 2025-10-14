#include "menuRecurso.h"

TipoRecurso menuRecursoRecebe() {
    // Recebe um novo Recurso/Equipamento do usuario e retorna o recurso/equipamento preenchido
    TipoRecurso recurso;
    recursoInit(&recurso);

    // Recebe os dados do recurso/equipamento
    recurso.id = 0; // ID sera atribuido automaticamente
    
    recebeString(recurso.descricao, 150, "Digite a Descricao","Max. 150");
    recebeString(recurso.categoria, 50, "Digite a Categoria","Max. 50");
    recurso.qtdEstoque = recebeInt(0, 1000000, "Digite a Qtd no Estoque", "Entre 0 e 1m");
    recurso.precoCusto = recebeFloat(0, 1000000, "Digite o Preco Custo", "Entre 0 e 1m");
    recurso.valorLocacao = recebeFloat(0, 1000000, "Digite o Valor de Locacao", "Entre 0 e 1m");

    return recurso;
}

void menuRecursoAdicionar(ListaRecurso **listaRecurso){
    // Guarda o novo item
    TipoRecurso novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuRecursoRecebe(); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printItemRecurso(novo);
        
        if( printConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( recursoAdicionar(listaRecurso, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuRecursoRemover(ListaRecurso **listaRecurso){
    int ID = recebeID(); // recebe o ID do item que vai ser removido
    
    // Busca o Item q vai ser removido
    TipoRecurso *Recurso; // Para guardar resultado de busca
    Recurso = recursoBuscar(*listaRecurso, ID);
    if (Recurso == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Mostra o Item que vai ser removido
    
    printItemRecurso(*Recurso);
    
    
    // Pede confirmacao, se tiver ok, remove o Recurso
    if (printConfirma()){
        recursoRemover(listaRecurso, ID);
        printRemoverSucesso();
    }
}

void menuRecursoAtualizar(ListaRecurso **listaRecurso){
    // Declara um novo item pra receber os dados atualizados
    TipoRecurso novoRecurso;
    TipoRecurso* velhoRecurso;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID();
    velhoRecurso = recursoBuscar(*listaRecurso, ID);

    // Se esse ID n existe, mostra erro
    if (velhoRecurso == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Caso contrario, recebe os novos dados
    novoRecurso = menuRecursoRecebe();

    // ===============================
    // Mostra as mudancas

    // Printa os antigos dados
    printMensagem("Dados Antigos","=");
    
    printItemRecurso(*velhoRecurso);
    
    
    // Printa os novos dados
    printMensagem("Dados Novos","=");
    
    printItemRecurso(novoRecurso);
    
    
    // ===============================
    // Confirma se o usuario realmente quer atualizar
    if (printConfirma()){
        recursoAtualizar(*listaRecurso, novoRecurso, ID);
        printAtualizarSucesso();
    }
}

void menuRecursoBuscar(ListaRecurso **listaRecurso){
    TipoRecurso *Recurso; // Para guardar resultado de busca
    Recurso = recursoBuscar(*listaRecurso, recebeID());
    if (Recurso != NULL){
        
        printItemRecurso(*Recurso);
        
    }
    else printNaoEncontrado();
}

void menuRecursoListar(ListaRecurso *lista) {
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
        // Exibe o menu de Recurso
        printMenuRecurso();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Recurso
                menuRecursoAdicionar(listaRecurso);
                esperaEnter();
                break;
            case 2:
                // Remover Recurso
                menuRecursoRemover(listaRecurso);
                esperaEnter();
                break;
            case 3:
                // Atualizar Recurso
                menuRecursoAtualizar(listaRecurso);
                esperaEnter();
                break;
            case 4:
                // Buscar Recurso
                menuRecursoBuscar(listaRecurso);
                esperaEnter();
                break;
            case 5:
                // Listar Recursos
                menuRecursoListar(*listaRecurso);
                esperaEnter();
                break;
            case 0:
                // Voltar ao menu principal
                printf("\n => Voltando ao menu principal");
                break;
            default:
                // Opcao invalida
                printOpcaoInvalida();
                esperaEnter();
        }
    }while (escolha != 0);
    
}