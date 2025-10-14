#include "menuProdutora.h"

TipoProdutora menuProdutoraRecebe() {
    // Recebe uma nova Produtora do usuario e retorna a produtora preenchida
    TipoProdutora produtora;
    produtoraInit(&produtora);

    // Recebe os dados da produtora
    produtora.id = 0; // ID sera atribuido automaticamente
    recebeString(produtora.nomeFantasia, 100, "Digite o Nome Fantasia","Max. 100");
    recebeString(produtora.razaoSocial, 100, "Digite a Razao Social","Max. 100");
    recebeString(produtora.inscricaoEstadual, 20, "Digite a Razao Social","9 Digitos");
    recebeCNPJ(produtora.cnpj);
    recebeString(produtora.endereco, 100, "Digite o Endereco","Max. 100");
    recebeTelefone(produtora.cnpj);
    recebeEmail(produtora.email);
    recebeString(produtora.nomeDoResponsavel, 100, "Digite o Nome do Responsavel","Max. 100");
    recebeString(produtora.telefoneDoResponsavel, 11, "Digite o Telefone do Responsavel","10 ou 11 Digitos");
    produtora.margemDeLucro = recebeFloat(0, 1000000, "Digite a Margem de Lucro", "Entre 0 e 1m");

    return produtora;
}

void menuProdutoraAdicionar(ListaProdutora **listaProdutora){
    // Guarda o novo item
    TipoProdutora novo;

    // Enquanto o usuario nao confirmar, roda dnv
    while (1){
        novo = menuProdutoraRecebe(); // Recebe os valroes do usuario
        
        // Mostra os dados que foram inseridos
        printItemProdutora(novo);
        
        if( printConfirma() ) break;  // Pergunta o usuario se ta td certo
    }
    
    // Realmente adiciona na lista
    if ( produtoraAdicionar(listaProdutora, novo) ) printAdicionarSucesso();
    else printAdicionarFalha();
}

void menuProdutoraRemover(ListaProdutora **listaProdutora){
    int ID = recebeID(); // recebe o ID do item que vai ser removido
    
    // Busca o Item q vai ser removido
    TipoProdutora *Produtora; // Para guardar resultado de busca
    Produtora = produtoraBuscar(*listaProdutora, ID);
    if (Produtora == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Mostra o Item que vai ser removido
    
    printItemProdutora(*Produtora);
    
    
    // Pede confirmacao, se tiver ok, remove o Produtora
    if (printConfirma()){
        produtoraRemover(listaProdutora, ID);
        printRemoverSucesso();
    }
}

void menuProdutoraAtualizar(ListaProdutora **listaProdutora){
    // Declara um novo item pra receber os dados atualizados
    TipoProdutora novoProdutora;
    TipoProdutora* velhoProdutora;

    // Recebe o ID do item que vai ser atualizado
    int ID = recebeID();
    velhoProdutora = produtoraBuscar(*listaProdutora, ID);

    // Se esse ID n existe, mostra erro
    if (velhoProdutora == NULL){
        printNaoEncontrado();
        return;
    }
    
    // Caso contrario, recebe os novos dados
    novoProdutora = menuProdutoraRecebe();

    // ===============================
    // Mostra as mudancas

    // Printa os antigos dados
    printMensagem("Dados Antigos","=");
    
    printItemProdutora(*velhoProdutora);
    
    
    // Printa os novos dados
    printMensagem("Dados Novos","=");
    
    printItemProdutora(novoProdutora);
    
    
    // ===============================
    // Confirma se o usuario realmente quer atualizar
    if (printConfirma()){
        produtoraAtualizar(*listaProdutora, novoProdutora, ID);
        printAtualizarSucesso();
    }
}

void menuProdutoraBuscar(ListaProdutora **listaProdutora){
    TipoProdutora *Produtora; // Para guardar resultado de busca
    Produtora = produtoraBuscar(*listaProdutora, recebeID());
    if (Produtora != NULL){
        
        printItemProdutora(*Produtora);
        
    }
    else printNaoEncontrado();
}

void menuProdutoraListar(ListaProdutora *lista) {
    limparTela();

    // Lista todas as produtoras cadastradas
    if (lista == NULL) {
        printf("\n => Nenhuma produtora cadastrada.\n");
        return;
    }

    
    ListaProdutora *atual = lista->prox; // Pula o no' cabeca
    while (atual != NULL) {
        // Se Item estiver ativo, printa
        if (atual->produtora.ativo) printItemProdutora(atual->produtora);
        atual = atual->prox;
    }
    
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

        switch (escolha){
            case 1:
                // Adicionar Produtora
                menuProdutoraAdicionar(listaProdutora);
                esperaEnter();
                break;
            case 2:
                // Remover Produtora
                menuProdutoraRemover(listaProdutora);
                esperaEnter();
                break;
            case 3:
                // Atualizar Produtora
                menuProdutoraAtualizar(listaProdutora);
                esperaEnter();
                break;
            case 4:
                // Buscar Produtora
                menuProdutoraBuscar(listaProdutora);
                esperaEnter();
                break;
            case 5:
                // Listar Produtoras
                menuProdutoraListar(*listaProdutora);
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