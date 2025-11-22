#include "evento.h"

#include "cliente.h"
#include "equipe.h"

void eventoInit(TipoEvento *evento) {
    evento->ativo = true;     // por padrao inciar ativo
    evento->id = 0;           // id incrementa automaticamente

    // Atributos comecam vazios pra tirar lixo de memoria
    strcpy(evento->nome,                "");
    evento->codigoCliente = 0;

    memset(&evento->dataInicio, 0, sizeof(struct tm));
    memset(&evento->dataFim, 0,     sizeof(struct tm));
    strcpy(evento->localEvento,         "");
    strcpy(evento->cidade,              "");
    strcpy(evento->uf,                  "");

    evento->status = STATUS_ORCAMENTO;

    evento->listaRecursos = NULL;
    evento->listaEquipes = NULL;
    evento->listaFornecedores = NULL;

    evento->custoTotalRecursos = 0.0;
    evento->custoTotalEquipe = 0.0;
    evento->custoTotalForn = 0.0;
    evento->custoTotal = 0.0;

    strcpy(evento->obs,             "");
}
void eventoListaInit(ListaEvento **listaEvento) {
    *listaEvento = NULL;
}
//
// void recursoEventoListaInit(ItemRecursoEvento *listaRecursos){
//     listaRecursos->prox = NULL;
//     recursoEventoListaInit(&listaRecursos->evento);
// }
//
// void equipeEventoListaInit(ItemEquipeEvento *listaEquipes){
//     listaEquipes->prox = NULL;
//     equipeEventoListaInit(&listaEquipes->evento);
// }

// void fornecedorEventoListaInit(ItemFornecedorEvento *listaFornecedores){
    // listaFornecedores->prox = NULL;
    // fornecedorEventoListaInit(&listaFornecedores->evento);
//}
// ===== CRUD EVENTTO =====

int eventoAdicionar(ListaEvento **listaEvento, TipoEvento evento){
    // aloca o espaco para um novo no'
    ListaEvento *novo = (ListaEvento *)malloc(sizeof(ListaEvento));
    if(novo == NULL) return 0;

    // atribui os dados ao novo no'
    novo->evento = evento;
    novo->evento.ativo = true;
    novo->prox = NULL;

    if(*listaEvento == NULL){ // se a lista estiver vazia, e' so' substituir
        novo->evento.id = 1;
        *listaEvento = novo;
    } else { // se n estiver vazia, percorre ate' o final da lista

        // variavel auxiliar para percorrer a lista
        ListaEvento *atual = *listaEvento;
        // percorre ate' o final da lista
        while(atual->prox != NULL) atual = atual->prox;

        // atribui o ID do novo no' como o ID do ultimo mais um
        novo->evento.id = atual->evento.id + 1;
        // adiciona o novo no' no final da lista
        atual->prox = novo;

    }

    // retorna sucesso
    return 1;

}

int eventoRemover(ListaEvento **listaEvento, int id){
    // variavel auxiliar para percorrer a lista
    ListaEvento *atual = *listaEvento;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do cliente atual for o id q eu quero, marca como inativo
        if(atual->evento.id == id){
            // marca o cliente como inativo
            atual->evento.ativo = false;
            return 1;
        }
        atual = atual->prox;
    }

    // se chegar aqui, n achei o cliente
    return 0;
}

int eventoAtualizar(ListaEvento *listaEvento, TipoEvento eventoAtualizado, int id) {
    ListaEvento *atual = listaEvento;

    while (atual != NULL) {
        if (atual->evento.id == id) {
            // Guarda os ponteiros das listas encadeadas
            ListaRecurso *recursos = atual->evento.listaRecursos;
            ListaEquipeEvento *equipes = atual->evento.listaEquipes;
            ListaFornecedorEvento *fornecedores = atual->evento.listaFornecedores;

            // Atualiza os dados do evento
            atual->evento = eventoAtualizado;
            atual->evento.id = id; // mantém o ID

            // Restaura os ponteiros das listas
            atual->evento.listaRecursos = recursos;
            atual->evento.listaEquipes = equipes;
            atual->evento.listaFornecedores = fornecedores;

            return 1; // sucesso
        }
        atual = atual->prox;
    }
    return 0; // evento não encontrado
}
TipoEvento* eventoBuscar(ListaEvento *listaEvento, int id){
    // variavel auxiliar para percorrer a lista
    ListaEvento *atual = listaEvento;

    while(atual != NULL){
        if(atual->evento.id == id){
            return &atual->evento;
        }
        atual = atual->prox;
    }

    // n foi encontrado
    return NULL;
}

void eventoListaLiberar(ListaEvento *listaEvento) {
    ListaEvento *aux = listaEvento;

    while (listaEvento != NULL) {
        aux = listaEvento;
        listaEvento = listaEvento->prox; // atualiza aux antes de liberrar p/ o prox no
        // Libera as listas internas
        eventoLiberarRecursos(aux->evento.listaRecursos);
        eventoLiberarEquipes(aux->evento.listaEquipes);
        eventoLiberarFornecedores(aux->evento.listaFornecedores);

        listaEvento = listaEvento->prox;
        free(aux);
        aux = NULL; // previnir incertezas
    }
}

//=========== GESTAO DOS RECURSOS ===========
int eventoAdicionarRecurso(TipoEvento *evento, ItemRecursoEvento item) {
    ListaRecurso *novo = (ListaRecurso *)malloc(sizeof(ListaRecurso));
    if (novo == NULL) return 0;

    novo->item = item;
    novo->prox = NULL;

    if (evento->listaRecursos == NULL){
        evento->listaRecursos = novo;
    }else {
        ListaRecurso *atual = evento->listaRecursos;
        while(atual->prox != NULL) { //acesso valido na memoria qnd atual->prox for null
            atual = atual->prox;
        }
        atual->prox = novo; // apos o ult no insere
    }
    eventoRecalcularTotais(evento);
    return 1;
}

int eventoRemoveRecurso(TipoEvento *evento, int codigoRecurso) {
    ListaRecurso *atual = evento->listaRecursos;
    ListaRecurso *anterior = NULL;

    while (atual != NULL) {
        if (atual->item.codigoRecurso == codigoRecurso) {
            if (anterior == NULL) {
                evento->listaRecursos = atual->prox;
            }
            free(atual);

            eventoRecalcularTotais(evento);
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

ItemRecursoEvento* eventoBuscarRecurso(TipoEvento *evento, int codigoRecurso) {
    ListaRecurso *atual = evento->listaRecursos;

    while (atual != NULL) {
        if (atual ->item.codigoRecurso == codigoRecurso) {
            return &atual->item;
        }
        atual = atual->prox;
    }
    return NULL;
}

void eventoLiberarRecurso(ListaRecursoEvento *listaRecurso) {
    while (listaRecurso != NULL) {
        ListaRecursoEvento *aux = listaRecurso;
        listaRecurso = listaRecurso->prox;
        free(aux);
    }
}
//=========== GESTAO DA EQUIPE ===========

int eventoAdicionarEquipe(TipoEvento *evento, ItemEquipeEvento) {
    ListaEquipe * novo = (ListaEquipe *)malloc(sizeof(ListaEquipe));
    if (novo == NULL) return 0;

    novo->item = item;
    novo->prox = NULL;
}

//=========== GESTAO DOS FORNECEDORES ===========

//=========== METODOS DOS CALCULOS ===========
double eventoCalcularTotalRecursos(TipoEvento *evento);
double eventoCalcularTotalEquipe(TipoEvento *evento);
double eventoCalcularTotalFornecedores(TipoEvento *evento);
void eventoRecalcularTotais(TipoEvento *evento);

//=========== ARQUIVOS DO EVENTO ===========
int eventoSalvarTXT(TipoEvento *evento) {
    FILE *arquivo = fopen("dados/evento.txt", "w");
    if (arquivo == NULL) return 0;

    ListaEvento *atual = listaEvento;

    while(atual != NULL) {
        if (atual->evento.ativo){

            fprintf(arquivo, "%d|%s|%d|%s|%s|%s|%s|%s|%s|%s|%d|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%s\n",
                            atual->evento.id,
                            atual->evento.nome,
                            atual->evento.codigoCliente,
                            atual->evento.dataInicio,
                            atual->evento.dataFim,
                            atual->evento.localEvento,
                            atual->evento.cidade,
                            atual->evento.uf,
                            atual->evento.status,
                            atual->evento.custo_total_recursos,
                            atual->evento.custo_total_equipe,
                            atual->evento.custo_total_fornecedores,
                            atual->evento.custo_total,
                            atual->evento.margem_lucro_percentual,
                            atual->evento.valor_total_evento,
                            atual->evento.obs);
             }
        atual = atual->prox;
    }

    fclose(arquivo);
    return 1;
}


int eventoLerTXT(ListaEvento **listaEvento) {
    FILE *arquivo = fopen("dados/evento.txt", "r");
    if (arquivo == NULL) return 0;

    TipoEvento temp = {0};
    int status_int;

    while (fscanf(arquivo, "%d|%99[^|]|%d|%10[^|]|%10[^|]|%199[^|]|%49[^|]|%2[^|]|%d|%f|%f|%f|%f|%f|%f|%499[^\n]\n",
                  &temp.id,
                  temp.nome,
                  &temp.codigoCliente,
                  temp.dataInicio = (struct tm){0},
                  temp.dataFim = (struct tm){0},
                  temp.localEvento,
                  temp.cidade,
                  temp.uf,
                  &status_int,
                  &temp.custoTotalRecursos,
                  &temp.custoTotalEquipe,
                  &temp.custoTotalForn,
                  &temp.custoTotal,
                  &temp.margemLucro,
                  &temp.valorFinal,
                  temp.obs) == 18) {

        temp.ativo = 1;
        temp.status = (StatusEvento)status_int;
        temp.listaRecursos = NULL;
        temp.listaEquipes = NULL;
        temp.listaFornecedores = NULL;

        eventoAdicionar(listaEvento, temp);
                  }

    fclose(arquivo);
    return 1;
}

int eventoLerBIN(TipoEvento **listaEvento) {
    FILE *arquivo = fopen("dados/evento.bin", "rb");
    if (arquivo == NULL) return 0;

    TipoEvento temp = {0};

    // conferir se os nomes estao corretos ou se confudi listaRecursos p/ lista_recursos
    while (fread(&temp, sizeof(TipoEvento), 1, arquivo) == 1) {
        // zerar ponteiros da lista para evitar lixo
        temp.listaRecursos = NULL;
        temp.listaEquipes = NULL;
        temp.listaFornecedores = NULL;

            eventoAdicionar(listaEvento, temp);
        }

    fclose(arquivo);
    return 1;
}