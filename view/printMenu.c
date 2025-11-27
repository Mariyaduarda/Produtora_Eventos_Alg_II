#include "printMenu.h"

// Aqui tem tds as funcoes de exibicao de menus

void printMenuPrincipal(TipoProdutora produtora){
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Sistema de Gestao - %-42s | "
        "\n |==================================================================| "
        "\n |   1. Menu de Gerenciamento de dados                              | "
        "\n |   2. Gerenciar Eventos                                           | "
        "\n |   3. Gerenciar Financeiro                                        | "
        "\n |   4. Salvar dados                                                | "
        "\n |   5. Configuracoes                                               | "
        "\n |==================================================================| "
        "\n |   0. Sair                                                        | "
        "\n======================================================================"
        , produtora.nomeFantasia
    );
}

void printMenuCRUD(){
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Dados                                         | "
        "\n |==================================================================| "
        "\n |   1. Gerenciar Produtora                                         | "
        "\n |   2. Gerenciar Clientes                                          | "
        "\n |   3. Gerenciar Equipe Interna                                    | "
        "\n |   4. Gerenciar Fornecedores e Parceiros                          | "
        "\n |   5. Gerenciar Operadores do Sistema                             | "
        "\n |   6. Gerenciar Recursos e Equipamentos                           | "
        "\n |==================================================================| "
        "\n |   0. Sair                                                        | "
        "\n======================================================================"
    );
}

//===============================================
// Menus CRUD

void printMenuProdutora(TipoProdutora produtora){
    limparTela();
    // header
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento da Produtora                                     | "
        "\n |==================================================================| "
    );

    // dados atuais
    printItemProdutora(produtora);

    // opcoes do menu
    printf(
        "\n |==================================================================| "
        "\n |   1. Atualizar Dados                                             | "
        "\n |   2. Apagar Dados                                                | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );
}

void printMenuCliente(){
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Clientes                                      | "
        "\n |==================================================================| "
        "\n |   1. Adicionar                                                   | "
        "\n |   2. Remover                                                     | "
        "\n |   3. Atualizar                                                   | "
        "\n |   4. Buscar                                                      | "
        "\n |   5. Listar                                                      | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );
}

void printMenuFornecedor(){
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Fornecedores e Parceiros                      | "
        "\n |==================================================================| "
        "\n |   1. Adicionar                                                   | "
        "\n |   2. Remover                                                     | "
        "\n |   3. Atualizar                                                   | "
        "\n |   4. Buscar                                                      | "
        "\n |   5. Listar                                                      | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );
}

void printMenuEquipe(){
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Equipes Internas                              | "
        "\n |==================================================================| "
        "\n |   1. Adicionar                                                   | "
        "\n |   2. Remover                                                     | "
        "\n |   3. Atualizar                                                   | "
        "\n |   4. Buscar                                                      | "
        "\n |   5. Listar                                                      | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );

}

void printMenuRecurso(){
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Recursos e Equipamentos                       | "
        "\n |==================================================================| "
        "\n |   1. Adicionar                                                   | "
        "\n |   2. Remover                                                     | "
        "\n |   3. Atualizar                                                   | "
        "\n |   4. Buscar                                                      | "
        "\n |   5. Listar                                                      | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );

}

void printMenuOperador(){
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Operadores de Sistema                         | "
        "\n |==================================================================| "
        "\n |   1. Adicionar                                                   | "
        "\n |   2. Remover                                                     | "
        "\n |   3. Atualizar                                                   | "
        "\n |   4. Buscar                                                      | "
        "\n |   5. Listar                                                      | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );
}

void printMenuConfig(TipoConfig config){
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Configuracoes do Sistema                                       | "
        "\n |==================================================================| "
        "\n |   1. Resetar configuracoes                                       | "
        "\n |   2. Metodo de Salvamento                                %s | "
        "\n |   3. Validar dados                                    %s | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================",
        config.salvar_como_binario ? "Binario" : "  Texto",
        config.validar_dados ? "     Ativa" : "Desativada"
    );
}

// ===== MENU DE TRANSACOES =====
void printMenuTransacaoPrincipal() {
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento Financeiro                                       |"
        "\n |==================================================================|"
        "\n |   1. Movimentacao de Caixa                                       |"
        "\n |   2. Contas a Receber                                            |"
        "\n |   3. Contas a Pagar                                              |"
        "\n |   4. Nota Fiscal de Entrada                                      |"
        "\n |   5. Relatorios                                                  |"
        "\n |==================================================================|"
        "\n |   0. Voltar                                                      |"
        "\n======================================================================"
    );
}

// ===== MENU MVIMENTACAO DO CAIXA =====
void printMenuMovimentacaoCaixa(float saldo) {
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Movimentacao de Caixa                                          |"
        "\n |==================================================================|"
        "\n | Saldo Atual: R$ %-48.2f |"
        "\n |==================================================================|"
        "\n |   1. Registrar Entrada                                           |"
        "\n |   2. Registrar Saida                                             |"
        "\n |   3. Consultar Movimentacoes                                     |"
        "\n |==================================================================|"
        "\n |   0. Voltar                                                      |"
        "\n======================================================================",
        saldo
    );
}

// ===== MENU CONTAS A RECEBER =====
void printMenuContasReceber() {
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Contas a Receber                                               |"
        "\n======================================================================"
        "\n |   1. Gerar Conta (via Evento)                                    |"
        "\n |   2. Baixar Conta (Receber Pagamento)                            |"
        "\n |   3. Consultar Conta especifica                                  |"
        "\n |   4. Listar Todas as Contas                                      |"
        "\n |------------------------------------------------------------------|"
        "\n |   0. Voltar                                                      |"
        "\n======================================================================"
    );
}
// ===== MENU CONTAS A PAGAR =====
void printMenuContasPagar() {
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Contas a Pagar                                                 |"
        "\n======================================================================"
        "\n |   1. Gerar Conta Manual                                          |"
        "\n |   2. Baixar Conta (Efetuar Pagamento)                            |"
        "\n |   3. Consultar Conta especifica                                  |"
        "\n |   4. Listar Todas as Contas                                      |"
        "\n |------------------------------------------------------------------|"
        "\n |   0. Voltar                                                      |"
        "\n======================================================================"
    );
}
// ===== MENU RELATORIOS =====
void printMenuRelatorios() {
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Relatorios Financeiros                                         |"
        "\n======================================================================"
        "\n |   1. Fluxo de Caixa                                              |"
        "\n |   2. Contas a Receber                                            |"
        "\n |   3. Contas a Pagar                                              |"
        "\n |------------------------------------------------------------------|"
        "\n |   0. Voltar                                                      |"
        "\n======================================================================"
    );
}

// ===== MENU DE EVENTOS =====
void printMenuEventos() {
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Eventos                                       | "
        "\n |==================================================================| "
        "\n |   1. Novo Evento                                                 | "
        "\n |   2. Remover Eventos                                             | "
        "\n |   3. Gerenciar Evento                                            | "
        "\n |   4. Listar Evento                                               | " 
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );
}

void printMenuEventoGerenciar(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    printItemEvento(*evento);
    
    printf(
        "\n======================================================================"
        "\n |   1. Editar Dados Basicos                                        | "
        "\n |   2. Gerenciar Recursos                                          | "
        "\n |   3. Gerenciar Equipes                                           | "
        "\n |   4. Gerenciar Fornecedores                                      | "
        "\n |   5. Mudar Status                                                | "
        "\n |   6. Ver Relatorio                                               | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );
}

void printMenuEventoGerenciarRecursos(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    printItemEvento(*evento);
    
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Recursos do Evento                            | "
        "\n |==================================================================| "
        "\n |   1. Adicionar Recurso                                           | "
        "\n |   2. Remover Recurso                                             | "
        "\n |   3. Listar Recursos                                             | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );
}

void printMenuEventoGerenciarEquipes(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    printItemEvento(*evento);
    
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Equipes do Evento                             | "
        "\n |==================================================================| "
        "\n |   1. Adicionar Equipe                                            | "
        "\n |   2. Remover Equipe                                              | "
        "\n |   3. Listar Equipes                                              | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );
}

void printMenuEventoGerenciarFornecedores(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    printItemEvento(*evento);
    
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Fornecedores do Evento                        | "
        "\n |==================================================================| "
        "\n |   1. Adicionar Fornecedor                                        | "
        "\n |   2. Remover Fornecedor                                          | "
        "\n |   3. Listar Fornecedores                                        | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );
}

void printMenuEventoGerenciarDados(TipoEvento *evento, TipoConfig *config) {
    limparTela();
    printItemEvento(*evento);
    
    printf(
        "\n======================================================================"
        "\n | # Gerenciamento de Dados Basicos do Evento                       | "
        "\n |==================================================================| "
        "\n |   1. Editar Nome                                                 | "
        "\n |   2. Editar Local                                                | "
        "\n |   3. Editar Cidade                                               | "
        "\n |   4. Editar UF                                                   | "
        "\n |   5. Editar Margem de Lucro                                      | "
        "\n |   6. Editar Observacoes                                          | "
        "\n |   7. Editar Datas                                                | "
        "\n |==================================================================| "
        "\n |   0. Voltar                                                      | "
        "\n======================================================================"
    );
}