#include "evento.h"

#include "cliente.h"

void eventoInit(TipoEvento *evento) {
    evento->ativo = true;     // por padrao inciar ativo
    evento->id = 0;           // id incrementa automaticamente

    // Atributos comecam vazios pra tirar lixo de memoria
    strcpy(evento->nome,                "-");
    evento->codigoCliente = 0;

    strcpy(evento->dataInicio,          "-");
    strcpy(evento->dataFim,             "-");
    strcpy(evento->horaFim,             "-");
    strcpy(evento->horaInicio,          "-");
    strcpy(evento->localEvento,         "-");
    strcpy(evento->cidade,              "-");
    strcpy(evento->uf,                  "-");

    evento->status = STATUS_ORCAMENTO,

    strcpy(evento->listaRecursos = NULL);
    strcpy(evento->listaEquipes = NULL);
    strcpy(evento->listaFornecedores = NULL);

    strcpy(evento-> custoTotal = 0.0);
    strcpy(evento-> custoTotalEquipe = 0.0);
    strcpy(evento->custoTotalEquipe = 0.0);
    strcpy(evento->custoTotalServicos = 0.0);
    strcpy(evento->custoTotal = 0.0);
    strcpy(evento->obs, "-");
}
void eventoInit(ListaEvento *listaEvento) {
    listaEvento->prox = NULL;
    eventoInit(&listaEvento->evento);
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

int eventoAdicionar(ListaEvento **listaEvento, TipoEvento evento) {
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

int eventoAtualizar(ListaEvento *listaEvento, TipoEvento eventoAtualizado, int id){
    // variavel auxiliar para percorrer a lista
    ListaEvento *atual = listaEvento;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){
        // se o id do cliente atual for o id q eu quero, atualiza os dados
        if(atual->evento.id == id){

            //guarda o ponteiro das listas antes de copiar
            ItemRecursoEvento *recursos = atual->evento.listaRecursos;
            ItemEquipeEvento *equipes = atual->evento.listaEquipes;
            ItemFornecedorEvento *fornecedores = atual->evento.listaFornecedores;

            // agora atualiza evento
            atual->evento = eventoAtualizado;
            atual->evento.id = id; // garante q o id n vai ser alterado

            atual->evento.listaRecursos = recursos;
            atual->evento.listaEquipes = equipes;
            atual->evento.listaFornecedores = fornecedores;

            return 1; // sucesso
        }
        atual = atual->prox;
    }
    return 0;
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

void eventoListaLiberar(TipoEvento* listaEvento){
    //auxiliar pra liberar cada no um por um
    ListaEvento* aux;

    // enquanto ainda tiver algo na lista, libera a cabeca e avanca
    while (listaEvento != NULL){
        aux = listaEvento;

        // libera as listas de itens antes de lierar o evento blz
        eventoLiberarRecursos(aux->evento.listaRecursos);
        eventoLiberarEquipes(aux->evento.listaEquipes);
        eventoLiberarFornecedores(aux->evento.listaFornecedores);

        listaEvento = listaEvento->prox;
        free(aux);
    }
}

//=========== GESTAO DOS RECURSOS ===========
//=========== GESTAO DA EQUIPE ===========
//=========== GESTAO DOS FORNECEDORES ===========


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
                            atual->evento.codigo_cliente,
                            atual->evento.data_inicio,
                            atual->evento.data_fim,
                            atual->evento.hora_inicio,
                            atual->evento.hora_fim,
                            atual->evento.local_evento,
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


int eventoLerTXT(TipoEvento **listaEvento) {
    FILE *arquivo = fopen("dados/evento.txt", "r");
    if (arquivo == NULL) return 0;

    // usada p/ armazenar dados do arq. serve como buffer d leitura
    // le os campos de evento.txt, preenche os campos de temp,
    // dps copia os dados e passa p/ a posicao correta na >listaEvento
    TipoEvento temp;
    int status_int; // comum p/ armazenar codigos de status

    // le os atributos do arquivo
    while (fscanf(arquivo, "%d|%99[^|]|%d|%10[^|]|%10[^|]|%5[^|]|%5[^|]|%199[^|]|%49[^|]|%2[^|]|%d|%f|%f|%f|%f|%f|%f|%499[^\n]\n",
    &temp.id,
             temp.nome,
             &temp.codigo_cliente,
             temp.data_inicio,
             temp.data_fim,
             temp.hora_inicio,
             temp.hora_fim,
             temp.local_evento,
             temp.cidade,
             temp.uf,
             &status_int,
             &temp.custo_total_recursos,
             &temp.custo_total_equipe,
             &temp.custo_total_fornecedores,
             &temp.custo_total,
             &temp.margem_lucro_percentual,
             &temp.valor_total_evento,
             temp.obs) == 18) {
        temp.ativo = true;
        temp.status = (StatusEvento)status_int;
        temp.listaEquipes = NULL;
        temp.listaFornecedores = NULL;
        temp.listaRecursos = NULL;

        eventoAdicionar(listaEvento, temp);
    }
        fclose(arquivo);
        return 0;


    fclose(arquivo);
    return 1;
}

int eventoSalvarBIN(TipoEvento *evento) {
    FILE *arquivo = fopen("dados/evento.bin", "wb");
    if (arquivo == NULL) return 0;

    ListaEvento *atual = lista;

    while(atual != NULL) {
        if (atual != NULL) {
            fwrite(&atual->evento, sizeof(TipoEvento), 1, arquivo);
        }
        atual = atual->prox;
    }

    fclose(arquivo);
    return 1;
}

int eventoLerBIN(TipoEvento *evento) {
    FILE *arquivo = fopen("dados/evento.bin", "rb");
    if (arquivo == NULL) return 0;

    TipoEvento temp;

    // conferir se os nomes estao corretos ou se confudi listaRecursos p/ lista_recursos
    while (atual != NULL) {
        if (fread(&temp, sizeof(TipoEvento), 1, arquivo) == 1) {
            temp.listaEquipes = NULL;
            temp.listaFornecedores = NULL;
            temp.listaRecursos = NULL;

            eventoAdicionar(lista, tempo);
        }
    }

    if (fread(evento, sizeof(TipoEvento), 1, arquivo) != 1) {
        fclose(arquivo);
        return 0;
    }

    fclose(arquivo);
    return 1;
}