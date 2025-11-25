#include "evento.h"
#include "fornecedor.h"
#include "cliente.h"
#include "equipe.h"
#include "recurso.h"

void eventoInit(TipoEvento *evento) {
    evento->ativo = true;         // td evento comeca como ativo
    evento->id = 0;               // id vai ser calculado automaticamente
    evento->codigoCliente = 0;    // cliente sera atribuido depois

    // Atributos comecam vazios pra tirar lixo de memoria
    strcpy(evento->nome,          "");
    strcpy(evento->localEvento,   "");
    strcpy(evento->cidade,        "");
    strcpy(evento->uf,            "");
    strcpy(evento->obs,           "");

    memset(&evento->dataInicio, 0, sizeof(struct tm));
    memset(&evento->dataFim, 0, sizeof(struct tm));

    evento->status = STATUS_ORCAMENTO;

    evento->custoTotalRecursos = 0.0;
    evento->custoTotalEquipe = 0.0;
    evento->custoTotalForn = 0.0;
    evento->custoTotal = 0.0;
    evento->margemLucro = 0.0;
    evento->valorFinal = 0.0;
}

void eventoListaInit(ListaEvento *lista) {
    lista->prox = NULL;
    eventoInit(&lista->evento);
}

// ===== CRUD EVENTO =====

int eventoAdicionar(ListaEvento **lista, TipoEvento evento) {
    // aloca o espaco para um novo no'
    ListaEvento *novo = (ListaEvento *)malloc(sizeof(ListaEvento));
    if(novo == NULL) return 0;

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
    return 1;
}

int eventoRemover(ListaEvento **lista, int id) {
    // variavel auxiliar para percorrer a lista
    ListaEvento *atual = *lista;

    // enquanto oq eu to olhando n for nulo, avanca
    while(atual != NULL){

        // se o id do evento atual for o id q eu quero, marca como inativo
        if(atual->evento.id == id){
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
        lista = lista->prox;
        free(aux);
    }
}

//=========== UNIR RECURSOS, EQUIPES E FORNECEDORES ===========

/*
int eventoUnirRecurso(TipoEvento *evento, ListaRecurso *listaGlobalRecursos, int codigoRecurso,
    int qtd, int diasEvento) {

    if (evento == NULL || listaGlobalRecursos == NULL) return 0;

    // Busca o recurso na lista global
    TipoRecurso *recursoEncontrado = recursoBuscar(listaGlobalRecursos, codigoRecurso);
    if (recursoEncontrado == NULL) return 0;

    // Verifica se tem estoque suficiente
    if (recursoEncontrado->qtdEstoque < qtd) return 0;

    // Verifica se o recurso já está no evento
    if (eventoBuscarRecurso(evento, codigoRecurso) != NULL) {
        return 0;
    }

    // Cria o item do recurso para o evento
    ItemRecursoEvento item;
    item.codigoRecurso = codigoRecurso;
    item.qtd = qtd;
    item.diasEvento = diasEvento;
    item.valorUnitario = recursoEncontrado->valorLocacao;
    item.subtotal = qtd * item.valorUnitario * diasEvento;

    // Adiciona o recurso ao evento
    return eventoAdicionarRecurso(evento, item);
}

int eventoUnirEquipe(TipoEvento *evento, ListaEquipe *listaGlobalEquipe, int codigoFunc,
    double valorDiaria, int numDias) {

    if (evento == NULL || listaGlobalEquipe == NULL) return 0;

    // Busca o funcionário na lista global
    TipoEquipe *funcEncontrado = equipeBuscar(listaGlobalEquipe, codigoFunc);
    if (funcEncontrado == NULL) return 0;

    // Verifica se o funcionário já está no evento
    if (eventoBuscarEquipe(evento, codigoFunc) != NULL) {
        return 0;
    }

    // Cria o item da equipe para o evento
    ItemEquipeEvento item;
    item.codigoFunc = codigoFunc;
    item.valorDiaria = valorDiaria;
    item.numDias = numDias;
    item.subtotal = valorDiaria * numDias;

    // Adiciona a equipe ao evento
    return eventoAdicionarEquipe(evento, item);
}

int eventoUnirFornecedor(TipoEvento *evento, ListaFornecedor *listaGlobalFornecedor,
    int codigoFornecedor, const char *descricaoServico, double valorServico) {

    if (evento == NULL || listaGlobalFornecedor == NULL) return 0;

    // Busca o fornecedor na lista global
    TipoFornecedor *fornecedorEncontrado = fornecedorBuscar(listaGlobalFornecedor, codigoFornecedor);
    if (fornecedorEncontrado == NULL) return 0;

    // Verifica se o fornecedor já está no evento
    if (eventoBuscarFornecedor(evento, codigoFornecedor) != NULL) {
        return 0;
    }

    // Cria o item do fornecedor para o evento
    ItemFornecedorEvento item;
    item.codigoFornecedor = codigoFornecedor;
    strcpy(item.descricaoServico, descricaoServico);
    item.valorServico = valorServico;

    // Adiciona o fornecedor ao evento
    return eventoAdicionarFornecedor(evento, item);
}
*/

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

//=========== METODOS DOS CALCULOS ===========
// Funções comentadas - dependem de estruturas externas

/*
double eventoCalcularTotalRecursos(TipoEvento *evento) {
    double total = 0.0;
    ListaRecurso *atual = evento->listaRecursos;

    while (atual != NULL) {
        total += atual->item.subtotal;
        atual = atual->prox;
    }

    return total;
}

double eventoCalcularTotalEquipe(TipoEvento *evento) {
    double total = 0.0;
    ListaEquipe *atual = evento->listaEquipes;

    while (atual != NULL) {
        total += atual->item.subtotal;
        atual = atual->prox;
    }

    return total;
}

double eventoCalcularTotalFornecedores(TipoEvento *evento) {
    double total = 0.0;
    ListaFornecedor *atual = evento->listaFornecedores;

    while (atual != NULL) {
        total += atual->item.valorServico;
        atual = atual->prox;
    }

    return total;
}

void eventoRecalcularTotais(TipoEvento *evento) {
    evento->custoTotalRecursos = eventoCalcularTotalRecursos(evento);
    evento->custoTotalEquipe = eventoCalcularTotalEquipe(evento);
    evento->custoTotalForn = eventoCalcularTotalFornecedores(evento);

    evento->custoTotal = evento->custoTotalRecursos +
                         evento->custoTotalEquipe +
                         evento->custoTotalForn;

    // Calcula valor final com margem de lucro
    evento->valorFinal = evento->custoTotal * (1.0 + evento->margemLucro / 100.0);
}
*/

//==================================================
// Arquivos

int eventoSalvarTXT(ListaEvento *lista){
    // Abre o arquivo em um ponteiro de arquivo
    FILE* fp = fopen("dados/evento.txt", "w");

    // Confere se deu erro
    if(fp == NULL) return 0;

    // Aux pra percorrer a lista
    if (lista == NULL) { fclose(fp); return 0; }
    ListaEvento* aux = lista;

    // Percorre a lista printando tudo no txt
    while (aux != NULL) {
        // Printa um item
        fprintf(fp, "%d,%d,%d,%d,%s,%s,%s,%s,%lf,%lf,%lf,%lf,%lf,%lf,%s\n",
        aux->evento.ativo,
        aux->evento.id,
        aux->evento.codigoCliente,
        aux->evento.status,
        aux->evento.nome,
        aux->evento.localEvento,
        aux->evento.cidade,
        aux->evento.uf,
        aux->evento.custoTotalRecursos,
        aux->evento.custoTotalEquipe,
        aux->evento.custoTotalForn,
        aux->evento.custoTotal,
        aux->evento.margemLucro,
        aux->evento.valorFinal,
        aux->evento.obs);

        // Avanca
        aux = aux->prox;
    }

    // Deu certo, fecha o ponteiro e retorna sucesso
    fclose(fp);
    return 1;
}

int eventoLerTXT(ListaEvento **lista) {
    FILE *fp = fopen("dados/evento.txt", "r");
    if(fp == NULL) return 0;

    TipoEvento temp;
    // como nao tem assinatura de bool, le como int e atribui depois
    int ativoTemp, statusTemp;

    while(fscanf(fp, "%d,%d,%d,%d,%[^,],%[^,],%[^,],%[^,],%lf,%lf,%lf,%lf,%lf,%lf,%[^\n]",
        &ativoTemp,
        &temp.id,
        &temp.codigoCliente,
        &statusTemp,
        temp.nome,
        temp.localEvento,
        temp.cidade,
        temp.uf,
        &temp.custoTotalRecursos,
        &temp.custoTotalEquipe,
        &temp.custoTotalForn,
        &temp.custoTotal,
        &temp.margemLucro,
        &temp.valorFinal,
        temp.obs) == 15)
    {
        // atribui os booleanos
        temp.ativo = ativoTemp;
        temp.status = statusTemp;

        //adiciona na lista
        eventoAdicionar(lista, temp);
    }

    // Deu bom, fecha o arquivo e retorna sucesso
    fclose(fp);
    return 1;
}

int eventoSalvarBIN(ListaEvento* lista) {
    FILE* fp = fopen("dados/evento.bin", "wb");
    if (fp == NULL) return 0;

    // Aux pra percorrer a lista
    if (lista == NULL) { fclose(fp); return 0; }
    ListaEvento* aux = lista;

    // Percorre a lista escrevendo tudo no binario
    while (aux != NULL) {
        // Escreve um item
        fwrite(&aux->evento, sizeof(TipoEvento), 1, fp);

        // Avanca
        aux = aux->prox;
    }

    // Deu certo, fecha o ponteiro e retorna sucesso
    fclose(fp);
    return 1;
}

int eventoLerBIN(ListaEvento** lista) {
    FILE* fp = fopen("dados/evento.bin", "rb");
    if (fp == NULL) return 0;

    TipoEvento temp;

    // Le o arquivo binario ate o final
    while (fread(&temp, sizeof(TipoEvento), 1, fp) == 1) {
        eventoAdicionar(lista, temp);
    }

    // Deu bom, fecha o arquivo e retorna sucesso
    fclose(fp);
    return 1;
}