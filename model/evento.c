#include "evento.h"
#include "fornecedor.h"
#include "cliente.h"
#include "equipe.h"
#include "recurso.h"

void eventoInit(TipoEvento *evento) {
    evento->ativo = true;              // td evento comeca como ativo
    evento->id = 0;                    // id vai ser calculado automaticamente
    evento->idCliente = 0;             // cliente sera atribuido depois
    evento->status = STATUS_ORCAMENTO; // td evento comeca como status de orcamento

    // Atributos comecam vazios pra tirar lixo de memoria
    strcpy(evento->nome,          "");
    strcpy(evento->localEvento,   "");
    strcpy(evento->cidade,        "");
    strcpy(evento->uf,            "");
    strcpy(evento->obs,           "");

    // seta tds os dados de data como 0
    memset(&evento->dataInicio, 0, sizeof(struct tm));
    memset(&evento->dataFim, 0, sizeof(struct tm));

    // seta todos os custos e valores como 0
    evento->custoTotalRecurso = 0.0;
    evento->custoTotalEquipe = 0.0;
    evento->custoTotalFornecedor = 0.0;
    evento->custoTotal = 0.0;
    evento->margemLucro = 0.0;
    evento->valorFinal = 0.0;

    // inicializa listas internas como nulo
    evento->listaRecursos = NULL;
    evento->listaEquipes = NULL;
    evento->listaFornecedores = NULL;
}

void eventoListaInit(ListaEvento *lista) {
    lista->prox = NULL;
    eventoInit(&lista->evento);
}

// ===== CRUD EVENTO =====

ListaEvento* eventoAdicionar(ListaEvento **lista, TipoEvento evento) {
    // adiciona um novo evento na lista e retorna um ponteiro pra ele

    // aloca o espaco para um novo no'
    ListaEvento *novo = (ListaEvento *)malloc(sizeof(ListaEvento));
    if(novo == NULL) return NULL;

    // atribui os dados ao novo no'
    novo->evento = evento;
    novo->evento.ativo = true;
    novo->prox = NULL;

    if(*lista == NULL){ // se a lista estiver vazia, e' so' substituir
        novo->evento.id = 1;
        *lista = novo;
    } else { // se n estiver vazia, percorre ate' o final da lista

        // variavel auxiliar para percorrer a lista
        ListaEvento *atual = *lista;
        // percorre ate' o final da lista
        while(atual->prox != NULL) atual = atual->prox;

        // atribui o ID do novo no' como o ID do ultimo mais um
        novo->evento.id = atual->evento.id + 1;
        // adiciona o novo no' no final da lista
        atual->prox = novo;

    }

    // retorna sucesso
    return novo;
}

int eventoRemover(ListaEvento **lista, int id) {
    // variavel auxiliar para percorrer a lista
    ListaEvento *atual = *lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do evento atual for o id q eu quero, marca como inativo
        if(atual->evento.id == id){
            // libera as listas internas antes de marcar como inativo
            eventoLiberarTodosItens(&atual->evento);
            // marca o evento como inativo
            atual->evento.ativo = false;
            return 1;
        }
        atual = atual->prox;

    }

    // se chegar aqui, n achei o evento
    return 0;
}

int eventoAtualizar(ListaEvento *lista, TipoEvento eventoAtualizado, int id) {
    // variavel auxiliar para percorrer a lista
    ListaEvento *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do evento atual for o id q eu quero, atualiza os dados
        if(atual->evento.id == id){
            atual->evento = eventoAtualizado;
            atual->evento.id = id; // garante q o id n vai ser alterado
            return 1; // sucesso
        }
        atual = atual->prox;
    }

    // se chegar aqui, n achei o evento
    return 0;
}

TipoEvento* eventoBuscar(ListaEvento *lista, int id) {
    // variavel auxiliar para percorrer a lista
    ListaEvento *atual = lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do evento atual for o id q eu quero, retorna os dados
        if(atual->evento.id == id && atual->evento.ativo){
            return &atual->evento;
        }
        atual = atual->prox;
    }

    // se chegar aqui, n achei o evento
    return NULL;
}

void eventoListaLiberar(ListaEvento* lista) {
    //auxiliar pra liberar cada no um por um
    ListaEvento* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (lista != NULL){
        aux = lista;
        // libera as listas internas de cada evento antes de liberar o no
        eventoLiberarTodosItens(&aux->evento);
        lista = lista->prox;
        free(aux);
    }
}

// ========== LIBERAR LISTAS INTERNAS DO EVENTO ==========

void eventoLiberarRecursos(TipoEvento *evento) {
    if (evento == NULL) return;
    ListaRecursoEvento *atual = evento->listaRecursos;
    ListaRecursoEvento *aux;
    while (atual != NULL) {
        aux = atual;
        atual = atual->prox;
        free(aux);
    }
    evento->listaRecursos = NULL;
}

void eventoLiberarEquipes(TipoEvento *evento) {
    if (evento == NULL) return;
    ListaEquipeEvento *atual = evento->listaEquipes;
    ListaEquipeEvento *aux;
    while (atual != NULL) {
        aux = atual;
        atual = atual->prox;
        free(aux);
    }
    evento->listaEquipes = NULL;
}

void eventoLiberarFornecedores(TipoEvento *evento) {
    if (evento == NULL) return;
    ListaFornecedorEvento *atual = evento->listaFornecedores;
    ListaFornecedorEvento *aux;
    while (atual != NULL) {
        aux = atual;
        atual = atual->prox;
        free(aux);
    }
    evento->listaFornecedores = NULL;
}

void eventoLiberarTodosItens(TipoEvento *evento) {
    if (evento == NULL) return;
    eventoLiberarRecursos(evento);
    eventoLiberarEquipes(evento);
    eventoLiberarFornecedores(evento);
}

// ========== EDITAR CAMPOS DO EVENTO ==========

int eventoSetDatas(TipoEvento *evento, struct tm dataInicio, struct tm dataFim) {
    if (evento == NULL) return 0;
    evento->dataInicio = dataInicio;
    evento->dataFim = dataFim;
    return 1;
}

// ========== AUXILIARES PARA A INSERCAO ==========

int recursoContarUsoPeriodo(ListaEvento *listaEventos, int idRecurso, struct tm inicioConsulta, struct tm fimConsulta){
    // ainda n achou nenhum
    int total = 0;

    // percorre todos os eventos
    for (ListaEvento *aux = listaEventos; aux; aux = aux->prox) {

        // pega o evento da vez
        TipoEvento *evento = &aux->evento;

        // se o evento n bate com a consulta, ignora
        if (!periodosConflitam(evento->dataInicio, evento->dataFim, inicioConsulta, fimConsulta))
            continue;

        // caso contrario, percorre os recursos do evento
        for (ListaRecursoEvento *r = evento->listaRecursos; r; r = r->prox) {

            // se achei o recurso, soma a quantidade usada
            if (r->item.idRecurso == idRecurso) 
                total += r->item.qtd;

        }
    }

    return total;
}

int equipeEstaAlocadaPeriodo(ListaEvento *listaEventos, int idEquipe, struct tm inicioConsulta, struct tm fimConsulta){
    // percorre todos os eventos
    for (ListaEvento *aux = listaEventos; aux; aux = aux->prox) {

        // pega o evento da vez
        TipoEvento *evento = &aux->evento;

        // se o evento n bate com a consulta, ignora
        if (!periodosConflitam(evento->dataInicio, evento->dataFim, inicioConsulta, fimConsulta))
            continue;

        // caso contrario, percorre as equipes do evento
        for (ListaEquipeEvento *e = evento->listaEquipes; e; e = e->prox) {

            // se achei a equipe, retorna verdadeiro
            if (e->item.idEquipe == idEquipe) 
                return 1;

        }
    }

    return 0;
}

// ========== OPERACOES DAS LISTAS INTERNAS ==========

//=================
// RECURSO
int eventoAdicionarRecurso(TipoEvento *evento, ItemRecursoEvento item) {
    // se n tem evento n tem como adicionar
    if (evento == NULL) return 0;

    // cria o novo no
    ListaRecursoEvento *novo = (ListaRecursoEvento *)malloc(sizeof(ListaRecursoEvento));
    if (novo == NULL) return 0;

    // atribui os dados
    novo->item = item;
    novo->prox = NULL;

    // adiciona no final da lista
    if (evento->listaRecursos == NULL) {
        // se tiver vazia coloca no comeco
        evento->listaRecursos = novo;
    } else {
        // percorre ate o final
        ListaRecursoEvento *atual = evento->listaRecursos;
        while (atual->prox != NULL) atual = atual->prox;
        atual->prox = novo;
    }

    eventoCalcularTotal(evento);
    return 1;
}

ItemRecursoEvento* eventoBuscarRecurso(TipoEvento *evento, int idRecurso) {
    if (evento == NULL) return NULL;
    ListaRecursoEvento *atual = evento->listaRecursos;
    while (atual != NULL) {
        if (atual->item.idRecurso == idRecurso) return &atual->item;
        atual = atual->prox;
    }
    return NULL;
}

int eventoRemoverRecurso(TipoEvento *evento, int idRecurso) {
    if (evento == NULL) return 0;
    ListaRecursoEvento *atual = evento->listaRecursos;
    ListaRecursoEvento *prev = NULL;
    while (atual != NULL) {
        if (atual->item.idRecurso == idRecurso) {
            if (prev == NULL) evento->listaRecursos = atual->prox;
            else prev->prox = atual->prox;
            free(atual);
            eventoCalcularTotal(evento);
            return 1;
        }
        prev = atual;
        atual = atual->prox;
    }
    return 0;
}

//=================
// EQUIPE
int eventoAdicionarEquipe(TipoEvento *evento, ItemEquipeEvento item) {
    if (evento == NULL) return 0;

    ListaEquipeEvento *novo = (ListaEquipeEvento *)malloc(sizeof(ListaEquipeEvento));
    if (novo == NULL) return 0;
    novo->item = item;
    novo->prox = NULL;

    if (evento->listaEquipes == NULL) evento->listaEquipes = novo;
    else {
        ListaEquipeEvento *atual = evento->listaEquipes;
        while (atual->prox != NULL) atual = atual->prox;
        atual->prox = novo;
    }

    eventoCalcularTotal(evento);
    return 1;
}

ItemEquipeEvento* eventoBuscarEquipe(TipoEvento *evento, int idEquipe) {
    if (evento == NULL) return NULL;
    ListaEquipeEvento *atual = evento->listaEquipes;
    while (atual != NULL) {
        if (atual->item.idEquipe == idEquipe) return &atual->item;
        atual = atual->prox;
    }
    return NULL;
}

int eventoRemoverEquipe(TipoEvento *evento, int idEquipe) {
    if (evento == NULL) return 0;
    ListaEquipeEvento *atual = evento->listaEquipes;
    ListaEquipeEvento *prev = NULL;
    while (atual != NULL) {
        if (atual->item.idEquipe == idEquipe) {
            if (prev == NULL) evento->listaEquipes = atual->prox;
            else prev->prox = atual->prox;
            free(atual);
            eventoCalcularTotal(evento);
            return 1;
        }
        prev = atual;
        atual = atual->prox;
    }
    return 0;
}

//=================
// FORNECEDOR
int eventoAdicionarFornecedor(TipoEvento *evento, ItemFornecedorEvento item) {
    if (evento == NULL) return 0;

    ListaFornecedorEvento *novo = (ListaFornecedorEvento *)malloc(sizeof(ListaFornecedorEvento));
    if (novo == NULL) return 0;
    novo->item = item;
    novo->prox = NULL;

    if (evento->listaFornecedores == NULL) evento->listaFornecedores = novo;
    else {
        ListaFornecedorEvento *atual = evento->listaFornecedores;
        while (atual->prox != NULL) atual = atual->prox;
        atual->prox = novo;
    }

    eventoCalcularTotal(evento);
    return 1;
}

ItemFornecedorEvento* eventoBuscarFornecedor(TipoEvento *evento, int idFornecedor) {
    if (evento == NULL) return NULL;
    ListaFornecedorEvento *atual = evento->listaFornecedores;
    while (atual != NULL) {
        if (atual->item.idFornecedor == idFornecedor) return &atual->item;
        atual = atual->prox;
    }
    return NULL;
}

int eventoRemoverFornecedor(TipoEvento *evento, int idFornecedor) {
    if (evento == NULL) return 0;
    ListaFornecedorEvento *atual = evento->listaFornecedores;
    ListaFornecedorEvento *prev = NULL;
    while (atual != NULL) {
        if (atual->item.idFornecedor == idFornecedor) {
            if (prev == NULL) evento->listaFornecedores = atual->prox;
            else prev->prox = atual->prox;
            free(atual);
            eventoCalcularTotal(evento);
            return 1;
        }
        prev = atual;
        atual = atual->prox;
    }
    return 0;
}

//=========== MUDANCA DE STATUS ===========

int eventoAprovar(TipoEvento *evento) {
    if (evento == NULL) return 0;
    evento->status = STATUS_APROVADO;
    return 1;
}

int eventoFinalizar(TipoEvento *evento) {
    if (evento == NULL) return 0;
    evento->status = STATUS_FINALIZADO;
    return 1;
}

int eventoCancelar(TipoEvento *evento) {
    if (evento == NULL) return 0;
    evento->status = STATUS_CANCELADO;
    return 1;
}

int eventoOrcamento(TipoEvento *evento) {
    if (evento == NULL) return 0;
    evento->status = STATUS_ORCAMENTO;
    return 1;
}

//=========== CALCULOS DOS PRECOS ===========

double eventoCalcularTotalRecursos(TipoEvento *evento) {
    // Inicia como 0
    double total = 0.0;

    // aux pra percorrer a lista
    ListaRecursoEvento *aux = evento->listaRecursos;
    while (aux != NULL) {
        // calcula o total de cada item, considerando seu preco unitario, a qtd e o tempo q ficou com ele
        aux->item.precoTotal = aux->item.precoUnitario * aux->item.qtd * aux->item.qtdTempo;

        // ajusta o total
        total += aux->item.precoTotal;

        // avanca pro proximo item
        aux = aux->prox;
    }

    // ajusta e retorna o total de tds os itens
    evento->custoTotalRecurso = total;
    return total;
}

double eventoCalcularTotalEquipes(TipoEvento *evento) {
    // Inicia como 0
    double total = 0.0;

    // aux pra percorrer a lista
    ListaEquipeEvento *aux = evento->listaEquipes;
    while (aux != NULL) {

        // decide oq vai fzr, depende do tipo
        switch (aux->item.precoTipo) {
            case 0: // Fixo     - so' coloca o preco fixo no total
                aux->item.precoTotal = aux->item.precoValor;
                break;

            case 1: // Por hora - multiplica pela qtd de tempo, em hrs
                aux->item.precoTotal = aux->item.precoValor * aux->item.qtdTempo;
                break;

            case 2: // Por dia  - multiplica pela qtd de tempo, em dias
                aux->item.precoTotal = aux->item.precoValor * aux->item.qtdTempo;
                break;

            default: // Se o tipo n ta definido, coloca 0 pq n tem oq fzr
                aux->item.precoTotal = 0.0;
                break;
        }

        // pra cada item, adiciona no total
        total += aux->item.precoTotal;

        // avanca pro proximo item
        aux = aux->prox;
    }

    // ajusta e retorna o total de tds os itens
    evento->custoTotalEquipe = total;
    return total;
}

double eventoCalcularTotalFornecedores(TipoEvento *evento) {
    // Inicia como 0
    double total = 0.0;

    // aux pra percorrer a lista
    ListaFornecedorEvento *aux = evento->listaFornecedores;
    while (aux != NULL) {

        // decide oq vai fzr, depende do tipo
        switch (aux->item.precoTipo) {
            case 0: // Fixo     - so' coloca o preco fixo no total
                aux->item.precoTotal = aux->item.precoValor;
                break;

            case 1: // Por hora - multiplica pela qtd de tempo, em hrs
                aux->item.precoTotal = aux->item.precoValor * aux->item.qtdTempo;
                break;

            case 2: // Por dia  - multiplica pela qtd de tempo, em dias
                aux->item.precoTotal = aux->item.precoValor * aux->item.qtdTempo;
                break;

            default: // Se o tipo n ta definido, coloca 0 pq n tem oq fzr
                aux->item.precoTotal = 0.0;
                break;
        }

        // pra cada item, adiciona no total
        total += aux->item.precoTotal;

        // avanca pro proximo item
        aux = aux->prox;
    }

    // ajusta e retorna o total de tds os itens
    evento->custoTotalFornecedor = total;
    return total;
}

void eventoCalcularTotal(TipoEvento *evento) {
    // Calcula os custos individuais
    eventoCalcularTotalRecursos(evento);
    eventoCalcularTotalEquipes(evento);
    eventoCalcularTotalFornecedores(evento);

    // Custo total do evento
    evento->custoTotal = evento->custoTotalRecurso 
                        + evento->custoTotalEquipe
                        + evento->custoTotalFornecedor;

    // Custo a mandar pro cliente, contando a margem de lucro
    evento->valorFinal = evento->custoTotal + (evento->custoTotal + evento->margemLucro);
}

//==================================================
// Arquivos

// TXT
// Salva uma linha individual em txt
void eventoSalvarTXTLinha(FILE *f, TipoEvento *evento){
    fprintf(f,
        "E,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%s\n",
        evento->id,
        evento->idCliente,
        evento->ativo,
        evento->nome,

        evento->status,

        evento->dataInicio.tm_mday,
        evento->dataInicio.tm_mon,
        evento->dataInicio.tm_year,

        evento->dataFim.tm_mday,
        evento->dataFim.tm_mon,
        evento->dataFim.tm_year,

        evento->localEvento,
        evento->cidade,
        evento->uf,

        evento->custoTotalRecurso,
        evento->custoTotalEquipe,
        evento->custoTotalFornecedor,
        evento->custoTotal,
        evento->margemLucro,
        evento->obs
    );
}

void eventoSalvarTXTRecurso(FILE *f, ItemRecursoEvento *item){
    fprintf(f, "R,%d,%d,%d,%.2f,%.2f\n",
        item->idRecurso,
        item->qtdTempo,
        item->qtd,
        item->precoUnitario,
        item->precoTotal);
}

void eventoSalvarTXTEquipe(FILE *f, ItemEquipeEvento *item){
    fprintf(f, "Q,%d,%d,%d,%.2f,%.2f\n",
        item->idEquipe,
        item->qtdTempo,
        item->precoTipo,
        item->precoValor,
        item->precoTotal);
}

void eventoSalvarTXTFornecedor(FILE *f, ItemFornecedorEvento *item){
    fprintf(f, "F,%d,%d,%d,%.2f,%.2f\n",
        item->idFornecedor,
        item->qtdTempo,
        item->precoTipo,
        item->precoValor,
        item->precoTotal);
}

// Salva o evento todo em TXT
void eventoSalvarTXT(ListaEvento *lista){
    // abre o arquivo
    FILE *f = fopen("dados/evento.txt", "w");
    if (!f) return;

    // percorre a lista toda
    for (ListaEvento *aux = lista; aux; aux = aux->prox){

        // variavel auxiliar do evento da vez
        TipoEvento *evento = &aux->evento;

        // salva o evento em si
        eventoSalvarTXTLinha(f, evento);

        // Salva todos os recursos do evento
        for (ListaRecursoEvento *recurso = evento->listaRecursos; recurso; recurso = recurso->prox)
            eventoSalvarTXTRecurso(f, &recurso->item);

        // salva tds as equipes do evento
        for (ListaEquipeEvento *equipe = evento->listaEquipes; equipe; equipe = equipe->prox)
            eventoSalvarTXTEquipe(f, &equipe->item);

        // salva todos os fornecedores do evento
        for (ListaFornecedorEvento *fornecedor = evento->listaFornecedores; fornecedor; fornecedor = fornecedor->prox)
            eventoSalvarTXTFornecedor(f, &fornecedor->item);
    }

    fclose(f);
}

// Le uma linha individual em txt
void eventoLerTXTLinha(char *linha, TipoEvento *evento) {
    sscanf(linha,
        "E,%d,%d,%d,%99[^,],%d,%d,%d,%d,%d,%d,%d,%149[^,],%49[^,],%3[^,],%lf,%lf,%lf,%lf,%lf,%499[^\n]",
        &evento->id,                     // id do evento
        &evento->idCliente,              // id do cliente associado ao evento
        (int*)&evento->ativo,            // se o evento ta ativo ou n (como e' um bool, precisa transformar em int pro compilador n reclamar)
        evento->nome,                    // nome do evento em si
        (int*)&evento->status,           // status do evento (como e' um bool, precisa transformar em int pro compilador n reclamar)
        &evento->dataInicio.tm_mday,     // data: dia do mes q comecou
        &evento->dataInicio.tm_mon,      // data: mes q comecou 
        &evento->dataInicio.tm_year,     // data: ano q comecou
        &evento->dataFim.tm_mday,        // data: dia do mes q comecou
        &evento->dataFim.tm_mon,         // data: mes q acabou
        &evento->dataFim.tm_year,        // data: ano q acabou
        evento->localEvento,             // lugar q vai rolar o evento
        evento->cidade,                  // cidade q vai rolar o evento
        evento->uf,                      // unidade federal q vai ter o evento
        &evento->custoTotalRecurso,      // total em recursos
        &evento->custoTotalEquipe,       // total em equipes
        &evento->custoTotalFornecedor,   // total em fornecedores
        &evento->custoTotal,             // custo total
        &evento->margemLucro,            // margem de lucro do projeto
        evento->obs                      // observacoes se tiver
    );
}

void eventoLerTXTRecurso(char *linha, ItemRecursoEvento *item) {
    sscanf(linha, "R,%d,%d,%d,%f,%f",
           &item->idRecurso,
           &item->qtdTempo,
           &item->qtd,
           &item->precoUnitario,
           &item->precoTotal);
}

void eventoLerTXTEquipe(char *linha, ItemEquipeEvento *item) {
    sscanf(linha, "Q,%d,%d,%d,%f,%f",
           &item->idEquipe,
           &item->qtdTempo,
           &item->precoTipo,
           &item->precoValor,
           &item->precoTotal);
}

void eventoLerTXTFornecedor(char *linha, ItemFornecedorEvento *item) {
    sscanf(linha, "F,%d,%d,%d,%f,%f",
           &item->idFornecedor,
           &item->qtdTempo,
           &item->precoTipo,
           &item->precoValor,
           &item->precoTotal);
}

// Le o evento todo em TXT
int eventoLerTXT(ListaEvento **lista) {

    FILE *f = fopen("dados/evento.txt", "r");
    if (!f) return 0;

    // buffer pra ler a linha toda
    char linha[2048];
    // guarda o ultimo evento que foi lido
    //  - td equipe, recurso e fornecedor vai ser adicionado nele
    ListaEvento *ultimo = NULL;

    // percorre todas as linhas ate chegar uma q n da pra ler mais
    while (fgets(linha, sizeof(linha), f)) {

        // LINHA DE EVENTO
        if (linha[0] == 'E') {
            // declara um evento temporario
            TipoEvento evento;
            // seta tudo como 0 a principio
            memset(&evento, 0, sizeof(TipoEvento));

            // realmente le a linha
            eventoLerTXTLinha(linha, &evento);

            // inicia as listas como nulas
            evento.listaRecursos = NULL;
            evento.listaEquipes = NULL;
            evento.listaFornecedores = NULL;

            // adiciona o evento na lista e coloca esse evento como ultimo
            ultimo = eventoAdicionar(lista, evento);
        }

        // RECURSO
        else if (linha[0] == 'R' && ultimo != NULL) {
            // declara um item temporario
            ItemRecursoEvento item;
            // le a linha
            eventoLerTXTRecurso(linha, &item);
            // adiciona o item na lista do ultimo evento lido
            eventoAdicionarRecurso(&ultimo->evento, item);
        }

        // EQUIPE
        else if (linha[0] == 'Q' && ultimo != NULL) {
            // declara um item temporario
            ItemEquipeEvento item;
            // le a linha
            eventoLerTXTEquipe(linha, &item);
            // adiciona o item na lista do ultimo evento lido
            eventoAdicionarEquipe(&ultimo->evento, item);
        }

        // FORNECEDOR
        else if (linha[0] == 'F' && ultimo != NULL) {
            // declara um item temporario
            ItemFornecedorEvento item;
            // le a linha
            eventoLerTXTFornecedor(linha, &item);
            // adiciona o item na lista do ultimo evento lido
            eventoAdicionarFornecedor(&ultimo->evento, item);
        }
    }

    fclose(f);
    return 1;
}

// BIN
int eventoSalvarBIN(ListaEvento *lista) {
    // abre o arquivo
    FILE *f = fopen("dados/evento.bin", "wb");
    if (!f) return 0;

    // percorre a lista toda pra salvar todos
    for (ListaEvento *aux = lista; aux; aux = aux->prox) {
        // evento auxiliar da vez
        TipoEvento *evento = &aux->evento;

        // Slava o evento em si
        char tag = 'E';
        fwrite(&tag, sizeof(char), 1, f);
        fwrite(evento, sizeof(TipoEvento), 1, f);

        // percorre os recursos, salvando eles um por um
        for (ListaRecursoEvento *recurso = evento->listaRecursos ; recurso ; recurso = recurso->prox) {
            tag = 'R';
            fwrite(&tag, sizeof(char), 1, f);
            fwrite(&recurso->item, sizeof(ItemRecursoEvento), 1, f);
        }

        // percorre as equipés, salvando eles um por um
        for (ListaEquipeEvento *equipe = evento->listaEquipes ; equipe ; equipe = equipe->prox) {
            tag = 'Q';
            fwrite(&tag, sizeof(char), 1, f);
            fwrite(&equipe->item, sizeof(ItemEquipeEvento), 1, f);
        }

        // percorre os fornecedores, salvando eles um por um
        for (ListaFornecedorEvento *fornecedor = evento->listaFornecedores ; fornecedor; fornecedor = fornecedor->prox) {
            tag = 'F';
            fwrite(&tag, sizeof(char), 1, f);
            fwrite(&fornecedor->item, sizeof(ItemFornecedorEvento), 1, f);
        }
    }

    fclose(f);
    return 1;
}

int eventoLerBIN(ListaEvento **lista) {
    // abre o arquivo
    FILE *f = fopen("dados/evento.bin", "rb");
    if (!f) return 0;

    char tag;                   // pra guardar a tag q achei
    ListaEvento *ultimo = NULL; // pra guardar o ultimo evento, itens vao ser adicionados nele

    while (fread(&tag, sizeof(char), 1, f)) {

        // LINHA DE EVENTO
        if (tag == 'E') {
            // declara um evento temporario
            TipoEvento evento;

            // realmente le a linha
            fread(&evento, sizeof(TipoEvento), 1, f);
            
            // inicia as listas como nulas
            evento.listaRecursos = NULL;
            evento.listaEquipes = NULL;
            evento.listaFornecedores = NULL;

            // adiciona o evento na lista e coloca esse evento como ultimo
            ultimo = eventoAdicionar(lista, evento);
        }
        
        // RECURSO
        else if (tag == 'R' && ultimo != NULL) {
            // declara um item temporario
            ItemRecursoEvento item;
            // le a linha
            fread(&item, sizeof(ItemRecursoEvento), 1, f);
            // adiciona o item na lista do ultimo evento lido
            eventoAdicionarRecurso(&ultimo->evento, item);
        }

        // EQUIPE
        else if (tag == 'Q' && ultimo != NULL) {
            // declara um item temporario
            ItemEquipeEvento item;
            // le a linha
            fread(&item, sizeof(ItemEquipeEvento), 1, f);
            // adiciona o item na lista do ultimo evento lido
            eventoAdicionarEquipe(&ultimo->evento, item);
        }

        // FORNECEDOR
        else if (tag == 'F' && ultimo != NULL) {
            // declara um item temporario
            ItemFornecedorEvento item;
            // le a linha
            fread(&item, sizeof(ItemFornecedorEvento), 1, f);
            // adiciona o item na lista do ultimo evento lido
            eventoAdicionarFornecedor(&ultimo->evento, item);
        }
    }

    fclose(f);
    return 1;
}
