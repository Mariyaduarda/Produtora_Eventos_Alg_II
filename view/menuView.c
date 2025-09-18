#include "menuView.h"

// Aqui tem tds as funcoes de exibicao de menus

void printMenuPrincipal(){
    limparTela();
    printf("\n => Menu Principal"
        "\n 1. Gerenciar TipoCliente                 "
        "\n 2. Gerenciar Fornecedores e Parceiros "
        "\n 3. Gerenciar Produtora                "
        "\n 4. Gerenciar Equipe Interna           "
        "\n 5. Gerenciar Recursos e Equipamentos  "
        "\n 6. Gerenciar Operadores do Sistema    "
        "\n 0. Sair                               "
        "\n => "
    );
}

void printMenuCliente(){
    limparTela();
    printf("\n => TipoCliente"
        "\n 1. Adicionar"
        "\n 2. Remover"
        "\n 3. Atualizar"
        "\n 4. Buscar"
        "\n 5. Listar"
        "\n 0. Voltar "
        "\n => "
    );
}

void printMenuFornecedorParceiro(){
    limparTela();
    printf("\n => Fornecedores & Parceiros"
        "\n 1. Adicionar"
        "\n 2. Remover"
        "\n 3. Atualizar"
        "\n 4. Buscar"
        "\n 5. Listar"
        "\n 0. Voltar "
        "\n => "
    );
}

void printMenuProdutora(){
    limparTela();
    printf("\n => Produtora"
        "\n 1. Adicionar"
        "\n 2. Remover"
        "\n 3. Atualizar"
        "\n 4. Buscar"
        "\n 5. Listar"
        "\n 0. Voltar "
        "\n => "
    );

}

void printMenuEquipeInterna(){
    limparTela();
    printf("\n => Equipe Interna"
        "\n 1. Adicionar"
        "\n 2. Remover"
        "\n 3. Atualizar"
        "\n 4. Buscar"
        "\n 5. Listar"
        "\n 0. Voltar "
        "\n => "
    );

}

void printMenuRecursoEquipamento(){
    limparTela();
    printf("\n => Recursos & Equipamentos"
        "\n 1. Adicionar"
        "\n 2. Remover"
        "\n 3. Atualizar"
        "\n 4. Buscar"
        "\n 5. Listar"
        "\n 0. Voltar "
        "\n => "
    );

}

void printMenuOperadorSistema(){
    limparTela();
    printf("\n => Operadores do Sistema"
        "\n 1. Adicionar"
        "\n 2. Remover"
        "\n 3. Atualizar"
        "\n 4. Buscar"
        "\n 5. Listar"
        "\n 0. Voltar "
        "\n => "
    );
}