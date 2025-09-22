#include "mostrarItem.h"

//Funcoes para printar os itens
// - Cliente, Produtora etc

void printItemCliente(TipoCliente cliente) {
    printf("\n | =======================================");
    printf("\n | ID:       %d", cliente.id);
    printf("\n | Nome:     %s", cliente.nome);
    printf("\n | CPF/CNPJ: %s", cliente.cpf_cnpj);
    printf("\n | Telefone: %s", cliente.telefone);
    printf("\n | Email:    %s", cliente.email);
}

void printItemEquipe(TipoEquipe equipe) {
    printf("\n | =======================================");
    printf("\n | ID:      %d", equipe.id);
    printf("\n | Nome:    %s", equipe.nome);
    printf("\n | CPF:     %s", equipe.cpf);
    printf("\n | Funcao:  %s", equipe.funcao);
    printf("\n | Valor:   %.2f", equipe.valorDiariaHora);
}

void printItemFornecedor(TipoFornecedor fornecedor) {
    printf("\n | =======================================");
    printf("\n | ID:            %d", fornecedor.id);
    printf("\n | Nome:          %s", fornecedor.nomeFantasia);
    printf("\n | Razao:         %s", fornecedor.razaoSocial);
    printf("\n | CPF/CNPJ:      %s", fornecedor.cpf_cnpj);
    printf("\n | Endereco:      %s", fornecedor.endereco);
    printf("\n | Telefone:      %s", fornecedor.telefone);
    printf("\n | Tipo Servico:  %s", fornecedor.tipoServico);
}

void printItemOperador(TipoOperador operador) {
    printf("\n | =======================================");
    printf("\n | ID:       %d", operador.id);
    printf("\n | Nome:     %s", operador.nome);
    printf("\n | Usuario:  %s", operador.usuario);
}

void printItemProdutora(TipoProdutora produtora) {
    printf("\n | =======================================");
    printf("\n | ID:               %d", produtora.id);
    printf("\n | Nome:             %s", produtora.nomeFantasia);
    printf("\n | Razao:            %s", produtora.razaoSocial);
    printf("\n | CNPJ:             %s", produtora.cnpj);
    printf("\n | Endereco:         %s", produtora.endereco);
    printf("\n | Telefone:         %s", produtora.telefone);
    printf("\n | Email:            %s", produtora.email);
    printf("\n | Responsavel:      %s", produtora.nomeDoResponsavel);
    printf("\n | Tel. Resp.:       %s", produtora.telefoneDoResponsavel);
    printf("\n | Margem de Lucro:  %.2f%%", produtora.margemDeLucro);
}

void printItemRecurso(TipoRecurso recurso) {
    printf("\n | =======================================");
    printf("\n | ID:             %d", recurso.id);
    printf("\n | Descricao:      %s", recurso.descricao);
    printf("\n | Categoria:      %s", recurso.categoria);
    printf("\n | Qtd. Estoque:   %d", recurso.qtdEstoque);
    printf("\n | Preco Custo:    %.2f", recurso.precoCusto);
    printf("\n | Valor Locacao:  %.2f", recurso.valorLocacao);
}