#include "menuImpoExpo.h"
#include "mensagens.h"

// ========== SOLICITAÇÕES DE ENTRADA - IMPORTAÇÃO/EXPORTAÇÃO ==========

int viewSolicitarOpcoesExportacao(int* exportarCli, int* exportarForn, 
                                   int* exportarEv, int* exportarRec, 
                                   int* exportarEquip) {
    char opcao;
    int algumaSelecionada = 0;
    
    printf("\n====================================================================");
    printf("\n | Selecione os dados a serem exportados:                         |");
    printf("\n====================================================================");
    
    printf("\n Exportar Clientes? (S/N): ");
    scanf(" %c", &opcao);
    *exportarCli = (opcao == 'S' || opcao == 's') ? 1 : 0;
    if (*exportarCli) algumaSelecionada = 1;
    
    printf(" Exportar Fornecedores? (S/N): ");
    scanf(" %c", &opcao);
    *exportarForn = (opcao == 'S' || opcao == 's') ? 1 : 0;
    if (*exportarForn) algumaSelecionada = 1;
    
    printf(" Exportar Eventos? (S/N): ");
    scanf(" %c", &opcao);
    *exportarEv = (opcao == 'S' || opcao == 's') ? 1 : 0;
    if (*exportarEv) algumaSelecionada = 1;
    
    printf(" Exportar Recursos? (S/N): ");
    scanf(" %c", &opcao);
    *exportarRec = (opcao == 'S' || opcao == 's') ? 1 : 0;
    if (*exportarRec) algumaSelecionada = 1;
    
    printf(" Exportar Equipes? (S/N): ");
    scanf(" %c", &opcao);
    *exportarEquip = (opcao == 'S' || opcao == 's') ? 1 : 0;
    if (*exportarEquip) algumaSelecionada = 1;
    
    limparBuffer();
    return algumaSelecionada;
}

void viewSolicitarNomeArquivo(char* nomeArquivo, const char* titulo) {
    limparTela();
    printf("\n======================================================================");
    printf("\n | # %-63s |", titulo);
    printf("\n======================================================================");
    printf("\n Nome do arquivo (com extensao .xml): ");
    fgets(nomeArquivo, 100, stdin);
    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';
    
    // Adicionar .xml se não tiver
    if (!strstr(nomeArquivo, ".xml")) {
        strcat(nomeArquivo, ".xml");
    }
}

int viewSolicitarOpcaoImportacao() {
    int opcao;
    printf("\n======================================================================");
    printf("\n | # O que deseja fazer com os dados importados?                    |");
    printf("\n======================================================================");
    printf("\n |   1. Substituir dados existentes                                 |");
    printf("\n |   2. Adicionar aos dados existentes                              |");
    printf("\n |   3. Cancelar importacao                                         |");
    printf("\n======================================================================");
    printf("\n Opcao: ");
    scanf("%d", &opcao);
    limparBuffer();
    return opcao;
}

// ========== EXIBIÇÃO DE RESULTADOS - IMPORTAÇÃO/EXPORTAÇÃO ==========

void viewExibirSucessoExportacao(int quantidade, const char* nomeArquivo, const char* tipo) {
    printf("\n======================================================================");
    printf("\n | EXPORTACAO BEM-SUCEDIDA                                          |");
    printf("\n======================================================================");
    printf("\n | Tipo: %-59s |", tipo);
    printf("\n | Quantidade: %-52d |", quantidade);
    printf("\n | Arquivo: %-55s |", nomeArquivo);
    printf("\n======================================================================");
}

void viewExibirResultadoImportacao(int resultado, int quantidade, const char* tipo) {
    if (resultado == 1) {
        printf("\n======================================================================");
        printf("\n | IMPORTACAO BEM-SUCEDIDA - DADOS SUBSTITUIDOS                     |");
        printf("\n======================================================================");
        printf("\n | Tipo: %-59s |", tipo);
        printf("\n | Quantidade importada: %-42d |", quantidade);
        printf("\n======================================================================");
    }
    else if (resultado == 2) {
        printf("\n======================================================================");
        printf("\n | IMPORTACAO BEM-SUCEDIDA - DADOS ADICIONADOS                      |");
        printf("\n======================================================================");
        printf("\n | Tipo: %-59s |", tipo);
        printf("\n | Quantidade importada: %-42d |", quantidade);
        printf("\n======================================================================");
    }
    else if (resultado == 0) {
        printMensagem("Importacao cancelada pelo usuario", "INFO");
    }
    else if (resultado == -1) {
        printMensagem("Erro de memoria ao processar dados", "ERRO");
    }
}

void exibirCabecalhoExportacao() {
    limparTela();
    printf("\n======================================================================");
    printf("\n | # EXPORTACAO DE DADOS                                            |");
    printf("\n======================================================================");
}

void exibirResumoExportacao(int totalClientes, int totalFornecedores, 
                           int totalEventos, int totalRecursos, int totalEquipes) {
    printf("\n======================================================================");
    printf("\n | RESUMO DA EXPORTACAO                                             |");
    printf("\n======================================================================");
    if (totalClientes > 0)
        printf("\n | - Clientes: %-52d |", totalClientes);
    if (totalFornecedores > 0)
        printf("\n | - Fornecedores: %-47d |", totalFornecedores);
    if (totalEventos > 0)
        printf("\n | - Eventos: %-53d |", totalEventos);
    if (totalRecursos > 0)
        printf("\n | - Recursos: %-52d |", totalRecursos);
    if (totalEquipes > 0)
        printf("\n | - Equipes: %-53d |", totalEquipes);
    printf("\n======================================================================");
}

void viewAguardarContinuar() {
    printf("\n\n Pressione ENTER para continuar...");
    getchar();
}

// ========== MENSAGENS ESPECÍFICAS ==========

void exibirMensagemSucesso(const char* mensagem) {
    printMensagem((char*)mensagem, "#");
}

void exibirMensagemErro(const char* mensagem) {
    printMensagem((char*)mensagem, "ERRO");
}

void exibirMensagemInfo(const char* mensagem) {
    printMensagem((char*)mensagem, "INFO");
}

void exibirMensagemProcessando(const char* mensagem) {
    printMensagem((char*)mensagem, "...");
}