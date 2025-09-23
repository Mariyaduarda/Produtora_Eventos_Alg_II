#include "mostrarItem.h"

//Funcoes para printar os itens
// - Cliente, Produtora etc

void printItemCliente(TipoCliente cliente) {
    printf("\n | ID           | %-49d | ", cliente.id);
    printf("\n | Nome         | %-49s | ", cliente.nome);
    printf("\n | Endereco     | %-49s | ", cliente.endereco);
    printf("\n | CPF/CNPJ     | %-49s | ", cliente.cpf_cnpj);
    printf("\n | Telefone     | %-49s | ", cliente.telefone);
    printf("\n | Email        | %-49s | ", cliente.email);
    printf("\n | Nome Contato | %-49s | ", cliente.nomeDoContato);
}

void printItemEquipe(TipoEquipe equipe) {
    printf("\n | ID     | %-55d | ", equipe.id);
    printf("\n | Nome   | %-55s | ", equipe.nome);
    printf("\n | CPF    | %-55s | ", equipe.cpf);
    printf("\n | Funcao | %-55s | ", equipe.funcao);
    printf("\n | Valor  | %-55.2f | ", equipe.valorDiariaHora);
}

void printItemFornecedor(TipoFornecedor fornecedor) {
    printf("\n | ID       | %-53d | ", fornecedor.id);
    printf("\n | Nome     | %-53s | ", fornecedor.nomeFantasia);
    printf("\n | Razao    | %-53s | ", fornecedor.razaoSocial);
    printf("\n | CPF/CNPJ | %-53s | ", fornecedor.cpf_cnpj);
    printf("\n | Endereco | %-53s | ", fornecedor.endereco);
    printf("\n | Telefone | %-53s | ", fornecedor.telefone);
    printf("\n | Servico  | %-53s | ", fornecedor.tipoServico);
}

void printItemOperador(TipoOperador operador) {
    printf("\n | ID      | %-54d | ", operador.id);
    printf("\n | Nome    | %-54s | ", operador.nome);
    printf("\n | Usuario | %-54s | ", operador.usuario);
}

void printItemProdutora(TipoProdutora produtora) {
    printf("\n | ID              | %-46d | ", produtora.id);
    printf("\n | Nome            | %-46s | ", produtora.nomeFantasia);
    printf("\n | Razao           | %-46s | ", produtora.razaoSocial);
    printf("\n | CNPJ            | %-46s | ", produtora.cnpj);
    printf("\n | Endereco        | %-46s | ", produtora.endereco);
    printf("\n | Telefone        | %-46s | ", produtora.telefone);
    printf("\n | Email           | %-46s | ", produtora.email);
    printf("\n | Responsavel     | %-46s | ", produtora.nomeDoResponsavel);
    printf("\n | Telefone Resp.  | %-46s | ", produtora.telefoneDoResponsavel);
    printf("\n | Margem de Lucro | %-46.2f | ", produtora.margemDeLucro);
}

void printItemRecurso(TipoRecurso recurso) {
    printf("\n | ID            | %-48d | ", recurso.id);
    printf("\n | Descricao     | %-48s | ", recurso.descricao);
    printf("\n | Categoria     | %-48s | ", recurso.categoria);
    printf("\n | Qtd. Estoque  | %-48d | ", recurso.qtdEstoque);
    printf("\n | Preco Custo   | %-48.2f | ", recurso.precoCusto);
    printf("\n | Valor Locacao | %-48.2f | ", recurso.valorLocacao);
}