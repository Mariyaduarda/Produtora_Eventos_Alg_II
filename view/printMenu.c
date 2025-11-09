#include "printMenu.h"

// Aqui tem tds as funcoes de exibicao de menus

void printMenuPrincipal(TipoProdutora produtora){
    limparTela();
    printf(
        "\n======================================================================"
        "\n | # Sistema de Gestao - %-43s | "
        "\n |==================================================================| "
        "\n |   1. Menu de Gerenciamento de dados                              | "
        "\n |   2. Salvar dados                                                | "
        "\n |   3. Configuracoes                                               | "
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