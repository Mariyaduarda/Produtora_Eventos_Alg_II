#include "menuEquipe.h"

TipoEquipe menuEquipeRecebe() {
    // Recebe uma nova Equipe Interna do usuario e retorna a equipe preenchida
    TipoEquipe equipe;
    equipeInit(&equipe);

    // Recebe os dados da equipe interna
    equipe.id = 0; // ID sera atribuido automaticamente
    recebeString(equipe.nome, 100, "Digite o Nome","Max. 100");
    recebeCPF(equipe.cpf);
    recebeString(equipe.funcao, 50, "Digite a Funcao","Max. 50");
    equipe.valorDiariaHora = recebeFloat(0, 1000000, "Digite o Valor da Diaria", "Entre 0 e 1m");

    return equipe;
}

void menuEquipeAdicionar(ListaEquipe **listaEquipe){
    // Guarda o novo item
    TipoEquipe novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuEquipeRecebe(); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printItemEquipe(novo);
        
        if( printConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( equipeAdicionar(listaEquipe, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuEquipeRemover(ListaEquipe **listaEquipe){
    int ID = recebeID(); // recebe o ID do item que vai ser removido
    
    // Busca o Item q vai ser removido
    TipoEquipe *Equipe; // Para guardar resultado de busca
    Equipe = equipeBuscar(*listaEquipe, ID);
    if (Equipe == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Mostra o Item que vai ser removido
    
    printItemEquipe(*Equipe);
    
    
    // Pede confirmacao, se tiver ok, remove o Equipe
    if (printConfirma()){
        equipeRemover(listaEquipe, ID);
        printRemoverSucesso();
    }
}

void menuEquipeAtualizar(ListaEquipe **listaEquipe){
    // Declara um novo item pra receber os dados atualizados
    TipoEquipe novoEquipe;
    TipoEquipe* velhoEquipe;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID();
    velhoEquipe = equipeBuscar(*listaEquipe, ID);

    // Se esse ID n existe, mostra erro
    if (velhoEquipe == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Caso contrario, recebe os novos dados
    novoEquipe = menuEquipeRecebe();

    // ===============================
    // Mostra as mudancas

    // Printa os antigos dados
    printMensagem("Dados Antigos","=");
    
    printItemEquipe(*velhoEquipe);
    
    
    // Printa os novos dados
    printMensagem("Dados Novos","=");
    
    printItemEquipe(novoEquipe);
    
    
    // ===============================
    // Confirma se o usuario realmente quer atualizar
    if (printConfirma()){
        equipeAtualizar(*listaEquipe, novoEquipe, ID);
        printAtualizarSucesso();
    }
}

void menuEquipeBuscar(ListaEquipe **listaEquipe){
    TipoEquipe *Equipe; // Para guardar resultado de busca
    Equipe = equipeBuscar(*listaEquipe, recebeID());
    if (Equipe != NULL){
        
        printItemEquipe(*Equipe);
        
    }
    else printNaoEncontrado();
}

void menuEquipeListar(ListaEquipe *lista) {
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
    int escolha=0;
    do{
        // Exibe o menu de Equipe
        printMenuEquipe();

        // Recebe a escolha do usuario
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha){
            case 1:
                // Adicionar Equipe
                menuEquipeAdicionar(listaEquipe);
                esperaEnter();
                break;
            case 2:
                // Remover Equipe
                menuEquipeRemover(listaEquipe);
                esperaEnter();
                break;
            case 3:
                // Atualizar Equipe
                menuEquipeAtualizar(listaEquipe);
                esperaEnter();
                break;
            case 4:
                // Buscar Equipe
                menuEquipeBuscar(listaEquipe);
                esperaEnter();
                break;
            case 5:
                // Listar Equipes
                menuEquipeListar(*listaEquipe);
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