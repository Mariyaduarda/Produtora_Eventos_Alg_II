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

    // inicializa listas internas
    evento->listaRecursos = NULL;
    evento->listaEquipes = NULL;
    evento->listaFornecedores = NULL;
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

//=========== UNIR RECURSOS, EQUIPES E FORNECEDORES ===========

// ========== Operacoes sobre listas internas do evento ==========

int eventoAdicionarRecurso(TipoEvento *evento, ItemRecursoEvento item) {
    if (evento == NULL) return 0;

    ListaRecursoEvento *novo = (ListaRecursoEvento *)malloc(sizeof(ListaRecursoEvento));
    if (novo == NULL) return 0;
    novo->item = item;
    novo->prox = NULL;

    if (evento->listaRecursos == NULL) {
        evento->listaRecursos = novo;
    } else {
        ListaRecursoEvento *atual = evento->listaRecursos;
        while (atual->prox != NULL) atual = atual->prox;
        atual->prox = novo;
    }

    eventoRecalcularTotais(evento);
    return 1;
}

ItemRecursoEvento* eventoBuscarRecurso(TipoEvento *evento, int codigoRecurso) {
    if (evento == NULL) return NULL;
    ListaRecursoEvento *atual = evento->listaRecursos;
    while (atual != NULL) {
        if (atual->item.codigoRecurso == codigoRecurso) return &atual->item;
        atual = atual->prox;
    }
    return NULL;
}

int eventoRemoverRecurso(TipoEvento *evento, int codigoRecurso) {
    if (evento == NULL) return 0;
    ListaRecursoEvento *atual = evento->listaRecursos;
    ListaRecursoEvento *prev = NULL;
    while (atual != NULL) {
        if (atual->item.codigoRecurso == codigoRecurso) {
            if (prev == NULL) evento->listaRecursos = atual->prox;
            else prev->prox = atual->prox;
            free(atual);
            eventoRecalcularTotais(evento);
            return 1;
        }
        prev = atual;
        atual = atual->prox;
    }
    return 0;
}

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

    eventoRecalcularTotais(evento);
    return 1;
}

ItemEquipeEvento* eventoBuscarEquipe(TipoEvento *evento, int codigoFunc) {
    if (evento == NULL) return NULL;
    ListaEquipeEvento *atual = evento->listaEquipes;
    while (atual != NULL) {
        if (atual->item.codigoFunc == codigoFunc) return &atual->item;
        atual = atual->prox;
    }
    return NULL;
}

int eventoRemoverEquipe(TipoEvento *evento, int codigoFunc) {
    if (evento == NULL) return 0;
    ListaEquipeEvento *atual = evento->listaEquipes;
    ListaEquipeEvento *prev = NULL;
    while (atual != NULL) {
        if (atual->item.codigoFunc == codigoFunc) {
            if (prev == NULL) evento->listaEquipes = atual->prox;
            else prev->prox = atual->prox;
            free(atual);
            eventoRecalcularTotais(evento);
            return 1;
        }
        prev = atual;
        atual = atual->prox;
    }
    return 0;
}

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

    eventoRecalcularTotais(evento);
    return 1;
}

ItemFornecedorEvento* eventoBuscarFornecedor(TipoEvento *evento, int codigoFornecedor) {
    if (evento == NULL) return NULL;
    ListaFornecedorEvento *atual = evento->listaFornecedores;
    while (atual != NULL) {
        if (atual->item.codigoFornecedor == codigoFornecedor) return &atual->item;
        atual = atual->prox;
    }
    return NULL;
}

int eventoRemoverFornecedor(TipoEvento *evento, int codigoFornecedor) {
    if (evento == NULL) return 0;
    ListaFornecedorEvento *atual = evento->listaFornecedores;
    ListaFornecedorEvento *prev = NULL;
    while (atual != NULL) {
        if (atual->item.codigoFornecedor == codigoFornecedor) {
            if (prev == NULL) evento->listaFornecedores = atual->prox;
            else prev->prox = atual->prox;
            free(atual);
            eventoRecalcularTotais(evento);
            return 1;
        }
        prev = atual;
        atual = atual->prox;
    }
    return 0;
}

// ========== UNIR RECURSOS, EQUIPES E FORNECEDORES ==========

int eventoUnirRecurso(TipoEvento *evento, ListaRecurso *listaGlobalRecursos, int codigoRecurso,
    int qtd, int diasEvento) {

    if (evento == NULL || listaGlobalRecursos == NULL) return 0;

    // Busca o recurso na lista global
    TipoRecurso *recursoEncontrado = recursoBuscar(listaGlobalRecursos, codigoRecurso);
    if (recursoEncontrado == NULL) return 0;

    // Verifica se tem estoque suficiente
    if (recursoEncontrado->qtdEstoque < qtd) return 0;

    // Verifica se o recurso ja esta no evento
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

    // Atualiza estoque global
    recursoEncontrado->qtdEstoque -= qtd;

    // Adiciona o recurso ao evento
    return eventoAdicionarRecurso(evento, item);
}

int eventoUnirEquipe(TipoEvento *evento, ListaEquipe *listaGlobalEquipe, int codigoFunc,
    double valorDiaria, int numDias) {

    if (evento == NULL || listaGlobalEquipe == NULL) return 0;

    // Busca o funcionario na lista global
    TipoEquipe *funcEncontrado = equipeBuscar(listaGlobalEquipe, codigoFunc);
    if (funcEncontrado == NULL) return 0;

    // Verifica se o funcionario ja esta no evento
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

    // Verifica se o fornecedor ja esta no evento
    if (eventoBuscarFornecedor(evento, codigoFornecedor) != NULL) {
        return 0;
    }

    // Cria o item do fornecedor para o evento
    ItemFornecedorEvento item;
    item.codigoFornecedor = codigoFornecedor;
    strncpy(item.descricaoServico, descricaoServico, sizeof(item.descricaoServico)-1);
    item.descricaoServico[sizeof(item.descricaoServico)-1] = '\0';
    item.valorServico = valorServico;

    // Adiciona o fornecedor ao evento
    return eventoAdicionarFornecedor(evento, item);
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

//=========== METODOS DOS CALCULOS ===========

double eventoCalcularTotalRecursos(TipoEvento *evento) {
    double total = 0.0;
    ListaRecursoEvento *atual = evento->listaRecursos;

    while (atual != NULL) {
        total += atual->item.subtotal;
        atual = atual->prox;
    }

    return total;
}

double eventoCalcularTotalEquipe(TipoEvento *evento) {
    double total = 0.0;
    ListaEquipeEvento *atual = evento->listaEquipes;

    while (atual != NULL) {
        total += atual->item.subtotal;
        atual = atual->prox;
    }

    return total;
}

double eventoCalcularTotalFornecedores(TipoEvento *evento) {
    double total = 0.0;
    ListaFornecedorEvento *atual = evento->listaFornecedores;

    while (atual != NULL) {
        total += atual->item.valorServico;
        atual = atual->prox;
    }

    return total;
}

void eventoRecalcularTotais(TipoEvento *evento) {
    if (evento == NULL) return;

    evento->custoTotalRecursos = eventoCalcularTotalRecursos(evento);
    evento->custoTotalEquipe = eventoCalcularTotalEquipe(evento);
    evento->custoTotalForn = eventoCalcularTotalFornecedores(evento);

    evento->custoTotal = evento->custoTotalRecursos +
                         evento->custoTotalEquipe +
                         evento->custoTotalForn;

    // Calcula valor final com margem de lucro
    evento->valorFinal = evento->custoTotal * (1.0 + evento->margemLucro / 100.0);
}

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
        // Printa um item (campos fixos do evento)
        fprintf(fp, "%d,%d,%d,%d,%s,%s,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%s\n",
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

    // Agora salva os itens por-evento em arquivos separados (TXT)
    // Recursos
    FILE *fpRec = fopen("dados/evento_recursos.txt", "w");
    if (fpRec != NULL) {
        ListaEvento *e = lista;
        while (e != NULL) {
            ListaRecursoEvento *r = e->evento.listaRecursos;
            while (r != NULL) {
                // formato: eventoId,codigoRecurso,qtd,dias,valorUnitario,subtotal
                fprintf(fpRec, "%d,%d,%d,%d,%.2f,%.2f\n",
                    e->evento.id,
                    r->item.codigoRecurso,
                    r->item.qtd,
                    r->item.diasEvento,
                    r->item.valorUnitario,
                    r->item.subtotal);
                r = r->prox;
            }
            e = e->prox;
        }
        fclose(fpRec);
    }

    // Equipes
    FILE *fpEq = fopen("dados/evento_equipes.txt", "w");
    if (fpEq != NULL) {
        ListaEvento *e = lista;
        while (e != NULL) {
            ListaEquipeEvento *q = e->evento.listaEquipes;
            while (q != NULL) {
                // formato: eventoId,codigoFunc,valorDiaria,numDias,subtotal
                fprintf(fpEq, "%d,%d,%.2f,%d,%.2f\n",
                    e->evento.id,
                    q->item.codigoFunc,
                    q->item.valorDiaria,
                    q->item.numDias,
                    q->item.subtotal);
                q = q->prox;
            }
            e = e->prox;
        }
        fclose(fpEq);
    }

    // Fornecedores
    FILE *fpFor = fopen("dados/evento_fornecedores.txt", "w");
    if (fpFor != NULL) {
        ListaEvento *e = lista;
        while (e != NULL) {
            ListaFornecedorEvento *f = e->evento.listaFornecedores;
            while (f != NULL) {
                // formato: eventoId,codigoFornecedor,descricaoServico,valorServico
                fprintf(fpFor, "%d,%d,%s,%.2f\n",
                    e->evento.id,
                    f->item.codigoFornecedor,
                    f->item.descricaoServico,
                    f->item.valorServico);
                f = f->prox;
            }
            e = e->prox;
        }
        fclose(fpFor);
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

    while(fscanf(fp, "%d,%d,%d,%d,%99[^,],%149[^,],%49[^,],%3[^,],%lf,%lf,%lf,%lf,%lf,%lf,%499[^\n]",
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

        // inicializa listas internas (eventoAdicionar chamara eventoInit via uso anterior?)
        temp.listaRecursos = NULL;
        temp.listaEquipes = NULL;
        temp.listaFornecedores = NULL;

        //adiciona na lista
        eventoAdicionar(lista, temp);
    }

    // Agora tenta ler os arquivos de itens por-evento e associar aos eventos carregados
    // Recursos
    FILE *fpRec = fopen("dados/evento_recursos.txt", "r");
    if (fpRec != NULL) {
        int eventoId, codigoRecurso, qtd, dias;
        double valorUnitario, subtotal;
        while (fscanf(fpRec, "%d,%d,%d,%d,%lf,%lf\n",
               &eventoId, &codigoRecurso, &qtd, &dias, &valorUnitario, &subtotal) == 6) {
            TipoEvento *e = eventoBuscar(*lista, eventoId);
            if (e != NULL) {
                ItemRecursoEvento item;
                item.codigoRecurso = codigoRecurso;
                item.qtd = qtd;
                item.diasEvento = dias;
                item.valorUnitario = valorUnitario;
                item.subtotal = subtotal;
                eventoAdicionarRecurso(e, item);
            }
        }
        fclose(fpRec);
    }

    // Equipes
    FILE *fpEq = fopen("dados/evento_equipes.txt", "r");
    if (fpEq != NULL) {
        int eventoId, codigoFunc, numDias;
        double valorDiaria, subtotal;
        while (fscanf(fpEq, "%d,%d,%lf,%d,%lf\n",
               &eventoId, &codigoFunc, &valorDiaria, &numDias, &subtotal) == 5) {
            TipoEvento *e = eventoBuscar(*lista, eventoId);
            if (e != NULL) {
                ItemEquipeEvento item;
                item.codigoFunc = codigoFunc;
                item.valorDiaria = valorDiaria;
                item.numDias = numDias;
                item.subtotal = subtotal;
                eventoAdicionarEquipe(e, item);
            }
        }
        fclose(fpEq);
    }

    // Fornecedores
    FILE *fpFor = fopen("dados/evento_fornecedores.txt", "r");
    if (fpFor != NULL) {
        int eventoId, codigoFornecedor;
        char descricaoServico[200];
        double valorServico;
        while (fscanf(fpFor, "%d,%d,%199[^,],%lf\n",
               &eventoId, &codigoFornecedor, descricaoServico, &valorServico) == 4) {
            TipoEvento *e = eventoBuscar(*lista, eventoId);
            if (e != NULL) {
                ItemFornecedorEvento item;
                item.codigoFornecedor = codigoFornecedor;
                strncpy(item.descricaoServico, descricaoServico, sizeof(item.descricaoServico)-1);
                item.descricaoServico[sizeof(item.descricaoServico)-1] = '\0';
                item.valorServico = valorServico;
                eventoAdicionarFornecedor(e, item);
            }
        }
        fclose(fpFor);
    }

    // Deu bom, fecha o arquivo e retorna sucesso
    fclose(fp);
    return 1;
}

int eventoSalvarBIN(ListaEvento* lista) {
    // Salva events em binario (campos sem ponteiros)
    FILE* fp = fopen("dados/evento.bin", "wb");
    if (fp == NULL) return 0;

    if (lista == NULL) { fclose(fp); return 0; }

    // conta eventos
    int count = 0;
    ListaEvento *aux = lista;
    while (aux != NULL) { count++; aux = aux->prox; }

    // escreve quantidade
    fwrite(&count, sizeof(int), 1, fp);

    // escreve cada evento com campos fixos
    aux = lista;
    while (aux != NULL) {
        int ativo = aux->evento.ativo ? 1 : 0;
        int id = aux->evento.id;
        int codigoCliente = aux->evento.codigoCliente;
        int status = aux->evento.status;

        fwrite(&ativo, sizeof(int), 1, fp);
        fwrite(&id, sizeof(int), 1, fp);
        fwrite(&codigoCliente, sizeof(int), 1, fp);
        fwrite(&status, sizeof(int), 1, fp);

        // strings com tamanhos fixos
        fwrite(aux->evento.nome, sizeof(char), 100, fp);
        fwrite(aux->evento.localEvento, sizeof(char), 150, fp);
        fwrite(aux->evento.cidade, sizeof(char), 50, fp);
        fwrite(aux->evento.uf, sizeof(char), 4, fp);

        fwrite(&aux->evento.custoTotalRecursos, sizeof(double), 1, fp);
        fwrite(&aux->evento.custoTotalEquipe, sizeof(double), 1, fp);
        fwrite(&aux->evento.custoTotalForn, sizeof(double), 1, fp);
        fwrite(&aux->evento.custoTotal, sizeof(double), 1, fp);
        fwrite(&aux->evento.margemLucro, sizeof(double), 1, fp);
        fwrite(&aux->evento.valorFinal, sizeof(double), 1, fp);

        fwrite(aux->evento.obs, sizeof(char), 500, fp);

        aux = aux->prox;
    }

    fclose(fp);

    // salvar itens por-evento em arquivos binarios
    // Recursos
    FILE *fpRec = fopen("dados/evento_recursos.bin", "wb");
    if (fpRec != NULL) {
        ListaEvento *e = lista;
        while (e != NULL) {
            ListaRecursoEvento *r = e->evento.listaRecursos;
            while (r != NULL) {
                // escreve: eventoId + item
                fwrite(&e->evento.id, sizeof(int), 1, fpRec);
                fwrite(&r->item, sizeof(ItemRecursoEvento), 1, fpRec);
                r = r->prox;
            }
            e = e->prox;
        }
        fclose(fpRec);
    }

    // Equipes
    FILE *fpEq = fopen("dados/evento_equipes.bin", "wb");
    if (fpEq != NULL) {
        ListaEvento *e = lista;
        while (e != NULL) {
            ListaEquipeEvento *q = e->evento.listaEquipes;
            while (q != NULL) {
                fwrite(&e->evento.id, sizeof(int), 1, fpEq);
                fwrite(&q->item, sizeof(ItemEquipeEvento), 1, fpEq);
                q = q->prox;
            }
            e = e->prox;
        }
        fclose(fpEq);
    }

    // Fornecedores
    FILE *fpFor = fopen("dados/evento_fornecedores.bin", "wb");
    if (fpFor != NULL) {
        ListaEvento *e = lista;
        while (e != NULL) {
            ListaFornecedorEvento *f = e->evento.listaFornecedores;
            while (f != NULL) {
                fwrite(&e->evento.id, sizeof(int), 1, fpFor);
                fwrite(&f->item, sizeof(ItemFornecedorEvento), 1, fpFor);
                f = f->prox;
            }
            e = e->prox;
        }
        fclose(fpFor);
    }

    return 1;
}

int eventoLerBIN(ListaEvento** lista) {
    FILE* fp = fopen("dados/evento.bin", "rb");
    if (fp == NULL) return 0;

    int count = 0;
    if (fread(&count, sizeof(int), 1, fp) != 1) { fclose(fp); return 0; }

    for (int i = 0; i < count; i++) {
        TipoEvento temp;
        int ativoTemp, statusTemp;

        if (fread(&ativoTemp, sizeof(int), 1, fp) != 1) break;
        if (fread(&temp.id, sizeof(int), 1, fp) != 1) break;
        if (fread(&temp.codigoCliente, sizeof(int), 1, fp) != 1) break;
        if (fread(&statusTemp, sizeof(int), 1, fp) != 1) break;

        // read fixed strings
        fread(temp.nome, sizeof(char), 100, fp);
        fread(temp.localEvento, sizeof(char), 150, fp);
        fread(temp.cidade, sizeof(char), 50, fp);
        fread(temp.uf, sizeof(char), 4, fp);

        fread(&temp.custoTotalRecursos, sizeof(double), 1, fp);
        fread(&temp.custoTotalEquipe, sizeof(double), 1, fp);
        fread(&temp.custoTotalForn, sizeof(double), 1, fp);
        fread(&temp.custoTotal, sizeof(double), 1, fp);
        fread(&temp.margemLucro, sizeof(double), 1, fp);
        fread(&temp.valorFinal, sizeof(double), 1, fp);

        fread(temp.obs, sizeof(char), 500, fp);

        temp.ativo = (ativoTemp != 0);
        temp.status = statusTemp;

        // inicializa listas internas
        temp.listaRecursos = NULL;
        temp.listaEquipes = NULL;
        temp.listaFornecedores = NULL;

        eventoAdicionar(lista, temp);
    }

    fclose(fp);

    // Agora ler arquivos binarios de itens e associar
    // Recursos
    FILE *fpRec = fopen("dados/evento_recursos.bin", "rb");
    if (fpRec != NULL) {
        while (1) {
            int eventoId;
            ItemRecursoEvento item;
            if (fread(&eventoId, sizeof(int), 1, fpRec) != 1) break;
            if (fread(&item, sizeof(ItemRecursoEvento), 1, fpRec) != 1) break;
            TipoEvento *e = eventoBuscar(*lista, eventoId);
            if (e != NULL) eventoAdicionarRecurso(e, item);
        }
        fclose(fpRec);
    }

    // Equipes
    FILE *fpEq = fopen("dados/evento_equipes.bin", "rb");
    if (fpEq != NULL) {
        while (1) {
            int eventoId;
            ItemEquipeEvento item;
            if (fread(&eventoId, sizeof(int), 1, fpEq) != 1) break;
            if (fread(&item, sizeof(ItemEquipeEvento), 1, fpEq) != 1) break;
            TipoEvento *e = eventoBuscar(*lista, eventoId);
            if (e != NULL) eventoAdicionarEquipe(e, item);
        }
        fclose(fpEq);
    }

    // Fornecedores
    FILE *fpFor = fopen("dados/evento_fornecedores.bin", "rb");
    if (fpFor != NULL) {
        while (1) {
            int eventoId;
            ItemFornecedorEvento item;
            if (fread(&eventoId, sizeof(int), 1, fpFor) != 1) break;
            if (fread(&item, sizeof(ItemFornecedorEvento), 1, fpFor) != 1) break;
            TipoEvento *e = eventoBuscar(*lista, eventoId);
            if (e != NULL) eventoAdicionarFornecedor(e, item);
        }
        fclose(fpFor);
    }

    return 1;
}