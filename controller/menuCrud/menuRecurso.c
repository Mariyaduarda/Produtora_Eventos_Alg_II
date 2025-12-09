#include "menuRecurso.h"

TipoRecurso menuRecursoRecebe(TipoConfig *config) {
    // Recebe um novo Recurso/Equipamento do usuario e retorna o recurso/equipamento preenchido
    TipoRecurso recurso;
    recursoInit(&recurso);

    // Recebe os dados do recurso/equipamento
    recurso.id = 0; // ID sera atribuido automaticamente
    
    recebeString(recurso.descricao, 150, "Digite a Descricao","Max. 150", config->validar_dados);
    recebeString(recurso.categoria, 50, "Digite a Categoria","Max. 50", config->validar_dados);
    recurso.qtdEstoque = recebeInt(0, 1000000, "Digite a Qtd no Estoque", "Entre 0 e 1m", config->validar_dados);
    recurso.precoCusto = recebeFloat(0, 1000000, "Digite o Preco Custo", "Entre 0 e 1m", config->validar_dados);
    recurso.valorLocacao = recebeFloat(0, 1000000, "Digite o Valor de Locacao", "Entre 0 e 1m", config->validar_dados);

    return recurso;
}

void menuRecursoAdicionar(ListaRecurso **listaRecurso, TipoConfig *config){
    // Guarda o novo item
    TipoRecurso novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuRecursoRecebe(config); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printItemRecurso(novo);
        
        if( recebeConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( recursoAdicionar(listaRecurso, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuRecursoRemover(ListaRecurso **listaRecurso, TipoConfig *config){
    int ID = recebeID(config->validar_dados); // recebe o ID do item que vai ser removido
    
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
    if (recebeConfirma()){
        recursoRemover(listaRecurso, ID);
        printRemoverSucesso();
    }
}

void menuRecursoAtualizar(ListaRecurso **listaRecurso, TipoConfig *config){
    // Declara um novo item pra receber os dados atualizados
    TipoRecurso novoRecurso;
    TipoRecurso* velhoRecurso;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID(config->validar_dados);
    velhoRecurso = recursoBuscar(*listaRecurso, ID);

    // Se esse ID n existe, mostra erro
    if (velhoRecurso == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Caso contrario, recebe os novos dados
    novoRecurso = menuRecursoRecebe(config);

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
    if (recebeConfirma()){
        recursoAtualizar(*listaRecurso, novoRecurso, ID);
        printAtualizarSucesso();
    }
}

void menuRecursoBuscar(ListaRecurso **listaRecurso, TipoConfig *config){
    TipoRecurso *Recurso; // Para guardar resultado de busca
    Recurso = recursoBuscar(*listaRecurso, recebeID(config->validar_dados));
    if (Recurso != NULL){
        
        printItemRecurso(*Recurso);
        
    }
    else printNaoEncontrado();
}

void menuRecursoListar(ListaRecurso *lista, TipoConfig *config) {
    limparTela();

    // Lista todos os recursos/equipamentos cadastrados
    if (lista == NULL) {
        printMensagem("Nenhum item cadastrado","#");
        return;
    }

    
    ListaRecurso *atual = lista; // comeca auxiliar no comeco da lista
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->recurso.ativo) printItemRecurso(atual->recurso);
        atual = atual->prox;
    }
    
    // barra de baixo
    printf("\n======================================================================");
}

void menuRecurso(ListaRecurso **listaRecurso, TipoConfig *config) {
    // Enquanto o usuario n quiser sair, continua no menu
    int escolha=0;
    do{
        // Exibe o menu de Recurso
        printMenuRecurso();

        // Recebe a escolha do usuario
        escolha = recebeInt(0, 5, "Digite uma opcao", "#", config->validar_dados);

        switch (escolha){
            case 1:
                // Adicionar Recurso
                menuRecursoAdicionar(listaRecurso, config);
                esperaEnter();
                break;
            case 2:
                // Remover Recurso
                menuRecursoRemover(listaRecurso, config);
                esperaEnter();
                break;
            case 3:
                // Atualizar Recurso
                menuRecursoAtualizar(listaRecurso, config);
                esperaEnter();
                break;
            case 4:
                // Buscar Recurso
                menuRecursoBuscar(listaRecurso, config);
                esperaEnter();
                break;
            case 5:
                // Listar Recursos
                menuRecursoListar(*listaRecurso, config);
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