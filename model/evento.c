#include "evento.h"
#include "fornecedor.h"
#include "cliente.h"
#include "equipe.h"
#include "recurso.h"

void eventoInit(TipoEvento *evento) {
    evento->ativo = true;
    evento->id = 0;

    strcpy(evento->nome, "");
    //evento->cliente.id = 0;

    memset(&evento->dataInicio, 0, sizeof(struct tm));
    memset(&evento->dataFim, 0, sizeof(struct tm));
    strcpy(evento->localEvento, "");
    strcpy(evento->cidade,      "");
    strcpy(evento->uf,          "");

    evento->status = STATUS_ORCAMENTO;
    //
    // evento->listaRecursos = NULL;
    // evento->listaEquipes = NULL;
    // evento->listaFornecedores = NULL;

    evento->custoTotalRecursos = 0.0;
    evento->custoTotalEquipe = 0.0;
    evento->custoTotalForn = 0.0;
    evento->custoTotal = 0.0;
    evento->margemLucro = 0.0;
    evento->valorFinal = 0.0;

    strcpy(evento->obs, "");
}

void eventoListaInit(ListaEvento **listaEvento) {
    *listaEvento = NULL;
}

// ===== CRUD EVENTO =====

int eventoAdicionar(ListaEvento **listaEvento, TipoEvento evento) {
    ListaEvento *novo = (ListaEvento *)malloc(sizeof(ListaEvento));
    if (novo == NULL) return 0;

    novo->evento = evento;
    novo->evento.ativo = true;
    novo->prox = NULL;

    if (*listaEvento == NULL) {
        novo->evento.id = 1;
        *listaEvento = novo;
    } else {
        ListaEvento *atual = *listaEvento;
        while (atual->prox != NULL) atual = atual->prox;

        novo->evento.id = atual->evento.id + 1;
        atual->prox = novo;
    }

    return 1;
}

int eventoRemover(ListaEvento **listaEvento, int id) {
    ListaEvento *atual = *listaEvento;

    while (atual != NULL) {
        if (atual->evento.id == id) {
            atual->evento.ativo = false;
            return 1;
        }
        atual = atual->prox;
    }

    return 0;
}

int eventoAtualizar(ListaEvento *listaEvento, TipoEvento eventoAtualizado, int id) {
    ListaEvento *atual = listaEvento;

    while (atual != NULL) {
        if (atual->evento.id == id) {
            // Guarda os ponteiros com os tipos corretos
            ListaRecurso *recursos = atual->evento.listaRecursos;
            ListaEquipe *equipes = atual->evento.listaEquipes;
            ListaFornecedor *fornecedores = atual->evento.listaFornecedores;

            atual->evento = eventoAtualizado;
            atual->evento.id = id;

            // Restaura os ponteiros
            atual->evento.listaRecursos = recursos;
            atual->evento.listaEquipes = equipes;
            atual->evento.listaFornecedores = fornecedores;

            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

TipoEvento* eventoBuscar(ListaEvento *listaEvento, int id) {
    ListaEvento *atual = listaEvento;

    while (atual != NULL) {
        if (atual->evento.id == id && atual->evento.ativo) {
            return &atual->evento;
        }
        atual = atual->prox;
    }

    return NULL;
}

void eventoListaLiberar(ListaEvento *listaEvento) {
    while (listaEvento != NULL) {
        ListaEvento *aux = listaEvento;
        listaEvento = listaEvento->prox;

        eventoLiberarRecursos(aux->evento.listaRecursos);
        eventoLiberarEquipes(aux->evento.listaEquipes);
        eventoLiberarFornecedores(aux->evento.listaFornecedores);

        free(aux);
    }
}

//=========== UNIR RECURSOS, EQUIPES E FORNECEDORES ===========

int eventoUnirRecurso(TipoEvento *evento, ListaRecurso *listaGlobalRecursos, int codigoRecurso,
    int qtd, int diasEvento) {

    if (evento == NULL || listaGlobalRecursos == NULL) return 0;

    // Busca o recurso na lista global
    TipoRecurso *recursoEncontrado = recursoBuscar(listaGlobalRecursos, codigoRecurso);
    if (recursoEncontrado == NULL) return 0; // Recurso não encontrado

    // Verifica se tem estoque suficiente
    if (recursoEncontrado->qtdEstoque < qtd) return 0;

    // Verifica se o recurso já está no evento
    if (eventoBuscarRecurso(evento, codigoRecurso) != NULL) {
        return 0; // Recurso já adicionado ao evento
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
    if (funcEncontrado == NULL) return 0; // Funcionário não encontrado

    // Verifica se o funcionário já está no evento
    if (eventoBuscarEquipe(evento, codigoFunc) != NULL) {
        return 0; // Funcionário já adicionado ao evento
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
    if (fornecedorEncontrado == NULL) return 0; // Fornecedor não encontrado

    // Verifica se o fornecedor já está no evento
    if (eventoBuscarFornecedor(evento, codigoFornecedor) != NULL) {
        return 0; // Fornecedor já adicionado ao evento
    }

    // Cria o item do fornecedor para o evento
    ItemFornecedorEvento item;
    item.codigoFornecedor = codigoFornecedor;
    strcpy(item.descricaoServico, descricaoServico);
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

//=========== ARQUIVOS DO EVENTO ===========

int eventoSalvarTXT(ListaEvento *listaEvento) {
    FILE *arquivo = fopen("dados/evento.txt", "w");
    if (arquivo == NULL) return 0;

    ListaEvento *atual = listaEvento;

    while (atual != NULL) {
        if (atual->evento.ativo) {
            // Formatar datas como strings
            char dataIni[11], dataFim[11];
            sprintf(dataIni, "%02d/%02d/%04d",
                    atual->evento.dataInicio.tm_mday,
                    atual->evento.dataInicio.tm_mon + 1,
                    atual->evento.dataInicio.tm_year + 1900);
            sprintf(dataFim, "%02d/%02d/%04d",
                    atual->evento.dataFim.tm_mday,
                    atual->evento.dataFim.tm_mon + 1,
                    atual->evento.dataFim.tm_year + 1900);

            fprintf(arquivo, "%d|%s|%d|%s|%s|%s|%s|%s|%d|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%s\n",
                    atual->evento.id,
                    atual->evento.nome,
                    atual->evento.codigoCliente,
                    dataIni,
                    dataFim,
                    atual->evento.localEvento,
                    atual->evento.cidade,
                    atual->evento.uf,
                    atual->evento.status,
                    atual->evento.custoTotalRecursos,
                    atual->evento.custoTotalEquipe,
                    atual->evento.custoTotalForn,
                    atual->evento.custoTotal,
                    atual->evento.margemLucro,
                    atual->evento.valorFinal,
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
    char dataIni[11], dataFim[11];
    int dia, mes, ano;

    while (fscanf(arquivo, "%d|%99[^|]|%d|%10[^|]|%10[^|]|%149[^|]|%49[^|]|%2[^|]|%d|%lf|%lf|%lf|%lf|%lf|%lf|%499[^\n]\n",
                  &temp.id,
                  temp.nome,
                  &temp.codigoCliente,
                  dataIni,
                  dataFim,
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
                  temp.obs) == 16) {

        // Parse data início
        sscanf(dataIni, "%d/%d/%d", &dia, &mes, &ano);
        temp.dataInicio.tm_mday = dia;
        temp.dataInicio.tm_mon = mes - 1;
        temp.dataInicio.tm_year = ano - 1900;

        // Parse data fim
        sscanf(dataFim, "%d/%d/%d", &dia, &mes, &ano);
        temp.dataFim.tm_mday = dia;
        temp.dataFim.tm_mon = mes - 1;
        temp.dataFim.tm_year = ano - 1900;

        temp.ativo = true;
        temp.status = (StatusEvento)status_int;
        temp.listaRecursos = NULL;
        temp.listaEquipes = NULL;
        temp.listaFornecedores = NULL;

        eventoAdicionar(listaEvento, temp);
    }

    fclose(arquivo);
    return 1;
}

int eventoSalvarBIN(ListaEvento *listaEvento) {
    FILE *arquivo = fopen("dados/evento.bin", "wb");
    if (arquivo == NULL) return 0;

    ListaEvento *atual = listaEvento;

    while (atual != NULL) {
        if (atual->evento.ativo) {
            fwrite(&atual->evento, sizeof(TipoEvento), 1, arquivo);
        }
        atual = atual->prox;
    }

    fclose(arquivo);
    return 1;
}

int eventoLerBIN(ListaEvento **listaEvento) {
    FILE *arquivo = fopen("dados/evento.bin", "rb");
    if (arquivo == NULL) return 0;

    TipoEvento temp = {0};

    while (fread(&temp, sizeof(TipoEvento), 1, arquivo) == 1) {
        temp.listaRecursos = NULL;
        temp.listaEquipes = NULL;
        temp.listaFornecedores = NULL;

        eventoAdicionar(listaEvento, temp);
    }

    fclose(arquivo);
    return 1;
}