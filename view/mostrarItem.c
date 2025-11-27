#include "mostrarItem.h"

//Funcoes para printar os itens
// - Cliente, Produtora etc

void printItemProdutora(TipoProdutora produtora) {
    // Faz as formatacoes necessarias
    char cnpjFormatado[20];
    formataCPFouCNPJ(produtora.cnpj, cnpjFormatado);
    char telFormatado[20];
    formataTelefone(produtora.telefone, telFormatado);
    char telRespFormatado[20];
    formataTelefone(produtora.telefoneDoResponsavel, telRespFormatado);

    // Printa os dados
    printf("\n | Nome            | %-46s | ", produtora.nomeFantasia);
    printf("\n | Razao Social    | %-46s | ", produtora.razaoSocial);
    printf("\n | Endereco        | %-46s | ", produtora.endereco);
    printf("\n | Telefone        | %-46s | ", telFormatado);
    printf("\n | Email           | %-46s | ", produtora.email);
    printf("\n | Responsavel     | %-46s | ", produtora.nomeDoResponsavel);
    printf("\n | Telefone Resp.  | %-46s | ", telRespFormatado);
    printf("\n | Margem de Lucro | R$%-44.2f | ", produtora.margemDeLucro);
    printf("\n | CNPJ            | %-46s | ", cnpjFormatado);
}

void printItemCliente(TipoCliente cliente) {
    // Faz as formatacoes necessarias
    char telFormatado[20];
    formataTelefone(cliente.telefone, telFormatado);

    // Printa os dados
    printf("\n=[ ID: %-4d ]=========================================================",cliente.id);
    printf("\n | Nome         | %-49s | ", cliente.nome);
    printf("\n | Endereco     | %-49s | ", cliente.endereco);
    printf("\n | Telefone     | %-49s | ", telFormatado);
    printf("\n | Email        | %-49s | ", cliente.email);
    printf("\n | Nome Contato | %-49s | ", cliente.nomeDoContato);

    // Printa o cpf ou cnpj
    if(cliente.usa_CNPJ){
        char formatado[20];
        formataCPFouCNPJ(cliente.cpf_cnpj, formatado);
        printf("\n | CNPJ         | %-49s | ", formatado);
    } else {
        char formatado[20];
        formataCPFouCNPJ(cliente.cpf_cnpj, formatado);
        printf("\n | CPF          | %-49s | ", formatado);
    }
}

void printItemEquipe(TipoEquipe equipe) {
    char cpfFormatado[20];
    formataCPFouCNPJ(equipe.cpf, cpfFormatado);

    printf("\n=[ ID: %-4d ]=========================================================",equipe.id);
    printf("\n | Nome   | %-55s | ", equipe.nome);
    printf("\n | Funcao | %-55s | ", equipe.funcao);
    printf("\n | Valor  | R$%-53.2f | ", equipe.valor);
    switch (equipe.tipoValor){
        case 0:
            printf("\n | Tipo   | Valor Fixo                                              | ");
            break;
        case 1:
            printf("\n | Tipo   | Valor Por Hora                                          | ");
            break;
        case 2:
            printf("\n | Tipo   | Valor Por Dia                                           | ");
            break;
    }
    printf("\n | Tipo   | %-55d | ", equipe.tipoValor);
    printf("\n | CPF    | %-55s | ", cpfFormatado);
}

void printItemFornecedor(TipoFornecedor fornecedor) {
    // Faz as formatacoes necessarias
    char telFormatado[20];
    formataTelefone(fornecedor.telefone, telFormatado);

    printf("\n=[ ID: %-4d ]=========================================================",fornecedor.id);
    printf("\n | Nome     | %-53s | ", fornecedor.nomeFantasia);
    printf("\n | Razao    | %-53s | ", fornecedor.razaoSocial);
    printf("\n | Endereco | %-53s | ", fornecedor.endereco);
    printf("\n | Telefone | %-53s | ", telFormatado);
    printf("\n | Servico  | %-53s | ", fornecedor.tipoServico);
    // Printa o cpf ou cnpj
    if(fornecedor.usa_CNPJ){
        char formatado[20];
        formataCPFouCNPJ(fornecedor.cpf_cnpj, formatado);
        printf("\n | CNPJ     | %-53s | ", formatado);
    } else {
        char formatado[20];
        formataCPFouCNPJ(fornecedor.cpf_cnpj, formatado);
        printf("\n | CPF      | %-53s | ", formatado);
    }

    printf("\n | Valor  | R$%-53.2f | ", fornecedor.valor);
    switch (fornecedor.tipoValor){
        case 0:
            printf("\n | Tipo     | Valor Fixo                                            | ");
            break;
        case 1:
            printf("\n | Tipo     | Valor Por Hora                                        | ");
            break;
        case 2:
            printf("\n | Tipo     | Valor Por Dia                                         | ");
            break;
    }
}

void printItemOperador(TipoOperador operador) {
    printf("\n=[ ID: %-4d ]=========================================================",operador.id);
    printf("\n | Nome    | %-54s | ", operador.nome);
    printf("\n | Usuario | %-54s | ", operador.usuario);
}

void printItemRecurso(TipoRecurso recurso) {
    printf("\n=[ ID: %-4d ]=========================================================",recurso.id);
    printf("\n | Descricao     | %-48s | ", recurso.descricao);
    printf("\n | Categoria     | %-48s | ", recurso.categoria);
    printf("\n | Qtd. Estoque  | %-48d | ", recurso.qtdEstoque);
    printf("\n | Preco Custo   | R$%-46.2f | ", recurso.precoCusto);
    printf("\n | Valor Locacao | R$%-46.2f | ", recurso.valorLocacao);
}

void printItemEvento(TipoEvento evento) {
    char dataInicioStr[20] = "";
    char dataFimStr[20] = "";
    if (evento.dataInicio.tm_year != 0) strftime(dataInicioStr, sizeof(dataInicioStr), "%d/%m/%Y", &evento.dataInicio);
    if (evento.dataFim.tm_year != 0) strftime(dataFimStr, sizeof(dataFimStr), "%d/%m/%Y", &evento.dataFim);

    const char *statusStr;
    switch (evento.status) {
        case STATUS_ORCAMENTO: statusStr = "Orcamento"; break;
        case STATUS_APROVADO: statusStr = "Aprovado"; break;
        case STATUS_FINALIZADO: statusStr = "Finalizado"; break;
        case STATUS_CANCELADO: statusStr = "Cancelado"; break;
        default: statusStr = "Desconhecido"; break;
    }

    printf("\n=[ ID: %-4d ]=========================================================", evento.id);
    printf("\n | Nome Evento     | %-46s | ", evento.nome);
    printf("\n | Cliente (ID)    | %-46d | ", evento.idCliente);
    printf("\n | Status          | %-46s | ", statusStr);
    printf("\n | Data Inicio     | %-46s | ", dataInicioStr);
    printf("\n | Data Fim        | %-46s | ", dataFimStr);
    printf("\n | Local           | %-46s | ", evento.localEvento);
    printf("\n | Cidade          | %-46s | ", evento.cidade);
    printf("\n | Unidade Federal | %-46s | ", evento.uf);
    printf("\n | Custo Recursos  | R$%-44.2f | ", evento.custoTotalRecurso);
    printf("\n | Custo Equipe    | R$%-44.2f | ", evento.custoTotalEquipe);
    printf("\n | Custo Fornecd.  | R$%-44.2f | ", evento.custoTotalFornecedor);
    printf("\n | Custo Total     | R$%-44.2f | ", evento.custoTotal);
    printf("\n | Margem Lucro(%%) | %-46.2f | ", evento.margemLucro);
    printf("\n | Valor Final     | R$%-44.2f | ", evento.valorFinal);
    printf("\n | Observacoes     | %-46s | ", evento.obs);
}

void printItemRecursoEvento(ItemRecursoEvento item, TipoRecurso recurso){
    printf("\n |%-24s|%-4d|%-4d|%-5d|R$%-10.2f|R$%-10.2f|"
        ,recurso.descricao,item.idRecurso,item.qtd,item.qtdTempo,item.precoUnitario,item.precoTotal);
}

void printItemEquipeEvento(ItemEquipeEvento item, TipoEquipe equipe){
    char cpfFormatado[20];
    formataCPFouCNPJ(equipe.cpf, cpfFormatado);

    printf("\n======================================================================");
    printf("\n |Nome                    |ID  |Dias |Preco   |Preco Total          | ");
    printf("\n |%-24s|%-4d|%-5d|R$%-3.2lf|R$%-16.2f|"
        ,equipe.nome,item.idEquipe,item.qtdTempo, item.precoValor, item.precoTotal);
    printf("\n |CPF     | %-55s | ", cpfFormatado);
    printf("\n |Funcao                                                            | ");
    printf("\n |%-67s| ",equipe.funcao);
}
void printItemFornecedorEvento(ItemFornecedorEvento item, TipoFornecedor fornecedor){
    printf("\n |%-24s|%-4d|%-5d|%-5d|R$%-7.2f|R$%-7.2f|"
        ,fornecedor.nomeFantasia,item.idFornecedor,item.qtdTempo,item.precoTipo,item.precoValor,item.precoTotal);
}